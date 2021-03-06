//
// Created by loten on 30/04/2018.
//

#ifndef ADVANCEDTOPICS2_GAMEMANAGER_H
#define ADVANCEDTOPICS2_GAMEMANAGER_H

#include <map>
#include <memory.h>
#include "PlayerAlgorithm.h"
#include "EnumUtils.h"

#define NUM_OF_R 2
#define NUM_OF_P 5
#define NUM_OF_S 1
#define NUM_OF_B 2
#define NUM_OF_J 2
#define NUM_OF_F 1
#define MAX_TURNS_WITH_NO_FIGHTS 100

//***********************Game Manager*****************************************************

class GameManager {
private:
    unique_ptr<PlayerAlgorithm> player1;
    unique_ptr<PlayerAlgorithm> player2;
    BoardImp board;
    vector<shared_ptr<Piece>> player1Pieces;
    vector<shared_ptr<Piece>> player2Pieces;
    playerEnum currentPlayer;
    FightInfoImp fightInfo;
    GameStatus gameStatus;

public:
    GameManager(unique_ptr<PlayerAlgorithm> _player1, unique_ptr<PlayerAlgorithm> _player2);

    const GameStatus &getGameStatus() const {
        return gameStatus;
    }

    void validatePositioningVector(playerEnum player, vector<unique_ptr<PiecePosition>>&  piecePositions);

    void setPlayerPieces(const vector<unique_ptr<PiecePosition>> &piecePositions, playerEnum player,
                                      vector<unique_ptr<FightInfo>>& fights);
    bool performBattle(const Point& point, shared_ptr<Piece> source, shared_ptr<Piece> target);

    bool executeMove(unique_ptr<Move> move);

    void executeJoker(unique_ptr<JokerChange> jokerChange);

    void initGame();

    bool containsMovingPieces(vector<shared_ptr<Piece>>& playerPieces);

    bool containsFlags(vector<shared_ptr<Piece>>& playerPieces);

    void positioningStage();

    void positioningCheckGameEnd();

    void moveStage();

};

#endif //ADVANCEDTOPICS2_GAMEMANAGER_H
