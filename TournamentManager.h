#ifndef ADVANCEDTOPICS3_TOURNAMENTMANAGER_H
#define ADVANCEDTOPICS3_TOURNAMENTMANAGER_H

#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <atomic>
#include <dlfcn.h>
#include "GameManager.h"
using namespace std;

#define BUF_SIZE 1024
#define PATH_MAX_SIZE 4096
#define DEFAULT_NUM_OF_THREADS 4
#define DEFAULT_PATH ""

class TournamentManager {
private:
    static TournamentManager theTournamentManager;
    map<string, std::function<unique_ptr<PlayerAlgorithm>()>> factory;
    map<string, atomic<int>> scores;
    vector<void *> dlPlayerAlgorithms;
    // private ctor
    TournamentManager() = default;

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

    void runTournament() const;
};


#endif //ADVANCEDTOPICS3_TOURNAMENTMANAGER_H
