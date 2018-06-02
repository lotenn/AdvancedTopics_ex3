#ifndef ADVANCEDTOPICS2_POINT_H
#define ADVANCEDTOPICS2_POINT_H

#include <iostream>
#include <memory>
using namespace std;

class Point {
public:
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual ~Point() {}
};

class PointImp: public Point{
private:
    int x;
    int y;

public:
    PointImp(int _x, int _y): x(_x), y(_y){}
    int getX() const override {return x;}
    int getY() const override {return y;}
};


class PointUtils{
public:
    static int getCol(const Point& point){return point.getX()-1;}
    static int getRow(const Point& point){return point.getY()-1;}
};

#endif //ADVANCEDTOPICS2_POINT_H
