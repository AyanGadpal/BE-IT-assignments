// Auther : Ayan Naresh Gadpal
// Copyright : GNU public libraly
// Usage : Use left click to give Points of the Polygon , Right click to close the Polygon
// Note : The SHPC algorithm is in myMouse(), Thought output may look like line clipping, but 
//        its purely (maybe not Purly) SHPC algo
// REFERENCE: https://www.cs.helsinki.fi/group/goa/viewing/leikkaus/intro2.html

#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
using namespace std;
class Point;
int x1, y1, x2, y2, xmin = -100, ymin = -100, xmax = 100, ymax = 100;

bool flag = true;
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
Point T, S, E;

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

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-400, 400, -400, 400);
}

void myMouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag)
    {
        S.x = x - 400;
        S.y = 400 - y;
        cout << "\n X1 : " << x1 << " Y1: " << y1;
        flag = false;
        T = S;
    }
    else if ((btn == GLUT_LEFT_BUTTON || btn == GLUT_RIGHT_BUTTON) && state == GLUT_DOWN)
    {
        int nx, ny;
        E.x = x - 400;
        E.y = 400 - y;
        x1 = S.x;
        y1 = S.y;
        if (btn == GLUT_LEFT_BUTTON)
        {
            x2 = E.x;
            y2 = E.y;
        }
        else
        {
            x2 = T.x;
            y2 = T.y;
            flag = true;
        }

        cout << "\n X2 : " << x2 << " Y2: " << y2;
        float slope = (float)(y2 - y1) / (float)(x2 - x1);

        /* Left Clipping */
        if (x1 > xmin || x2 > xmin)
        {
            if (x2 < x1)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;
                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            if (x1 < xmin) // Find Intersection
            {
                ny = y1;
                nx = x1;
                y1 = slope * (xmin - x2) + y2;
                x1 = xmin;
                glColor3f(0, 1, 0);
                DDALine(Point(nx, ny), Point(x1, y1));
                glColor3f(0, 0, 0);
            }
        }

        /* Right Clipping */
        if (x1 < xmax || x2 < xmax)
        {
            if (x1 > x2)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;
                temp = y1;
                y1 = y2;
                y2 = temp;
            }

            if (x2 > xmax)
            {
                nx = x2;
                ny = y2;
                y2 = slope * (xmax - x1) + y1;
                x2 = xmax;

                glColor3f(0, 1, 0);
                DDALine(Point(x1, y1), Point(nx, ny));
                glColor3f(0, 0, 0);
            }
        }

        /* Top Clipping */
        if (y1 < ymax || y2 < ymax)
        {
            if (y2 < y1)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;
                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            if (y2 > ymax)
            {
                nx = x2;
                ny = y2;
                x2 = x1 + (ymax - y1) / slope;
                y2 = ymax;
                glColor3f(0, 1, 0);
                DDALine(Point(x2, y2), Point(nx, ny));
                glColor3f(0, 0, 0);
            }
        }

        /* Bottom Clipping */

        if (y2 > ymin || y1 > ymin)
        {
            if (y2 < y1)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;
                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            if (y1 < ymin)
            {
                ny = y1;
                nx = x1;
                y1 = ymin;
                x1 = x2 + (ymin - y2) / slope;
                glColor3f(0, 1, 0);
                DDALine(Point(x1, y1), Point(nx, ny));
                glColor3f(0, 0, 0);
            }
        }
        if (x1 >= xmin && x2 <= xmax && y2 <= ymax && y1 >= ymin)
        {
            DDALine(Point(x1, y1), Point(x2, y2));
        }
        else
        {
            glColor3f(0, 1, 0);
            DDALine(Point(x1, y1), Point(x2, y2));
            glColor3f(0, 0, 0);
        }

        S = E;
    }
}

void display()
{
    glColor3f(0.0f, 0.0f, 0.0f);

    glPointSize(2);
    DDALine(Point(xmax, -400), Point(xmax, 400)); // Right
    DDALine(Point(xmin, -400), Point(xmin, 400)); // Left
    DDALine(Point(-400, ymax), Point(400, ymax)); // TOP
    DDALine(Point(-400, ymin), Point(400, ymin)); // BOTTOM

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}