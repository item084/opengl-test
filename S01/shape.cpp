//
// Created by Yao on 8/8/2019.
//

#include "shape.h"
#include "map.h"

void DrawCube(void)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    //glBegin(GL_LINES);
    glColor4f(1, 0, 0, 0.5);


    glBegin(GL_POLYGON);
    glVertex3fv(vertex_list[0]);
    glVertex3fv(vertex_list[2]);
    glVertex3fv(vertex_list[6]);
    glVertex3fv(vertex_list[4]);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3fv(vertex_list[1]);
    glVertex3fv(vertex_list[3]);
    glVertex3fv(vertex_list[7]);
    glVertex3fv(vertex_list[5]);
    glEnd();


    glDisable(GL_BLEND);

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for(int i=0; i<12; ++i) // 12 条线段

    {
        for(int j=0; j<2; ++j) // 每条线段 2个顶点

        {
            //glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            angle = 6.00/180;
            //xyz[0] = xyz[2] = 0;
            break;
        case 'd':
        case 'D':
            angle = -6.00/180;
            //xyz[0] = xyz[2] = 0;
            break;
        case 'w':
        case 'W':
            front = 0.1;
            //xyz[1] = xyz[2] = 0;
            break;
        case 's':
        case 'S':
            front = -0.1;
            //xyz[1] = xyz[2] = 0;
            break;
        default:
            angle = 0;
            front = 0;
            break;
    }
    printf("Move to the %c direction\n", key);
    glutPostRedisplay();
}

void renderScene(void)
{
    //glDepthMask(GL_FALSE);
    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    glClearColor(0.6, 0.6, 0.6, 0.6);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluPerspective(100.0, (GLfloat) 600/(GLfloat) 600, 0.01, 20.0);
    float s =2.5;
    gluLookAt(0,-s,s,0,0,0,0,1,1); // Look at


    glScalef(1, 1, 1);

    glPushMatrix();


    //glTranslatef(-0.2, 0, 0); // 平移
    //glRotatef(angle, xyz[0], xyz[1], xyz[2]);


    //DrawCube();

    float l = 3, w = 1.5;
    Rect static road(Vec(l, w), Vec(-l, w), Vec(-l, -w), Vec(l, -w));
    road.paint(0.3, 0.3, 0.3);
    road.draw();

    //Cube road(8, 5 , 0.1);
    //road.paint(0.3, 0.3, 0.3);
    //road.draw();
    //Cube static cube(1,1,1);
    //cube.paint(0.6, 0, 0, 1);
    //cube.move(Vec(0, front));
    //front = 0;
    //cube.draw();

    Car static car;
    car.paint(1, 1, 0, 0.2);
    Vec vFront(front, front, front);
    car.move(vFront);
    front = 0;
    car.spin(angle);
    angle = 0;
    car.draw();

    glPopMatrix();
    glutSwapBuffers();
}

