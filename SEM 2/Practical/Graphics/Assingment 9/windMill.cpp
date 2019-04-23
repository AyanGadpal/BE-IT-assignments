// Auther : Ayan Naresh Gadpal
// Copyright : GNU public libraly

#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;

void Timer(int);
float x = 215 - 100, y = 185 - 100; //width - height (works somhow)

class Point
{
public:
    GLfloat x, y;
    Point()
    {
        x = y = 0;
    }
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Point neg() // Negate the points and return
    {
        return Point(-x, -y);
    }
};
Point A1(x, y), A2(y, x),
    B1(-x, y), B2(-y, x),
    C1(-x, -y), C2(-y, -x),
    D1(x, -y), D2(y, -x);

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* SKY */
    glColor3f(0, 0, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(-250, -100);
    glVertex2f(250, -100);
    glVertex2f(250, 250);
    glVertex2f(-250, 250);
    glEnd();

    /* Grass */
    glColor3f(0, 0.7, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-250, -100);
    glVertex2f(250, -100);
    glVertex2f(250, -250);
    glVertex2f(-250, -250);
    glEnd();

    /* Stand */
    glColor3f(0.6, 0.4, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-10, 0);
    glVertex2f(10, 0);
    glVertex2f(10, -230);
    glVertex2f(-10, -230);

    glEnd();

    /* WINDMILL */

    glColor3f(1, 0.5, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(A1.x, A1.y);
    glVertex2f(A2.x, A2.y);
    glVertex2f(0, 0);
    glVertex2f(B1.x, B1.y);
    glVertex2f(B2.x, B2.y);
    glVertex2f(0, 0);
    glVertex2f(C1.x, C1.y);
    glVertex2f(C2.x, C2.y);
    glVertex2f(0, 0);
    glVertex2f(D1.x, D1.y);
    glVertex2f(D2.x, D2.y);
    glEnd();

    glutSwapBuffers();
}
void init()
{
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(-250, 250, -250, 250);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("HELLO");
    glutTimerFunc(1000, Timer, 0);

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
Point rotateAC(Point p1, float angle)
{
    Point result;
    float theta = angle * 3.14159265 / (float)180;
    result.x = p1.x * cos(theta) - p1.y * sin(theta);
    result.y = p1.x * sin(theta) + p1.y * cos(theta);
    return result;
}
void Timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Timer, 0);

    A1 = rotateAC(A1, 1);
    A2 = rotateAC(A2, 1);
    B1 = rotateAC(B1, 1);
    B2 = rotateAC(B2, 1);
    C1 = rotateAC(C1, 1);
    C2 = rotateAC(C2, 1);
    D1 = rotateAC(D1, 1);
    D2 = rotateAC(D2, 1);
}