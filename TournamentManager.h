#ifndef ADVANCEDTOPICS3_TOURNAMENTMANAGER_H
#define ADVANCEDTOPICS3_TOURNAMENTMANAGER_H

#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <atomic>
#include <dlfcn.h>
#include <string>
#include <mutex>
#include <thread>
#include "GameManager.h"
using namespace std;

#define BUF_SIZE 1024
#define PATH_MAX_SIZE 4096
#define DEFAULT_NUM_OF_THREADS 4
#define DEFAULT_PATH "./"
//todo: max to 30
#define MAX_GAMES_NUMBER 100

class TournamentManager {
private:
    static TournamentManager theTournamentManager;
    mutex tournamentMutex;
    map<string, std::function<unique_ptr<PlayerAlgorithm>()>> factory;
    map<string, atomic<int>> scores;
    map<string, int> gamesPlayed;
    vector<void *> dlPlayerAlgorithms;
    int numOfthreads;
    const char *path;
    // private ctor
    TournamentManager():numOfthreads(DEFAULT_NUM_OF_THREADS), path(DEFAULT_PATH){};

public:
    static TournamentManager& getTournamentManager() {
        return theTournamentManager;
    }
    void registerAlgorithm(string id, function<unique_ptr<PlayerAlgorithm>()> factoryMethod) {
        if (factory.find(id) == factory.end()){
            factory[id] = factoryMethod;
            scores[id] = 0;
        }
        else{
            //todo: error msg
        }
    }
    bool loadPlayerAlgorithms();
    static void runGame();
    void runTournament();
    void updateScores(string &player1_id, string &player2_id, GameManager &gameManager, bool updatePlayer2);
    void cleanup();
    void setNumOfthreads(int numOfthreads);
    void setPath(char *path);
    void printTournamentResults();
};


#endif //ADVANCEDTOPICS3_TOURNAMENTMANAGER_H
