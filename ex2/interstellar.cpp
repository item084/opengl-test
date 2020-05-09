#include <windows.h>
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include "interstellar.h"


void Figure::move(Vec dir){
    anchor=Vec((anchor+dir).getX(),(anchor+dir).getY());
}

//

Quadrangle::Quadrangle(Vec _v1, Vec _v2, Vec _v3, Vec _v4) {
    v1=_v1; v2=_v2; v3=_v3; v4=_v4;
}

void Quadrangle::draw() {
    glColor3f(r,g,b);
    glBegin( GL_POLYGON );
    glVertex2f( (anchor+v1).getX(), (anchor+v1).getY() );
    glVertex2f( (anchor+v2).getX(), (anchor+v2).getY() );
    glVertex2f( (anchor+v3).getX(), (anchor+v3).getY() );
    glVertex2f( (anchor+v4).getX(), (anchor+v4).getY() );
    glEnd();
}


void Quadrangle::rotate(float a){
    v1=v1<<a;v2=v2<<a;v3=v3<<a;v4=v4<<a;
}

void Quadrangle::zoom(float k){
    v1=v1*k;v2=v2*k;v3=v3*k;v4=v4*k;
}

//

Teleport::Teleport(){
    v1=Vec(0.09,0.13);
    v3=v1*-1;
    v2=Vec(0.09,-0.13);
    v4=v2*-1;
    int i=rand();
    r=(float)rand()/RAND_MAX;
    g=(float)rand()/RAND_MAX;
    b=(float)rand()/RAND_MAX;
};

//

Triangle::Triangle(Vec _v1, Vec _v2, Vec _v3) {
    v1=_v1; v2=_v2; v3=_v3;
}

void Triangle::draw() {

    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f((anchor+v1).getX(),(anchor+v1).getY());
    glVertex2f((anchor+v2).getX(),(anchor+v2).getY());
    glVertex2f((anchor+v3).getX(),(anchor+v3).getY());
    glEnd();
};

void Triangle::rotate(float a){
    v1=v1<<a;v2=v2<<a;v3=v3<<a;
}

void Triangle::zoom(float k){
    v1=v1*k;v2=v2*k;v3=v3*k;
}

//

Circle::Circle(Vec o, float r, float rad){
    R=r;RAD=rad;O=o;
}

void Circle::draw() {
    int n=60;
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(O.getX()+anchor.getX()+R*cos(RAD*PI*i/n+dA), O.getY()+anchor.getY()+R*sin(RAD*PI*i/n+dA));
    }
    glEnd();
    glFlush();
}

void Circle::spin(float angle){
    dA+=angle;
}

void Circle::rotate(float angle){
    dA+=angle;
    O=O<<angle;
};

//

void Line::set(Vec _v1,Vec _v2, float _w, float _r, float _g, float _b){
    v1=_v1;v2=_v2;w=_w;r=_r;g=_g;b=_b;
}

void Line::rotate(float a){
    v1=v1<<a;v2=v2<<a;
}

void Line::draw(){
    glLineWidth(w);
    glBegin(GL_LINES);
    glColor3f(r,g,b);
    glVertex2f((v1+anchor).getX(),(v1+anchor).getY());
    glVertex2f((v2+anchor).getX(),(v2+anchor).getY());
    glEnd();
}

//

Point::Point(Vec _p, float _s, float _r, float _g, float _b){
    p=_p;s=_s;r=_r;g=_g;b=_b;
}

void Point::draw(){
    glColor3f(r,g,b);
    glPointSize(s);
    glBegin(GL_POINTS);
    glVertex2f((p).getX(), (p).getY());
    glEnd();
}

//

Group::~Group(){
    for (int i=0;i<piece;i++){delete part[i];}
};


void Group::setAnchor(Vec a) {
    int i;
    anchor=a;
    for (i=0;i<piece;i++){
        part[i]->setAnchor(a);
    }
}

void Group::draw(){
    int i;
    for (i=0;i<piece;i++){
        part[i]->draw();
    }
}

void Group::move(Vec dir){
    int i;
    anchor=Vec((anchor+dir).getX(),(anchor+dir).getY());
    for (i=0;i<piece;i++){
        part[i]->move(dir);
    }
}

void Group::rotate(){
    float static angle=0;
    angle+=PI/180;
    int i;
    for (i=0;i<piece;i++){
        part[i]->rotate(angle);
    }
}

void Group::rotate(float angle){
    int i;
    for (i=0;i<piece;i++){
        part[i]->rotate(angle);
    }
}

void Group::zoom(){
    int static j=0;
    float static z=1;
    if ((z>=0.5)&&(j==0)) {z*=0.99;}
    else if (z<=1.5) {j=1;z*=1.01;}
    else j=0;
    int i;
    for (i=0;i<piece;i++){
        part[i]->zoom(z);
    }
}

//

Rocket::Rocket(){
    piece=8;

    Vec v01(0,0.15),v02(0.035,0.09),v03(-0.035,0.09);
    part[0]=new Triangle(v01,v02,v03);
    part[0]->paint(102.0/255,178.0/255,102.0/255);

    Vec v11(0.035,0.09),v12(0.035,-0.09),v13=v11*-1,v14=v12*-1;
    part[1]=new Quadrangle(v11,v12,v13,v14);
    part[1]->paint(220.0/255,220.0/255,20.0/255);

    Vec v2(0,0.003);
    Vec v21(0.008,0.013),v22(0.008,-0.013),v23=v21*-1,v24=v22*-1;
    part[2]=new Quadrangle(v21+v2,v22+v2,v23+v2,v24+v2);
    part[2]->paint(0.0/255,173.0/255,238.0/255);

    Vec v3(-0.017,0.05);
    Vec v31(0.006,0.007),v32(0.006,-0.007),v33=v31*-1,v34=v32*-1;
    part[3]=new Quadrangle(v31+v3,v32+v3,v33+v3,v34+v3);
    part[3]->paint(236.0/255,0.0/255,141.0/255);

    Vec v4(0.017,0.05);
    Vec v41(0.006,0.007),v42(0.006,-0.007),v43=v41*-1,v44=v42*-1;
    part[4]=new Quadrangle(v41+v4,v42+v4,v43+v4,v44+v4);
    part[4]->paint(236.0/255,0.0/255,141.0/255);

    Vec v5(-0.035,-0.09);
    Vec v51(0,0),v52(-0.04,0),v53(0,0.08);
    part[5]=new Triangle(v51+v5,v52+v5,v53+v5);
    part[5]->paint(234.0/255,140.0/255,22.0/255);

    Vec v6(0.035,-0.09);
    Vec v61(0,0),v62(0.04,0),v63(0,0.08);
    part[6]=new Triangle(v61+v6,v62+v6,v63+v6);
    part[6]->paint(234.0/255,140.0/255,22.0/255);

    Vec v7(0,-0.09);
    Vec v71(-0.0248,0),v72(0.0248,0),v73(0.0325,-0.022),v74(-0.0325,-0.022);
    part[7]=new Quadrangle(v71+v7,v72+v7,v73+v7,v74+v7);
    part[7]->paint(0,0,0);

};

//

UFO::UFO(){
    piece=5;

    Vec v0(0,0);
    part[0]=new Circle(v0,0.06,1);
    part[0]->paint(0,0,1);

    Vec v1(-0.045,0.062);
    float a=PI*2/7;
    Vec v11(-0.0015,0.02),v12(0.0015,0.02),v13=v11*-1,v14=v12*-1;
    part[1]=new Quadrangle((v11<<a)+v1,(v12<<a)+v1,(v13<<a)+v1,(v14<<a)+v1);
    part[1]->paint(1,155.0/255,53.0/255);

    Vec v2(0.045,0.062);
    Vec v21(-0.0015,0.02),v22(0.0015,0.02),v23=v21*-1,v24=v22*-1;
    part[2]=new Quadrangle((v21>>a)+v2,(v22>>a)+v2,(v23>>a)+v2,(v24>>a)+v2);
    part[2]->paint(1,155.0/255,53.0/255);

    Vec v3(-0.04,0);
    Vec v31(-0.016,0),v32(0.016,0),v33(0.021,-0.019),v34(-0.021,-0.019);
    part[3]=new Quadrangle(v31+v3,v32+v3,v33+v3,v34+v3);
    part[3]->paint(1,241.0/255,0);

    Vec v4(0.04,0);
    Vec v41(-0.016,0),v42(0.016,0),v43(0.021,-0.019),v44(-0.021,-0.019);
    part[4]=new Quadrangle(v41+v4,v42+v4,v43+v4,v44+v4);
    part[4]->paint(1,241.0/255,0);

};

//

Car::Car() {
    piece = 6;

    Vec v0(0,0);
    Vec v01(0.045,0.14),v02(-0.045,0.14),v03=v01*-1,v04=v02*-1;
    part[0]=new Quadrangle(v01+v0,v02+v0,v03+v0,v04+v0);
    part[0]->paint(1,191.0/255,127.0/255);

    Vec v1(-0.045,0);
    Vec v11(-0.07,0.032),v12(-0.07,-0.032),v13(0,-0.1),v14(0,0.1);
    part[1]=new Quadrangle(v11+v1,v12+v1,v13+v1,v14+v1);
    part[1]->paint(127.0/255,127.0/255,255.0/255);

    Vec v2(0.04,0.065);
    part[2]=new Circle(v2,0.025,2);
    part[2]->paint(1,127.0/255,63.0/255);

    Vec v3(0.04,-0.065);
    part[3]=new Circle(v3,0.025,2);
    part[3]->paint(1,127.0/255,63.0/255);

    part[4]=new Circle(v2,0.025,0.5);
    part[4]->paint(0,0,0);

    part[5]=new Circle(v3,0.025,0.5);
    part[5]->paint(0,0,0);
}

int Car::wheel(float speed){
    int i;
    for (i=4;i<=5;i++){
        part[i]->spin(speed);
    }
    return 1;
}

//

Parkinglot::Parkinglot(){
    int i=0;
    slot[0]=Vec(-0.725,-0.85);;
    for (i=0;i<5;i++){
        slot[i+1]=Vec(-0.435+0.22*i,-0.45);
        slot[10-i]=Vec(-0.435+0.22*i,0.45);
        isempty[i+1]=isempty[10-i]=true;
    }
}

Parkinglot::~Parkinglot(){
}

void Parkinglot::build(){
    int i=0;
    line[0].set(Vec(-0.55,-0.6),Vec(0.9,-0.6));
    line[1].set(Vec(-0.9,0.6),Vec(0.9,0.6));
    line[2].set(Vec(-0.9,0.6),Vec(-0.9,-0.68));
    line[3].set(Vec(0.9,0.6),Vec(0.9,-0.6));
    line[4].set(Vec(-0.55,-0.6),Vec(-0.55,-0.68));
    for (i=0;i<6;i++){
        line[5+i].set(Vec(-0.545+0.220*i,-0.35),Vec(-0.545+0.220*i,-0.6),0.3);
        line[11+i].set(Vec(-0.545+0.220*i,0.35),Vec(-0.545+0.220*i,0.6),0.3);
    }
    line[17].setAnchor(Vec(-0.55,-0.68));
    line[17].set(Vec(-0.29,0),Vec(0,0),1.5,1,0.76,0.76);

    for (i=0;i<18;i++){
        line[i].draw();
    }

    Vec v1(0.53,0.055),v2(0.53,-0.055),v3=v1*-1,v4=v2*-1;
    Quadrangle block(v1,v2,v3,v4);
    block.paint(0.44,0.44,0.44);
    block.draw();
}

void Parkinglot::park(){
    int i;
    bool static initialized=false;
    int static num = rand() % 3 + 4;
    int static  guests[10][3];
    if (!initialized) {
        int pos=rand()%10+1,type;
        for (i = 0; i < num; i++) {
            if (i<=2) type=i+1;
            else type = rand() % 3 + 1;
            while (!isempty[pos]) { pos = rand() % 10 + 1; }
            isempty[pos] = false;
            guests[i][1]=type;
            guests[i][2]=pos;
        }
        initialized=true;
    }
    for (i = 0; i < num; i++) {
        switch (guests[i][1]){
            case 1:{
                Teleport t;
                t.setAnchor(slot[guests[i][2]]);
                t.draw();
                break;
            }
            case 2:{
                Rocket r;
                r.setAnchor(slot[guests[i][2]]);
                r.zoom();
                r.draw();
                break;
            }
            case 3:{
                UFO u;
                u.setAnchor(slot[guests[i][2]]);
                u.rotate();
                u.draw();
                break;
            }
            default:break;
        }
    }
}


void Parkinglot::parkCar(Car* car, Vec *posi){
    int static step=0;
    int static pos = rand() % 10 + 1;
    bool static parked=false;
    if (!parked) {
        while (!isempty[pos]) { pos = rand() % 10 + 1; }
        parked=true;
    }

    Vec p = slot[pos];
    Point position(p,6);
    position.draw();

    if (pos<6) {
        if (step <= 2) { car_trajectory(posi); } else car_trajectory(posi, 0);
        switch (step) {
            case 0:
                gate(1);
                if (car_enter(car, posi)) step++;
                break;
            case 1:
                gate(-1);
                if (car_turn(car, posi, 4)) step++;
                break;
            case 2:
                if (car_go(car, posi, 0.305 + (pos - 1) * 0.22)) step++;
                break;
            case 3:
                (*car).wheel(2 * VELOCITY / 0.025);
                if (car_turn(car, posi, -4, 0.25)) step++;
                break;
            default:
                car_stay(car, posi);
                break;
        }
        car_stay(car, posi);

    }

    else {
        if (step<=5) {car_trajectory(posi);} else car_trajectory(posi,0);
        switch (step) {
            case 0:
                gate(1);
                if (car_enter(car, posi)) step++;
                break;
            case 1:
                gate(-1);
                if (car_turn(car, posi, 4)) step++;
                break;
            case 2:
                if (car_go(car, posi, 1.01)) step++;
                break;
            case 3:
                if (car_turn(car, posi, -2, 0.19)) step++;
                break;
            case 4:
                if (car_turn(car, posi, -1, 0.19)) step++;
                break;
            case 5:
                if (car_go(car, posi, -0.36 - (pos - 6) * 0.22)) step++;
                break;
            case 6:
                (*car).wheel(2 * VELOCITY / 0.025);
                if (car_turn(car, posi, -2)) step++;
                break;
            default:
                car_stay(car, posi);
                break;
        }
        car_stay(car, posi);

    }
};

int Parkinglot::gate(int argu){
    float static ang=0;
    if (argu==1) {
        ang+=0.0285;
        line[17].set(Vec(-0.29,0)<<-ang,Vec(0,0),1.5,1,0,0);
        line[17].draw();
    }
    else {
        ang-=0.030;
        line[17].set(Vec(-0.29,0)<<-ang,Vec(0,0),1.5,1,0,0);
        line[17].draw();
    }
    return 1;
}

int Parkinglot::car_enter(Car* car, Vec *p){

    if ((*p).getY()>-0.45) {
        Vec d(0,-0.45-(*p).getY());
        (*car).setAnchor(*p+d);
        return 1;
      }
    else {
        Vec d(0,VELOCITY);

        (*car).setAnchor(*p);
        (*car).wheel(-VELOCITY/0.025);

        *p=*p+d;

        return 0;
    }
}

int Parkinglot::car_go(Car* car, Vec *p, float dis) {
    float static moved=0;
    int sym=1;
    if (dis<0) {sym=-1;dis=-dis;}
    if (moved>dis) {
        Vec d(sym*(dis-moved),0);
        *p = *p + d;
        moved=0;
        return 1;
    }
    else{
        (*car).setAnchor(*p);
        (*car).wheel(-VELOCITY/0.025);

        Vec d(sym*VELOCITY, 0);
        *p = *p + d;
        moved+=VELOCITY;

        return 0;
    }
}

int Parkinglot::car_turn(Car* car, Vec *p, int argu, float r) {//clockwise +
    float static angle=0;
    float R=r;
    int sym=1;
    if (argu<0) {sym=-1;argu=-argu;}
    if (angle>PI/2) {
        (*car).rotate(sym*(angle-PI/2));
        angle=0;
        return 1;
    }
    else{
        (*car).setAnchor(*p);
        (*car).rotate(sym*(-OMEGA));
        (*car).wheel(-VELOCITY/0.025);

        angle+=OMEGA;

        float dD=R*OMEGA,dx,dy;
        dx=sin(angle+PI/2*argu)*dD;
        dy=cos(angle+PI/2*argu)*dD;
        if (sym<0){
            dx=-cos(angle-PI/2*argu)*dD;
            dy=-sin(angle-PI/2*argu)*dD;
        }
        Vec d(dx,dy);
        *p = *p + d;
        return 0;
    }
}

int Parkinglot::car_stay(Car* car, Vec *p){
    (*car).setAnchor(*p);
    (*car).draw();
}

void Parkinglot::car_trajectory(Vec *posi, int forward) {
    int static i = 0, t = 0;
    Vec static tra[2000];
    tra[0] =Vec(0, 0);

    if ((*posi).getX() != tra[i].getX() || (*posi).getY() != tra[i].getY()) {
        i++;
        tra[i] = *posi;
    }

    int j;

    if (forward) {
        t=i;
        for (j = 1; j <= i; j++) {
            Point blue(tra[j],3,0,0,1);
            blue.draw();
        }
    }
    else{
        for (j = 1; j < t; j++) {
            Point blue(tra[j],3,0,0,1);
            blue.draw();
        }
        for (j = t; j <= i; j++) {
            Point red(tra[j],3);
            red.draw();
        }
    }

}