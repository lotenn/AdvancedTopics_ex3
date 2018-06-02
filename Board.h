//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_BOARD_H
#define ADVANCEDTOPICS2_BOARD_H

#include "PiecePosition.h"

#define M 10
#define N 10

class Board {
public:
    virtual int getPlayer(const Point& pos) const=0; // 1 for player 1’s piece, 2 for 2, 0 if empty
    virtual ~Board() {}
};

class BoardImp : public Board{
private:
    shared_ptr<Piece> board[N][M];
    shared_ptr<Piece> emptyPiece;

public:
    BoardImp(): emptyPiece(move(make_shared<EmptyPiece>())){}
    void clearBoard();
    int getPlayer(const Point& pos) const override {
        return playerEnumToInt(board[PointUtils::getRow(pos)][PointUtils::getCol(pos)]->getPlayer());
    }
    shared_ptr<Piece>& getEmptyPiece(){return emptyPiece;}
    shared_ptr<Piece> getPiece(const Point& point){
        int row = PointUtils::getRow(point), col = PointUtils::getCol(point);
        return board[row][col];
    }
    void setPiece(const Point& point, shared_ptr<Piece> piece){
        int row = PointUtils::getRow(point), col = PointUtils::getCol(point);
        board[row][col] = piece;
    }
    string boardToString();
};


#endif //ADVANCEDTOPICS2_BOARD_H
