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
#include "Parser.h"

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

class FilePlayerAlgorithm: public PlayerAlgorithm{
private:
    vector<unique_ptr<Move>> moves;
    vector<unique_ptr<JokerChange>> jokerChanges;
    playerEnum player;
    int currentMove;
    int currentJokerChange;

public:
    FilePlayerAlgorithm(playerEnum _player):player(_player), currentMove(0), currentJokerChange(0){}

    unique_ptr<Move> getMove() override {
        //no more moves
        //moves file was not parsed yet
        if(currentMove==0)
            this->getMoves();
        if(currentMove == (int)moves.size()){
            return make_unique<MoveImp>(INVALID_COORD,INVALID_COORD,INVALID_COORD,INVALID_COORD);
        }
        return move(moves[currentMove++]);
    }

    unique_ptr<JokerChange> getJokerChange() override  {
        if(currentJokerChange == (int)jokerChanges.size()){
            return make_unique<JokerChangeImp>(INVALID_COORD,INVALID_COORD,INVALID_CHAR);
        }
        return move(jokerChanges[currentJokerChange++]);
    }

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;

    void getMoves();

    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override {
        //nonsense - to use the unused parameter
        if(b.getPlayer(PointImp(1,1)) && !fights.empty()){
            return;
        }
    };

    void notifyOnOpponentMove(const Move& move) override {
        //nonsense - to use the unused parameter
        if(move.getTo().getX() >0){
            return;
        }
    }; // called only on opponent’s move

    void notifyFightResult(const FightInfo& fightInfo) override {
        //nonsense - to use the unused parameter
        if(fightInfo.getWinner()==NO_PLAYER){
            return;
        }
    }; // called only if there was a fight
};

class PossiblePieces {
private:
    playerEnum player;
    possiblePieceType possiblePiece;
    bool optFlag;
    bool isJoker;

public:

    bool IsJoker() const {
        return isJoker;
    }

    void setIsJoker(bool isJoker) {
        PossiblePieces::isJoker = isJoker;
    }

    playerEnum getPlayer() const {
        return player;
    }

    void setPlayer(playerEnum player) {
        PossiblePieces::player = player;
    }

    possiblePieceType getPossiblePiece() const {
        return possiblePiece;
    }

    void setPossiblePiece(possiblePieceType possiblePiece) {
        PossiblePieces::possiblePiece = possiblePiece;
    }

    bool isOptFlag() const {
        return optFlag;
    }

    void setOptFlag(bool isMovable) {
        PossiblePieces::optFlag = isMovable;
    }

    void reset(){
        this->player = NO_PLAYER;
        this->possiblePiece = pEMPTY;
        this->optFlag = false;
        this->isJoker = false;
    }

    bool canMove();
};

class AutoPlayerAlgorithm: public PlayerAlgorithm{
private:
    playerEnum player;
    PossiblePieces knownBoard[N][M][2];

public:
    AutoPlayerAlgorithm(playerEnum _player): player(_player){resetKnownBoard();}
    void resetKnownBoard();
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    void notifyOnOpponentMove(const Move& move) override; // called only on opponent’s move
    void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
    unique_ptr<Move> getMove() override;
    unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
    void getPossibleTargets(const PointImp& point, vector<PointImp>& targetsToFill, bool jokerChange);
    void performPlayerMove(const PointImp &from, const PointImp &to);
    bool canCapture(possiblePieceType playerPiece, possiblePieceType opponentPiece);
    vector<pieceType> getKnownWeakerPieces(pieceType playerPiece) const;
    possiblePieceType getJokerRepStrongerThan(const possiblePieceType &threatType) const;
};


#endif //ADVANCEDTOPICS2_PLAYERALGORITHM_H
