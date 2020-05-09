#include <windows.h>
#include <cmath>
#include <iostream>
#include <GL/glut.h>
using namespace std;

#ifndef A01_SHAPE_H
#define A01_SHAPE_H

static const float PI=3.1415926535;
static const float VELOCITY=0.01;
static const float OMEGA=0.03;

class Vec {
public:
    Vec(float x = 0, float y = 0): x(x), y(y) {};
    ~Vec();
    float getX();
    float getY();
    Vec operator+ (Vec v);
    Vec operator- (Vec v);
    Vec operator* (float k);
    float operator* (Vec v);
    Vec operator<< (float a);
    Vec operator>> (float a);
private:
    float x,y;
};

class Figure {
public:
    Figure() : anchor(0, 0) {}
    ~Figure();
    virtual void setAnchor(const Vec &a) { anchor = a;}
    virtual void draw() {};
    virtual void move(Vec dir);
    virtual void spin(float angle) {};
    virtual void rotate(float angle) {};
    virtual void zoom(float k) {};
protected:
    Vec anchor;
};

class ColoredFig : public Figure{
public:
    ColoredFig():r(0), g(0), b(0){}
    void paint(float ri, float gi, float bi) {
        this->r=ri;
        this->g=gi;
        this->b=bi;
    }
protected:
    float r,g,b;
};

class Quadrangle : public ColoredFig{
public:
    Quadrangle() {};
    Quadrangle(const Vec &vi1, const Vec &vi2, const Vec &vi3, const Vec &vi4):
    v1(vi1), v2(vi2), v3(vi3), v4(vi4) {};
    void draw();
    void rotate(float angle);
    void zoom(float k);
protected:
    Vec v1,v2,v3,v4;
};

class Teleport : public Quadrangle{
public:
    Teleport();
};

class Triangle : public ColoredFig{
public:
    Triangle() {};
    Triangle(Vec v1, Vec v2, Vec v3);
    void draw();
    void rotate(float angle);
    void zoom(float k);
protected:
    Vec v1,v2,v3;
};

class Circle : public ColoredFig{
public:
    Circle(){};
    Circle(Vec o, float r, float rad=2);
    void draw();
    void move(Vec dir){};
    void spin(float angle);
    void rotate(float angle);
    void zoom(float k){};
protected:
    float R,RAD,dA=0;
    Vec O;
};

class Line :public ColoredFig{
public:
    Line() {}
    void set(Vec v1, Vec v2, float _w=1.5, float _r=0.45, float _g=0.45, float _b=0.45);
    void draw();
    void rotate(float a);
private:
    float w;
    Vec v1,v2;
};

class Point: public ColoredFig{
public:
    Point() {s=3;}
    Point(Vec _p, float _s=3, float _r=1, float _g=0, float _b=0);
    void draw();
private:
    Vec p;
    float s;
};

class Group :public Figure {
public:
    Group(){};
    ~Group();
    void setAnchor(Vec a);
    void draw(); // Draw out all its figures
    void move(Vec dir); // Move all its figures
    void rotate(); // Rotate the group as a whole.
    void rotate(float angle);
    void zoom(); // Zoom the group as a whole.

protected:
    int piece;
    ColoredFig* part[20];
};

class Rocket :public Group{
public:
    Rocket();
};

class UFO :public Group{
public:
    UFO();
};


class Car :public Group{
public:
    Car();
    int wheel(float speed);
};

class Parkinglot {
public:
    Parkinglot();
    ~Parkinglot();
    void build();
    void park();
    void parkCar(Car* car, Vec *p);
private:
    int gate(int argu);
    int car_enter(Car* car, Vec *p);
    int car_turn(Car* car, Vec *p, int argu, float R=0.25);
    int car_go(Car* car, Vec *p, float distance);
    int car_stay(Car* car, Vec *p);
    void car_trajectory(Vec *p, int forward=1);
    Line line[20];
    Vec slot[11];
    bool isempty[11];
};

#endif //A01_SHAPE_H