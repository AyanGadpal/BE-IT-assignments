// Auther : Ayan Naresh Gadpal
// Copyright : GNU public libraly

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;

class Point;
void DDALine(Point, Point);
void checkBox(Point, Point, Point, Point);
void cross(Point, Point, Point, Point, int); // Bottom,Top,Density of lines

class Point
{
public:
    int x, y;
    Point()
    {
        x = y = 0;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

Point rotate(Point p1, float angle)
{
    Point result;
    float theta = angle * PI / 180;
    result.x = p1.x * cos(theta) - p1.y * sin(theta);
    result.y = p1.x * sin(theta) + p1.y * cos(theta);
    return result;
}

Point translate(Point p,int tra)
{

}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-320.0f, 320.0f, -320.0f, 320.0f);
}

void display()
{

    Point B(0, 0), TL(0, 200), T(200, 200), BR(200, 0);
    checkBox(B,TL,T,BR);

    B = rotate(B,45);
    T = rotate(T,45);
    BR = rotate(BR,45);
    TL = rotate(TL,45);

    glColor3f(1.0f, 0.0f, 0.0f);
    checkBox(B,TL,T,BR);

    glFlush();
}

void mouseEventListener(int button, int state, int x, int y)
{
    
}

void checkBox(Point B, Point TL, Point T, Point BR)
{
    DDALine(B, TL);
    DDALine(B, BR);

    DDALine(TL, T);
    DDALine(BR, T);

    cross(B, TL, T, BR, 3); // Bottom , Top ,Intensity
}

void cross(Point B, Point TL, Point T, Point BR, int l)
{
    int x1 = (B.x + BR.x) / 2;
    int y1 = (B.y + BR.y) / 2;
    Point verticalA(x1, y1);
    int x2 = (TL.x + T.x) / 2;
    int y2 = (TL.y + T.y) / 2;
    Point verticalB(x2, y2);

    x1 = (B.x + TL.x) / 2;
    y1 = (B.y + TL.y) / 2;
    Point horizontalA(x1, y1);
    x2 = (BR.x + T.x) / 2;
    y2 = (BR.y + T.y) / 2;
    Point horizontalB(x2, y2);

    x1 = (B.x + T.x) / 2;
    y1 = (B.y + T.y) / 2;
    Point mid(x1, y1);

    if (l > 0)
    {
        DDALine(verticalA, verticalB);     // ^
        DDALine(horizontalA, horizontalB); // >
        l--;
        cross(B, horizontalA, mid, verticalA, l);
        cross(horizontalA,TL,verticalB,mid, l);
        cross(mid,verticalB,T,horizontalB, l);
        cross(verticalA,mid,horizontalB,BR, l);
    }
    else
    {
        return;
    }
}

void DDALine(Point p1, Point p2)
{
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;

    GLfloat step = 0;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    GLfloat xInc = dx / step;
    GLfloat yInc = dy / step;

    glBegin(GL_POINTS);
    for (float i = 1; i <= step; i++)
    {
        glVertex2i(x1, y1);
        x1 += xInc;
        y1 += yInc;
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("CHESS");
    glutDisplayFunc(display);
    glutMouseFunc(mouseEventListener);
    init();
    glutMainLoop();
    return 0;
}
