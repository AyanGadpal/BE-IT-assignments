// Auther : Ayan Naresh Gadpal
// Copyright : GNU public libraly

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;

class Point;                                 // Well, for coordinates x,y
void DDALine(Point, Point);                  // Starting point ,ending point
void checkBox(Point, Point, Point, Point);   // Bottom,Top_left,Top,Bottom_Right
void cross(Point, Point, Point, Point, int); // Bottom,Top_left,Top,Bottom_Right,Density
Point midPoint(Point, Point);                // Returns the Midpoint of given two Point

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
    Point neg() // Negate the points and return
    {
        return Point(-x, -y);
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

Point translate(Point p, Point t)
{
    return Point(p.x + t.x, p.y + t.y);
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

    Point B(0, 0), TL(0, 200), T(200, 200), BR(200, 0); // coordinates
    //checkBox(B, TL, T, BR);  //Original chess Box

    Point mid = midPoint(B, T); // Centroid

    /* Translate its center to origin, if you want to rotate around its center */
    B = translate(B, mid.neg());
    BR = translate(BR, mid.neg());
    T = translate(T, mid.neg());
    TL = translate(TL, mid.neg());

    // NOW ROTATEEEEE!!!
    B = rotate(B, 45);
    T = rotate(T, 45);
    BR = rotate(BR, 45);
    TL = rotate(TL, 45);

    //Translate back to its orignal position, but with rotated coordinates ! ^_^
    B = translate(B, mid);
    BR = translate(BR, mid);
    T = translate(T, mid);
    TL = translate(TL, mid);

    // Change color and display rotated chessbox
    glColor3f(1.0f, 0.0f, 0.0f);
    checkBox(B, TL, T, BR);

    glFlush();
}

void mouseEventListener(int button, int state, int x, int y)
{
}

void checkBox(Point B, Point TL, Point T, Point BR)
{
    // DRAW BAKSAA
    DDALine(B, TL);
    DDALine(B, BR);
    DDALine(TL, T);
    DDALine(BR, T);

    cross(B, TL, T, BR, 2); // Bottom , Top ,Intensity! (Factorial maybe)
}

Point midPoint(Point A, Point B)
{
    return Point((A.x + B.x) / 2, (A.y + B.y) / 2);
}

void cross(Point B, Point TL, Point T, Point BR, int l)
{
    // For Vetrical Partition
    Point verticalA = midPoint(B, BR);
    Point verticalB = midPoint(TL, T);

    // For Horizontal Partition
    Point horizontalA = midPoint(B, TL);
    Point horizontalB = midPoint(BR, T);

    Point mid = midPoint(B, T);

    if (l > 0) // To control level of recurstion
    {
        DDALine(verticalA, verticalB);     // ↕
        DDALine(horizontalA, horizontalB); // ↔
        l--;

        // Recursive Pass All 4 new small boxes to cross
        cross(B, horizontalA, mid, verticalA, l); 
        cross(horizontalA, TL, verticalB, mid, l);
        cross(mid, verticalB, T, horizontalB, l);
        cross(verticalA, mid, horizontalB, BR, l);
    }
    else
        return; // well return
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
