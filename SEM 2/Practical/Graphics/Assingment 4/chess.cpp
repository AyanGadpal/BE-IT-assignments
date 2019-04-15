// Auther : Ayan N Gadpal
// Copyright : GNU public libraly
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;

class Point;
void DDALine(Point, Point);
void checkBox(Point, Point);
void cross(Point, Point, int); // Bottom,Top,Density of lines

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

// int rotatex(int x, int y, double angle)
// {
// 	return x*cos( angle * PI / 180.0 ) - y*sin( angle * PI / 180.0 );
// }

// int rotatey(int x, int y, double angle)
// {
// 	return x*sin( angle * PI / 180.0 ) + y*cos( angle * PI / 180.0 );
// }

// int translatex(int x, int tx)
// {
// 	return x - tx;
// }

// int translatey(int y, int ty)
// {
// 	return y - ty;
// }

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-320.0f, 320.0f, -320.0f, 320.0f);
}

void display()
{
    // int x = rotatex(200, 200, 45);
    // int y = rotatex(200, 200, 45);
    
    checkBox(Point(-0,-0), Point(200, 200));

    glFlush();
}

void mouseEventListener(int button, int state, int x, int y)
{
}

void checkBox(Point B, Point T)
{
    Point TL, BR;
    TL = Point(B.x, T.y);
    BR = Point(T.x, B.y);

    DDALine(B, TL);
    DDALine(B, BR);

    DDALine(TL, T);
    DDALine(BR, T);

    cross(B, T, 3); // Bottom , Top ,Intensity

}

void cross(Point B, Point T, int l)
{
    int mx = B.x + T.x;
    int my = B.y + T.y;
    int nx = mx / 2;
    int ny = my / 2;
    if (l > 0)
    {
        DDALine(Point(nx, B.y), Point(nx, T.y)); // ^
        DDALine(Point(B.x, ny), Point(T.x, ny)); // >
        l--;
        cross(B,Point(nx,ny),l);
        cross(Point(B.x, ny), Point(nx, T.y), l);
        cross(Point(nx,ny),T,l);
        cross(Point(nx,B.y),Point(T.x,ny),l);
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
    {
        step = abs(dx);
    }
    else
    {
        step = abs(dy);
    }

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
