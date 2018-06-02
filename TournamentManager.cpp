#include "TournamentManager.h"

const char *path = DEFAULT_PATH;
int numOfThreads = DEFAULT_NUM_OF_THREADS;

TournamentManager TournamentManager::theTournamentManager;
int currentUndonePlayer = 0;

bool TournamentManager::loadPlayerAlgorithms(){
    //todo: check if there were no so files

    FILE *dl;   // handle to read directory
    char command_str[PATH_MAX_SIZE + strlen("ls *.so")];
    sprintf(command_str, "ls %s*.so", path);  // command string to get dynamic lib names
    dl = popen(command_str, "r");
    if(!dl){
        //todo: maybe take off
        perror("popen error");
        return false;
    }
    void *dPlayerAlgorithm;
    char in_buf[BUF_SIZE]; // input buffer for playerAlgorithm names
    char playerAlgorithmName[1024];
    while(fgets(in_buf, BUF_SIZE, dl)) {
        // trim off the whitespace
        char *ws = strpbrk(in_buf, " \t\n");
        if (ws) *ws = '\0';
        // append ./ to the front of the lib playerAlgorithmName
        sprintf(playerAlgorithmName, "./%s", in_buf);
        dPlayerAlgorithm = dlopen(playerAlgorithmName, RTLD_NOW);
        if (dPlayerAlgorithm == NULL) {
            //todo: maybe take off
            cerr << dlerror() << endl;
            return false;
        }
        char *playerId;
        const char delim[] = " ._";

        playerId = strtok(playerAlgorithmName, delim);
        playerId = strtok(NULL, delim);

        //if the PA was not registered
        if(factory.find(playerId) == factory.end()){
          cout << "Player Algorithm: " << playerAlgorithmName << " was not registered" << endl;
        }
        IDs.push_back(playerId);
        gamesPlayed.push_back(0);
        dlPlayerAlgorithms.push_back(dPlayerAlgorithm);
    }
    return true;
}

/*
 * thread function
 */
void TournamentManager::runGame(){

    while(true) {
        tournamentMutex.lock();
        while(currentUndonePlayer < (int)IDs.size() && gamesPlayed[currentUndonePlayer] >= MAX_GAMES_NUMBER)
            currentUndonePlayer++;
        if(currentUndonePlayer >= (int)IDs.size()){break;}
        string player1_id = IDs[currentUndonePlayer];
        string player2_id;


        tournamentMutex.unlock();
        GameManager gameManager(factory[player1_id](), factory[player2_id]());
        gameManager.initGame();
        gameManager.positioningStage();
        if (!gameManager.getGameStatus().isGameOn()) {
            updateScores(player1_id, player2_id, gameManager);
        }
        gameManager.moveStage();
        updateScores(player1_id, player2_id, gameManager);
    }
}

void TournamentManager::updateScores(string &player1_id, string &player2_id, GameManager &gameManager) {
    playerEnum winner = gameManager.getGameStatus().getWinner();
    switch(winner){
        case PLAYER_1:
            scores[player1_id]+=3;
            break;
        case PLAYER_2:
            scores[player2_id]+=3;
            break;
        default:
            scores[player1_id]++;
            scores[player2_id]++;
            break;
    }
}


void TournamentManager::runTournament() const{

}