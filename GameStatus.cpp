#include "GameStatus.h"

void GameStatus::reset(){
    this->setGameOn();
    this->setMainReason(NO_REASON);
    this->setReason1(NO_REASON);
    this->setReason2(NO_REASON);
    this->setWinner(NO_PLAYER);
    this->setLoser(NO_PLAYER);
}