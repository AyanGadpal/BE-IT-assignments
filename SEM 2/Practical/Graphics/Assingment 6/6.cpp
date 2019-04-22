// Auther : Ayan Naresh Gadpal
// Copyright :  GNU public libraly
// Usage : Plot Polygon by left click and complete it by right click and rotate it by 
//          mouse wheel


#include <iostream>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <math.h>
#include <queue>
#define PI 3.14159265

using namespace std;
class Point;
queue<Point> in;
int w, h;
int mode = 0;
bool flag = true;
class Point
{
public:
    GLfloat x, y;

    Point() { x = y = 0; }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point negate()
    {
        return Point(-x, -y);
    }
};
dnyan
Point S, E, T;

void DDALine(Point A, Point B)
{
    GLfloat dx, dy, steps;
    dx = B.x - A.x;
    dy = B.y - A.y;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    GLfloat x, y, xi, yi;

    xi = dx / steps;
    yi = dy / steps;

    x = A.x;
    y = A.y;
    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++)
    {
        glVertex2i(x, y);
        x += xi;
        y += yi;
    }
    glEnd();
    glFlush();
}

Point rotateAC(Point p1, float angle)
{
    Point result;
    float theta = angle * PI / (float)180;
    result.x = p1.x * cos(theta) - p1.y * sin(theta);
    result.y = p1.x * sin(theta) + p1.y * cos(theta);
    return result;
}

Point rotateC(Point p1, float angle)
{
    Point result;
    float theta = angle * PI / (float)180;
    result.x = p1.x * cos(theta) + p1.y * sin(theta);
    result.y = -p1.x * sin(theta) + p1.y * cos(theta);
    return result;
}

Point scaling(Point p1,int sf)
{
    return Point(p1.x * sf, p1.y * sf);
}
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    w = glutGet(GLUT_WINDOW_WIDTH);
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}
void myMouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag)
    {
        flag = false;

        S.x = x - w / 2;
        S.y = h / 2 - y;
        in.push(S);
        T = S;
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        E.x = x - w / 2;
        E.y = h / 2 - y;
        in.push(E);
        DDALine(S, E);
        S = E;
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        DDALine(S, T);
        in.push(T);
    }
  
        if (btn == 3 || btn == 4) // WHEEL UP / DOWN
        {
            Point P, S, E, T;
            int cx = 0, cy = 0;
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1, 0, 0);
            DDALine(Point(-w / 2, 0), Point(w / 2, 0)); // X
            glColor3f(0, 0, 1);
            DDALine(Point(0, -h / 2), Point(0, h / 2)); // Y
            glColor3f(0, 0, 0);
            bool fl = true;
            int limit = in.size();
            for (int i = 0; i < limit; i++)
            {

                P = in.front();
                in.pop();
                if (btn == 3 )
                    P = rotateAC(P, 2); // UP
                if (btn == 4 )
                    P = rotateC(P, 2); // DOWN
                
                // if (btn == 3 && mode == 2)
                //     P = scaling(P, 1); // UP
                // if (btn == 4 && mode == 2)
                //     P = scaling(P, -1); // DOWN

                if (fl)
                {
                    S = P;
                    in.push(P);
                    fl = false;
                }
                else
                {
                    E = P;
                    DDALine(S, E);
                    S = E;
                    in.push(P);
                }

            }

            DDALine(Point(0, 0), Point(cx, cy));
            glFlush();
        }
}
void display()
{
    glColor3f(1, 0, 0);
    DDALine(Point(-w / 2, 0), Point(w / 2, 0)); // X
    glColor3f(0, 0, 1);
    DDALine(Point(0, -h / 2), Point(0, h / 2)); // Y
    glColor3f(0, 0, 0);                         // Reset to Black

    glFlush();
}
void menu(int choice)
{
    mode = choice;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("TRANSFORMATION");
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    // glutCreateMenu(menu);
    // glutAddMenuEntry("Rotation ", 1);
    // glutAddMenuEntry("Scale ", 2);
    // glutAttachMenu(GLUT_MIDDLE_BUTTON);
    init();
    glutMainLoop();
    return 0;
}
