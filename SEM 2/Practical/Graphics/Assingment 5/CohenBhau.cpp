// Auther : Ayan Naresh Gadpal
// Copyright : GNU public library

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

using namespace std;
const int INSIDE = 0; //0000
const int LEFT = 1;   //0001
const int RIGHT = 2;  //0010
const int BOTTOM = 4; //0100
const int TOP = 8;    //1000

int xmin, xmax, ymin, ymax, Mode = 0;
bool flag = true;
class Point
{
public:
    float x, y;
    Point()
    {
        x = y = 0;
    }
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};
Point B, T, BR, TL, S, E;
void DDALine(Point A, Point B)
{
    float dx = B.x - A.x;
    float dy = B.y - A.y;
    float step = 0;
    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
    float xi = dx / step;
    float yi = dy / step;
    float x = A.x, y = A.y;
    glBegin(GL_POINTS);
    for (int i = 0; i < step; i++)
    {
        glVertex2f(x, y);
        x += xi;
        y += yi;
    }
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-300, 300, -300, 300);
}
void reset()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DDALine(B, TL);
    DDALine(BR, T);
    DDALine(T, TL);
    DDALine(B, BR);

    /* For Simplicity */

    xmin = B.x < T.x ? B.x : T.x;
    xmax = T.x > B.x ? T.x : B.x;
    ymin = B.y < T.y ? B.y : T.y;
    ymax = T.y > B.y ? T.y : B.y;
   
}
void renderDisplay()
{

    glEnd();
    glFlush();
}
int code(Point A)
{
    int c = 0;      // Center
    if (A.y > ymax) // 1000 A
        c = 8;
    if (A.y < ymin) // 0100 B
        c = 4;
    if (A.x > xmax) // 0010 R
        c = c | 2;
    if (A.x < xmin) // 0001 L
        c = c | 1;
    return c;
}
void cohenLine()
{
    int scode, ecode;
    scode = code(S);
    ecode = code(E);
    float m = (E.x - S.x) / (E.y - S.y);
    int x, y;
    int c;
    

    while ((scode | ecode) != 0)
    {
        
        if ((scode & ecode) != 0)
            return;
        // Means Partically in
        c = (scode == 0) ? ecode : scode;
        if (c & TOP)
        {
            y = ymax;
            x = S.x + ((y - S.y) * m);
        }
        else if (c & BOTTOM)
        {
            y = ymin;
            x = S.x + ((y - S.y) * m);
        }
        else if (c & RIGHT)
        {
            x = xmax;
            y = S.y + (x - S.x) * m;
        }
        else if (c & LEFT)
        {
            x = xmin;
            y = S.y + (x - S.x) * m;
        }
        if (scode == 0)
        {
            E.x = x;
            E.y = y;
            ecode = code(E);
        }
        else
        {
            S.x = x;
            S.y = y;
            scode = code(S);
        }
    }
}
void motion(int x, int y)
{
    x = x - 300;
    y = 300 - y;
    if (Mode == 1)
    {
        if (flag)
        {
            flag = false;
            B.x = x;
            B.y = y;
        }
        else
        {
            T.x = x;
            T.y = y;
            TL.x = B.x;
            TL.y = T.y;
            BR.x = T.x;
            BR.y = B.y;
            reset();
        }
    }

    if (Mode == 2)
    {
        if (flag)
        {
            flag = false;
            S.x = x;
            S.y = y;
        }
        else
        {
            E.x = x;
            E.y = y;
            reset();

        }
    }
}
void pas(int x, int y)
{
    flag = true;
    if (Mode == 2)
    {
        cout << "\n xmin : "<<xmin<<"\n xmax : "<<xmax<<"\n ymin : "<<ymin<<"\n ymax : "<<ymax;
        cohenLine();
        DDALine(S, E);
    }
}

void menu(int choice)
{
    Mode = choice;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Cohen Line Clipping");
    init();
    // glutMouseFunc();
    glutCreateMenu(menu);
    glutAddMenuEntry("1) Window", 1);
    glutAddMenuEntry("2) Line", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMotionFunc(motion); //Callback for Mouse motion with any button pressed
    glutPassiveMotionFunc(pas);
    glutDisplayFunc(renderDisplay);
    glutMainLoop();
    return 0;
}