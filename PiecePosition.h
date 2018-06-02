#ifndef ADVANCEDTOPICS2_PIECEPOSITION_H
#define ADVANCEDTOPICS2_PIECEPOSITION_H

#include <iostream>
#include <memory>
#include "Piece.h"

using namespace std;

class PiecePosition{
public:
    virtual const Point& getPosition() const = 0;
    virtual char getPiece() const = 0; // R, P, S, B, J or F
    virtual char getJokerRep() const = 0; // ONLY for Joker: R, P, S or B -- non-Joker may return ‘#’
    virtual ~PiecePosition() {}
};

class PiecePositionImp: public PiecePosition{
private:
    unique_ptr<Point> position;
    char piece;
    char jokerRep;

public:
    PiecePositionImp(int x, int y, char _piece, char _jokerRep):
            position(make_unique<PointImp>(x,y)),
            piece(_piece),
            jokerRep(_jokerRep) {}

    const Point& getPosition() const override {
        return *(this->position.get());
    }

    char getPiece() const override {    // R, P, S, B, J or F
        return this->piece;
    }

    char getJokerRep() const override {  // ONLY for Joker: R, P, S or B -- non-Joker may return ‘#’
        return this->jokerRep;
    }
};

#endif //ADVANCEDTOPICS2_PIECEPOSITION_H
