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





string getWinnerString(playerEnum player);

//***********************Game Manager*****************************************************

class GameManager {
private:
    unique_ptr<PlayerAlgorithm> player1;
    unique_ptr<PlayerAlgorithm> player2;
    BoardImp board;
    vector<shared_ptr<Piece>> player1Pieces;
    vector<shared_ptr<Piece>> player2Pieces;
    int player1Score;
    int player2Score;
    playerEnum currentPlayer;
    FightInfoImp fightInfo;
    GameStatus gameStatus;


public:
    GameManager(playerMode player1Mode, playerMode player2Mode);

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

    void raisePlayerScore(int score, playerEnum player);

    bool badPositioningFile(endGameReason reason);

    bool badMovesFile(endGameReason reason);

    bool badInputFile(endGameReason reason);

    string getBadInputFileMessage(endGameReason reason);

    void printBadInputFile();

    string getReasonString();

    void endGame();

    void generateOutputFile(const char *outputFilePath, string winner, string reason, string board);

    static bool parsePlayerModes(char* commandLine, playerMode& player1mode, playerMode& player2mode);

    };


#endif //ADVANCEDTOPICS2_GAMEMANAGER_H
