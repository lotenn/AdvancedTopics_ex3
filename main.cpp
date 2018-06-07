#include "TournamentManager.h"
#include "MainAux.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(!(argc == 1 || argc == 3 || argc == 5)){
        cout << "Invalid number of command line arguments" << endl;
        return 0;
    }
    TournamentManager theTournamentManager = TournamentManager::getTournamentManager();
    int num_of_threads;
    char *path;
    bool threadArgPassed = false, pathArgPassed = false;
    for(int i = 1; i < argc; i+=2){
        parsingArgsResult res = parseArguments(argv[i], argv[i+1], num_of_threads, path);
        if(res == PARSE_THREAD && !threadArgPassed){
            theTournamentManager.setNumOfthreads(num_of_threads);
            threadArgPassed = true;
        }
        else if(res == PARSE_PATH && !pathArgPassed){
            theTournamentManager.setPath(path);
            pathArgPassed = true;
        }
        else{
            cout << "Wrong argument format" << endl;
            return 0;
        }
    }


    return 0;
}