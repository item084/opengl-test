#include <windows.h>
#include <cmath>
#include <iostream>
#include <GL/glut.h>
using namespace std;
static const float PI=3.1415926535;
static const float VELOCITY=0.01;
static const float OMEGA=0.03;

class Vec {
    public:
    Vec() {x=y=0;}
    Vec(float _x, float _y) {
        x = _x; y = _y;
    }
    ~Vec() {}
    float getX() {return x;}
    float getY() {return y;}
    //void setVec(float _x, float _y) {x=_x; y=_y;}

    // Example Overloads + operator
    // returns the sum of 2 Vec
    Vec operator+ (Vec v) {
        return (Vec(x + v.getX(), y + v.getY()));
    }
    // Overload - on 2 Vectors
    // return thier difference Vector
    Vec operator- (Vec v) {
        return (Vec(x - v.getX(), y - v.getY()));
    }
    // Overload * operator on a float k
    // return current Vector scaled by k
    Vec operator* (float k) {
        return (Vec(x*k, y*k));
    }
    // Overload * on 2 Vectors
    // return their inner product (scaler product)
    float operator* (Vec v) {
        return (x*v.getX()+y*v.getY());
    }
    // Overload << on an angle
    // return current vector rotated counter clockwise
    // by this angle
    Vec operator<< (float a) {
        return (Vec(
            x*cos(a)-y*sin(a),
            x*sin(a)+y*cos(a)
        ));
    }
    // Overload >> on an angle
    // return current vector rotated clockwise
    // by this angle
    Vec operator>> (float a) {
        return (Vec(
            x*cos(a)+y*sin(a),
            -x*sin(a)+y*cos(a)
        ));
    }
    private:
    float x,y;
};

class Figure {
    public:
    Figure() : anchor(0, 0) {}
    ~Figure() {}
    virtual void setAnchor(Vec a) {anchor = a;}
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
    ColoredFig(){r=g=b=0;}
    void paint(float _r, float _g, float _b) {
        r=_r; g=_g; b=_b;
    }
    protected:
      float r,g,b;
};

class Quadrangle : public ColoredFig{
    public:
      Quadrangle() {};
      Quadrangle(Vec v1, Vec v2, Vec v3, Vec v4);
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