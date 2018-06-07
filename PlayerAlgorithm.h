//
// Created by loten on 23/04/2018.
//

#ifndef ADVANCEDTOPICS2_PLAYERALGORITHM_H
#define ADVANCEDTOPICS2_PLAYERALGORITHM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <ctime>
#include "FightInfo.h"
#include "Move.h"

using namespace std;

#define INVALID_COORD (-1)
#define INVALID_CHAR '\0'
#define PRIMARY 0
#define SECONDARY 1
#define LEFTMOST_COL 0
#define RIGHTMOST_COL (M-1)
#define UPMOST_ROW (N-1)
#define DOWNMOST_ROW 0

class PlayerAlgorithm {
public:
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)=0;
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights)=0;
    virtual void notifyOnOpponentMove(const Move& move)=0; // called only on opponent’s move
    virtual void notifyFightResult(const FightInfo& fightInfo)=0; // called only if there was a fight
    virtual unique_ptr<Move> getMove()=0;
    virtual unique_ptr<JokerChange> getJokerChange()=0; // nullptr if no change is requested
    virtual ~PlayerAlgorithm() {}
};

#endif //ADVANCEDTOPICS2_PLAYERALGORITHM_H
