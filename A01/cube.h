//
// Created by Yao on 8/8/2019.
//
#include <windows.h>
#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

#ifndef A01_CUBE_H
#define A01_CUBE_H

// 将立方体的八个顶点保存到一个数组里面

static const float vertex_list[][3] =
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

// 将要使用的顶点的序号保存到一个数组里面

static const GLint index_list[][2] =
        {
                {0, 1},
                {2, 3},
                {4, 5},
                {6, 7},
                {0, 2},
                {1, 3},
                {4, 6},
                {5, 7},
                {0, 4},
                {1, 5},
                {7, 3},
                {2, 6}
        };

// 绘制立方体

void DrawCube(void)
{
    int i,j;

    glBegin(GL_LINES);
    for(i=0; i<12; ++i) // 12 条线段

    {
        for(j=0; j<2; ++j) // 每条线段 2个顶点

        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

static float rotate = 0;
static int times = 0;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glTranslatef(-0.2, 0, 0); // 平移

    glScalef(2, 1, 1);    // 缩放


    times++;
    if(times > 100)
    {
        times = 0;
    }

    if(times % 100 == 0)
    {
        rotate += 0.3;
    }

    glRotatef(rotate, 0, 1, 0);
    glRotatef(rotate, 1, 0, 0);

    glColor3f(1, 0, 0);

    DrawCube();

    glPopMatrix();
    glutSwapBuffers();
}


#endif //A01_CUBE_H
