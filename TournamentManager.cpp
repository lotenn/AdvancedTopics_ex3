#include "TournamentManager.h"

const char *path = DEFAULT_PATH;
int numOfThreads = DEFAULT_NUM_OF_THREADS;

TournamentManager TournamentManager::theTournamentManager;

bool TournamentManager::loadPlayerAlgorithms(){
    FILE *dl;   // handle to read directory
    char command_str[PATH_MAX_SIZE + strlen("ls *.so")];
    sprintf(command_str, "ls %s*.so", path);  // command string to get dynamic lib names
    dl = popen(command_str, "r");
    if(!dl){
        perror("popen");
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
            cerr << dlerror() << endl;
            return false;
        }
    }


//    list<void *> dl_list; // list to hold handles for dynamic libs
////    list<void *>::iterator itr;
////    vector<string> shape_names;  // vector of shape types used to build menu
////    list<shape *> shape_list;  // list of shape objects we create
////    list<shape *>::iterator sitr;
////    map<string, maker_t *, less<string> >::iterator fitr;
////    // get the names of all the dynamic libs (.so  files) in the current dir
        // add the handle to our list
////        dl_list.insert(dl_list.end(), dlib);

    return true;
}


void TournamentManager::runTournament() const{


}