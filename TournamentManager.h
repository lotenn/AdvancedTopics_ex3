#ifndef ADVANCEDTOPICS3_TOURNAMENTMANAGER_H
#define ADVANCEDTOPICS3_TOURNAMENTMANAGER_H

#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include "GameManager.h"
using namespace std;

class TournamentManager {
private:
    static TournamentManager theTournamentManager;
    map<string, std::function<unique_ptr<PlayerAlgorithm>()>> factory;
    map<string, atomic<int>> scores;
    // private ctor
    TournamentManager() {}

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
    void runTournament() const;
};


#endif //ADVANCEDTOPICS3_TOURNAMENTMANAGER_H
