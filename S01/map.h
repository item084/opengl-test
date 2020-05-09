#include <windows.h>
#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

#ifndef S01_MAP_H
#define S01_MAP_H

class Vec {
public:
    Vec(): x(0), y(0), z(0) {};
    Vec(float x, float y, float z = 0): x(x), y(y), z(z) {};
    ~Vec(){};
    float getX();
    float getY();
    float getZ();
    Vec operator+ (Vec v);
    Vec operator- (Vec v);
    Vec operator* (float k);
    float operator* (Vec v);
    Vec operator<< (float a); // horizontal
    Vec operator>> (float a); // horizontal
private:
    float x,y,z;
};

class Figure {
public:
    Figure() : anchor(0, 0, 0) {}
    ~Figure(){};
    virtual void setAnchor(const Vec &a) { anchor = a;}
    virtual void draw() {};
    virtual void draw(int t) {};
    virtual void move(const Vec &dir);
    virtual void spin(float angle) {};
    virtual void rotate(float angle) {};
    virtual void zoom(float k) {};
protected:
    Vec anchor;
};

class ColoredFig : public Figure{
public:
    ColoredFig():r(0), g(0), b(0), a(1){}
    void paint(float ri, float gi, float bi, float ai = 0) {
        this->r=ri;
        this->g=gi;
        this->b=bi;
        this->a=ai;
    }
protected:
    float r = 0, g = 0, b = 0, a = 1;
};

class Rect: public ColoredFig {
public:
    Rect(){};
    Rect(const Vec &v1, const Vec &v2, const Vec &v3, const Vec &v4):
            v1(v1), v2(v2), v3(v3), v4(v4) {};
    void draw();
    void draw(int t);
    //void draw(int l, int a);
    void rotate(float angle);
    void zoom(float k) { return; };
protected:
    Vec v1, v2, v3, v4;
};


class Cube: public ColoredFig {
public:
    Cube(){};
    Cube(float l, float w, float h);
    void draw();
    void rotate(float angle) { return; };
    void zoom(float k) { return; };
    void move(const Vec &dir);
protected:
    float l,w,h;
    Rect face[6];
};

class Car: public ColoredFig {
public:
    Car();
    void draw();
    void rotate(float angle) { return; };
    void zoom(float k) { return; };
    void move(Vec &dir);
    void spin(float angle);
protected:
    float l,w,h;
    Vec head;
    Rect face[6];
};

#endif //S01_MAP_H
