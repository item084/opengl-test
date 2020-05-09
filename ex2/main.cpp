#include <windows.h>
#include <GL/glut.h>
#include "interstellar.h"
#include <ctime>
#include <cmath>
void TimeStep(int n) {
  glutTimerFunc(25, TimeStep, 0); glutPostRedisplay();
}
void glDraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //

    srand(time(0));

    Parkinglot p;
    p.build();
    p.park();

    Car static car;
    Vec static posi(-0.725,-1);

    p.parkCar(&car,&posi);

    //
    glutSwapBuffers();
    glFlush();
    }
int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Interstellar Parking lot!");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw);
    //gluOrtho2D(-10, 10, -10, 10);
    glutTimerFunc(25, TimeStep, 0);
    glutMainLoop();
}