#ifndef ADVANCEDTOPICS2_MOVE_H
#define ADVANCEDTOPICS2_MOVE_H

#include "JokerChange.h"

class Move {
public:
    virtual const Point& getFrom() const = 0;
    virtual const Point& getTo() const = 0;
    virtual ~Move() {}
};

class MoveImp: public Move{
private:
    unique_ptr<Point> from;
    unique_ptr<Point> to;

public:
    MoveImp(int fromX, int fromY, int toX, int toY):
            from(make_unique<PointImp>(PointImp(fromX, fromY))),
            to(make_unique<PointImp>(PointImp(toX, toY))){}

    const Point& getFrom() const override {return *(this->from);}
    const Point& getTo() const override {return *(this->to);}
};


#endif //ADVANCEDTOPICS2_MOVE_H
