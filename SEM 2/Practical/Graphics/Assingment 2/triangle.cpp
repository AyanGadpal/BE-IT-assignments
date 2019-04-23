#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;
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
Point S, E, T;
void putPixel(Point A)
{
    glBegin(GL_POINTS);
    glVertex2f(A.x, A.y);
    glEnd();
}
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

void circle(Point C, float r)
{
    Point P(0, r);
    float pi = 3 - 2 * r;
    putPixel(Point(P.x + C.x, P.y + C.y));
    putPixel(C);
    while (P.x <= P.y)
    {
        if (pi < 0)
        {
            P.x++;
            pi += 4 * P.x + 6;
        }
        else
        {
            P.x++;
            P.y--;
            pi += 4 * (P.x - P.y) + 16;
        }

        putPixel(Point(P.x + C.x, P.y + C.y));
        putPixel(Point(-P.x + C.x, P.y + C.y));
        putPixel(Point(-P.x + C.x, -P.y + C.y));
        putPixel(Point(P.x + C.x, -P.y + C.y));
        putPixel(Point(-P.y + C.x, P.x + C.y));
        putPixel(Point(-P.y + C.x, -P.x + C.y));
        putPixel(Point(P.y + C.x, -P.x + C.y));
        putPixel(Point(P.y + C.x, P.x + C.y));
    }

    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-250, 250, -250, 250);
}
void circleMod(Point C,float r)
{
    circle(C, r);
    circle(C, r / 2);
    int x, y;
    x = C.x+r * cos(30 * 3.14 / 180);
    y = C.y;
    DDALine(Point(C.x, C.y + r), Point(-x,y -r / 2));
    DDALine(Point(C.x, C.y+r), Point(x,  - r / 2));
    DDALine(Point(C.x-x,C.y+ y - r / 2), Point(x,  - r / 2));
}
void renderDisplay()
{
    float r = 100;
    
    glFlush();
}

void motion(int x, int y)
{
    x = x - 250;
    y = 250 - y;
    if (flag)
    {
        S.x = x;
        S.y = y;
        flag = false;
    }
    else
    {
        E.x = x;
        E.y = y;
        cout << endl
             << x << " " << y;
        glClear(GL_COLOR_BUFFER_BIT);
        circleMod(Point(0, 0), E.x);
    }
}
int main(int agrc, char **argv)
{
    glutInit(&agrc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Pattern");
    init();
     glutMotionFunc(motion);
    glutDisplayFunc(renderDisplay);

    //glutTimerFunc(1000,Timer,0); // DONT UNCOMMENT IT
    glutMainLoop();
    return 0;
}