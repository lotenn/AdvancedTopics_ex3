//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_JOKERCHANGE_H
#define ADVANCEDTOPICS2_JOKERCHANGE_H
#include "Point.h"
#define NO_JOKER_CHANGE_SYMBOL '#'

class JokerChange {
public:
    virtual const Point& getJokerChangePosition() const=0;
    virtual char getJokerNewRep() const=0; // R, P, S or B (but NOT J and NOT F)
    virtual ~JokerChange() {}
};

class JokerChangeImp: public JokerChange{
private:
    unique_ptr<Point> jokerChangePosition;
    char jokerNewRep;
public:
    JokerChangeImp(int x, int y, char _jokerNewRep):
            jokerChangePosition(make_unique<PointImp>(x,y)),
            jokerNewRep(_jokerNewRep){}

    const Point& getJokerChangePosition() const override{
        return *(this->jokerChangePosition);
    }

    char getJokerNewRep() const override{
        return this->jokerNewRep;
    }
};


#endif //ADVANCEDTOPICS2_JOKERCHANGE_H
