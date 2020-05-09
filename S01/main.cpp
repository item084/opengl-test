#include <windows.h>
#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include "shape.h"

using namespace std;

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.5f,-0.5f, 0.5f, 0.5f);
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D not so hard");


    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(&keyboard);
    glutMainLoop();
    return 0;
}