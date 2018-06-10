#include <algorithm>
#include <sstream>
#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

bool TournamentManager::loadPlayerAlgorithms(){
    //todo: check if there were no so files

    FILE *dl;   // handle to read directory
    stringstream stream_command_str;
    stream_command_str << "ls " << path << "/*.so";
    string command_str = stream_command_str.str();

    dl = popen(command_str.c_str(), "r");
    if(!dl)
        return false;

    void *dPlayerAlgorithm;
    char in_buf[BUF_SIZE]; // input buffer for playerAlgorithm names
    char playerAlgorithmName[1024];
    while(fgets(in_buf, BUF_SIZE, dl)) {
        // trim off the whitespace
        char *ws = strpbrk(in_buf, " \t\n");
        if (ws) *ws = '\0';
        // append ./ to the front of the lib playerAlgorithmName
        sprintf(playerAlgorithmName, "%s", in_buf);
        dPlayerAlgorithm = dlopen(playerAlgorithmName, RTLD_NOW);

        if (dPlayerAlgorithm == NULL)
            return false;

        char *playerId;
        const char delim[] = " ._";
        playerId = strtok(playerAlgorithmName, delim);
        playerId = strtok(NULL, delim);

        //if the PA was not registered
        if(factory.find(playerId) == factory.end()){
          cout << "Player Algorithm: " << playerAlgorithmName << " was not registered" << endl;
        }
        gamesPlayed[playerId] = 0;
        dlPlayerAlgorithms.push_back(dPlayerAlgorithm);
    }
    return true;
}

/*
 * thread function
 */
 void TournamentManager::runGame(){
   while(true) {
        theTournamentManager.tournamentMutex.lock();
        auto mapIter = theTournamentManager.gamesPlayed.begin();
        for(; mapIter->second >= MAX_GAMES_NUMBER &&
              mapIter!= theTournamentManager.gamesPlayed.end(); mapIter++);
        if(mapIter == theTournamentManager.gamesPlayed.end()){
			theTournamentManager.tournamentMutex.unlock();
			break;
		}

        string player1_id = mapIter->first;
        theTournamentManager.gamesPlayed[player1_id]++;

        string player2_id;

        vector<string> finishedIDs;
        vector<string> unFinishedIDs;

        mapIter = theTournamentManager.gamesPlayed.begin();
        for(;mapIter != theTournamentManager.gamesPlayed.end(); mapIter++){
            if(player1_id == mapIter->first)
                continue;
            if(mapIter->second >= MAX_GAMES_NUMBER)
                finishedIDs.push_back(mapIter->first);
            else
                unFinishedIDs.push_back(mapIter->first);
        }
        std::srand(std::time(nullptr));
        int unfinished_size = (int)unFinishedIDs.size();
        bool player2NotFinished = unfinished_size > 0;
        if(player2NotFinished){
			int player2_ID_index = rand()%unfinished_size;
		    player2_id = unFinishedIDs[player2_ID_index];
            theTournamentManager.gamesPlayed[player2_id]++;
        }
        else{
			int finished_size = (int)finishedIDs.size();
			if(finished_size != 0){
				int player2_ID_index = rand() % finished_size;
				player2_id = finishedIDs[player2_ID_index];
				theTournamentManager.gamesPlayed[player2_id]++;
			}
        }
        theTournamentManager.tournamentMutex.unlock();
        GameManager gameManager(theTournamentManager.factory[player1_id](), theTournamentManager.factory[player2_id]());
        gameManager.initGame();
        gameManager.positioningStage();
        if (!gameManager.getGameStatus().isGameOn()) {
            theTournamentManager.updateScores(player1_id, player2_id, gameManager, player2NotFinished);
			continue;
        }
        gameManager.moveStage();
        theTournamentManager.updateScores(player1_id, player2_id, gameManager, player2NotFinished);
    }
}

void TournamentManager::updateScores(string &player1_id, string &player2_id, GameManager &gameManager, bool updatePlayer2) {
    playerEnum winner = gameManager.getGameStatus().getWinner();
    switch(winner){
        case PLAYER_1:
            scores[player1_id]+=3;
            break;
        case PLAYER_2:
            if(updatePlayer2)
                scores[player2_id]+=3;
            break;
        default:
            scores[player1_id]++;
            if(updatePlayer2)
                scores[player2_id]++;
            break;
    }
}

void TournamentManager::runTournament(){
    if(!theTournamentManager.loadPlayerAlgorithms()){
        cout << "Error: dll load failed" << endl;
        return;
    }
	if((int)factory.size() <= 1){
		cout << "Not enough players for tournament" << endl;
		cleanup();
		return;
	}
    int actual_thread_num = std::min(((int)dlPlayerAlgorithms.size()-1)*MAX_GAMES_NUMBER, numOfthreads);
    vector<thread> gameThreads;
    for(int i=0; i<actual_thread_num-1; i++){
        gameThreads.push_back(thread(runGame));
    }
    runGame();
    for(int i=0; i<(int)gameThreads.size(); i++){
        gameThreads[i].join();
    }
    printTournamentResults();
    cleanup();
}

void TournamentManager::cleanup(){
     factory.clear();
     for(int i=0; i<(int)dlPlayerAlgorithms.size(); i++)
         dlclose(dlPlayerAlgorithms[i]);
}

void TournamentManager::setNumOfthreads(int numOfthreads) {
    TournamentManager::numOfthreads = numOfthreads;
}

void TournamentManager::setPath(char *path) {
    TournamentManager::path = path;
}

void TournamentManager::printTournamentResults(){
    auto cmp = [](std::pair<string,int> const & a, std::pair<string,int> const & b) {
        return a.second != b.second?  a.second < b.second : a.first < b.first;
    };
    vector<std::pair<string,int>> pairs;
    for(auto iter = scores.begin(); iter!=scores.end(); iter++){
        pairs.push_back(*iter);
    }
    std::sort(pairs.begin(), pairs.end(), cmp);
    for(auto iter = pairs.rbegin(); iter!=pairs.rend(); iter++){
        cout << iter->first << " " << iter->second << endl;
    }
 }
