#include <windows.h>
#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

#ifndef S01_SHAPE_H
#define S01_SHAPE_H


static float vertex_list[][3] =
        {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
        };

static float angle = 0;
static float front = 0;



void keyboard(unsigned char key, int x, int y);

void DrawCube(void);

static float rotate = 0;
static int times = 0;

void renderScene(void);

#endif //S01_SHAPE_H
