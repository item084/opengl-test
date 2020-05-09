//
// Created by Yao on 8/8/2019.
//

#include "map.h"

float Vec::getX() {
    return x;
}

float Vec::getY() {
    return y;
}

float Vec::getZ() {
    return z;
}


Vec Vec::operator+ (Vec v) {
    return Vec(x + v.getX(), y + v.getY(), z + v.getZ());
}

Vec Vec::operator- (Vec v) {
    return Vec(x - v.getX(), y - v.getY(), z - v.getZ());
}

Vec Vec::operator* (float k) {
    return Vec(x*k, y*k, z*k);
}

float Vec::operator* (Vec v) {
    return x*v.getX()+y*v.getY();
}

Vec Vec::operator<< (float a) {
    return Vec(
            x*cos(a)-y*sin(a),
            x*sin(a)+y*cos(a),
            z
    );
}

Vec Vec::operator>> (float a) {
    return Vec(
            x*cos(a)+y*sin(a),
            -x*sin(a)+y*cos(a),
            z
    );
}

void Figure::move(const Vec &dir) {
    anchor = anchor + dir;
}

void Rect::draw() {
    const float x = anchor.getX();
    const float y = anchor.getY();
    const float z = anchor.getZ();

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glEnable(GL_BLEND);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex3f(x + v1.getX(), y + v1.getY(), z + v1.getZ());
    glVertex3f(x + v2.getX(), y + v2.getY(), z + v2.getZ());
    glVertex3f(x + v3.getX(), y + v3.getY(), z + v3.getZ());
    glVertex3f(x + v4.getX(), y + v4.getY(), z + v4.getZ());
    glEnd();
    //glDisable(GL_BLEND);
}

void Rect::draw(int t) {
    const float x = anchor.getX();
    const float y = anchor.getY();
    const float z = anchor.getZ();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glColor4f(r, g, b, a);
    glBegin(GL_POLYGON);
    glVertex3f(x + v1.getX(), y + v1.getY(), z + v1.getZ());
    glVertex3f(x + v2.getX(), y + v2.getY(), z + v2.getZ());
    glVertex3f(x + v3.getX(), y + v3.getY(), z + v3.getZ());
    glVertex3f(x + v4.getX(), y + v4.getY(), z + v4.getZ());
    glEnd();
    glDisable(GL_BLEND);

    if (!t) {
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex3f(x + v1.getX(), y + v1.getY(), z + v1.getZ());
        glVertex3f(x + v2.getX(), y + v2.getY(), z + v2.getZ());
        glVertex3f(x + v3.getX(), y + v3.getY(), z + v3.getZ());
        glVertex3f(x + v4.getX(), y + v4.getY(), z + v4.getZ());
        glEnd();
    }
}

void Rect::rotate(float angle) {
    v1 = v1<<angle;
    v2 = v2<<angle;
    v3 = v3<<angle;
    v4 = v4<<angle;
}

Cube::Cube(float l, float w, float h):
        l(l), w(w), h(h) {
    const float x = anchor.getX();
    const float y = anchor.getY();
    const float z = anchor.getZ();

    float s[3] = {1, 1, 1};
    float sign[4] = {1, 1, 0 , 0};
    Vec temp[4];

    int cnt = 0;

    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 2; j++) {
            s[0] = 1 - 2 * (j%2);
            for (int k = 0; k < 4; k++) {
                s[1] = 1 - 2 * sign[k];
                s[2] = 1 - 2 * sign[(k + 1) % 4];
                temp[k] = Vec(x + s[i] * l / 2, y + s[(i + 1) % 3] * w / 2, z + s[(i + 2) % 3] * h / 2);
            }
            face[cnt].setAnchor(anchor);
            face[cnt++] = Rect(temp[0], temp[1], temp[2], temp[3]);
        }
    }

}

void Cube::draw() {
    const float x = anchor.getX();
    const float y = anchor.getY();
    const float z = anchor.getZ();

    float s[3] = {1, 1, 1};
    float sign[4] = {1, 1, 0 , 0};


    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);

    for (auto & i : face) {
        i.paint(r, g, b, a);
        i.draw(1);
    }

    /*
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 2; j++) {
            s[0] = 1 - 2 * (j%2);
            glColor4f(r, g, b, a);
            glBegin(GL_POLYGON);
            for (int k = 0; k < 4; k++) {
                s[1] = 1 - 2 * sign[k];
                s[2] = 1 - 2 * sign[(k + 1) % 4];
                //cout << x + s[i] * l / 2 << " " << y + s[(i + 1) % 3] * w / 2 << " " << z + s[(i + 2) % 3] * h / 2 << endl;
                glVertex3f(x + s[i] * l / 2, y + s[(i + 1) % 3] * w / 2, z + s[(i + 2) % 3] * h / 2);
            }
            glEnd();
        }
    }


    glDisable(GL_BLEND);
    */




    glEnable(GL_DEPTH_TEST);
    glColor4f(0, 1, 0, 1);
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 2; j++) {
            glColor3f(0, 0, 0);
            glBegin(GL_LINES);
            s[0] = 1 - 2 * (j%2);
            for (int k = 0; k < 4; k++) {
                s[1] = 1 - 2 * sign[k];
                s[2] = 1 - 2 * sign[(k + 1) % 4];
                glVertex3f(x + s[i] * l / 2, y + s[(i + 1) % 3] * w / 2, z + s[(i + 2) % 3] * h / 2);
                s[1] = 1 - 2 * sign[(k + 1) % 4];
                s[2] = 1 - 2 * sign[(k + 2) % 4];
                glVertex3f(x + s[i] * l / 2, y + s[(i + 1) % 3] * w / 2, z + s[(i + 2) % 3] * h / 2);
            }
            glEnd();
        }
    }
    glDisable(GL_DEPTH_TEST);
}

void Cube::move(const Vec &dir) {
    anchor = anchor + dir;
    for (auto & i : face) {
        i.move(dir);
    }
}

Car::Car():l(1), w(1), h(1), head(Vec(0, 1, 0)){
    const float x = anchor.getX();
    const float y = anchor.getY();
    const float z = anchor.getZ();

    float s[3] = {1, 1, 1};
    float sign[4] = {1, 1, 0 , 0};
    Vec temp[4];

    int cnt = 0;

    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 2; j++) {
            s[0] = 1 - 2 * (j%2);
            for (int k = 0; k < 4; k++) {
                s[1] = 1 - 2 * sign[k];
                s[2] = 1 - 2 * sign[(k + 1) % 4];
                temp[k] = Vec(x + s[i] * l / 2, y + s[(i + 1) % 3] * w / 2, z + s[(i + 2) % 3] * h / 2);
            }
            face[cnt].setAnchor(anchor);
            face[cnt++] = Rect(temp[0], temp[1], temp[2], temp[3]);
        }
    }

}

void Car::draw() {
    const float x = anchor.getX();
    const float y = anchor.getY();
    const float z = anchor.getZ();

    float s[3] = {1, 1, 1};
    float sign[4] = {1, 1, 0 , 0};


    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);

    for (auto & i : face) {
        i.paint(r, g, b, a);
        if (&i == face + 4) {
            face[4].paint(1, 0, 0, 0.5);
            i.draw();
        } else {
            i.draw(1);
        }
        i.draw(0);
    }
}

void Car::move(Vec &dir) {
    anchor = anchor + (head * dir.getX());
    for (auto & i : face) {
        i.move(head * dir.getX());
    }
    //cout << dir.getX()<<endl;
}

void Car::spin(float angle) {
    head = head<<angle;
    for (auto & i : face) {
        i.rotate(angle);
    }
    //cout << head.getX() << " " << head.getY() << endl;
}