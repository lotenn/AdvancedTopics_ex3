//
// Created by root on 6/7/18.
//

#ifndef ADVANCEDTOPICS3_RSPPLAYER_204540710_H
#define ADVANCEDTOPICS3_RSPPLAYER_204540710_H

#include "PlayerAlgorithm.h"


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

class RSPPlayer_204540710: public PlayerAlgorithm{
private:
    playerEnum player;
    PossiblePieces knownBoard[N][M][2];

public:
    RSPPlayer_204540710();
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
	
//	void printKnownBoard();

};




#endif //ADVANCEDTOPICS3_RSPPLAYER_204540710_H
