//
// Created by Saar on 04/05/2018.
//

#ifndef ADVANCEDTOPICS2_GAMESTATUS_H
#define ADVANCEDTOPICS2_GAMESTATUS_H

#include "EnumUtils.h"


class GameStatus {
private:
    bool gameOn;
    endGameReason mainReason;
    endGameReason reason1;
    endGameReason reason2;
    playerEnum winner;
    playerEnum loser;

public:
    GameStatus(): gameOn(true){}

    bool isGameOn() const {
        return gameOn;
    }

    void setGameOn(){
        GameStatus::gameOn = true;
    }

    void setGameOff() {
        GameStatus::gameOn = false;
    }

    endGameReason getMainReason() const {
        return mainReason;
    }

    void setMainReason(endGameReason mainReason) {
        GameStatus::mainReason = mainReason;
    }

    endGameReason getReason1() const {
        return reason1;
    }

    void setReason1(endGameReason reason1) {
        GameStatus::reason1 = reason1;
    }

    endGameReason getReason2() const {
        return reason2;
    }

    void setReason2(endGameReason reason2) {
        GameStatus::reason2 = reason2;
    }

    playerEnum getWinner() const {
        return winner;
    }

    void setWinner(playerEnum winner) {
        GameStatus::winner = winner;
    }

    playerEnum getLoser() const {
        return loser;
    }

    void setLoser(playerEnum loser) {
        GameStatus::loser = loser;
    }

    void reset();
};


#endif //ADVANCEDTOPICS2_GAMESTATUS_H
