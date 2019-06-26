#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

using namespace std;
void init();
class Point;
void circle(Point, float);
void Timer(int);
float angle = 60;
int a = -350, b = -200;
class Point
{
public:
    float x, y;
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
int r = 60, i = 1;
Point C = {-370 + r, 0};

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluOrtho2D(-350, 350, -350, 350);
}
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
    for (int i = 0; i < 360;i+=30)
    {
        int x = C.x + r * cos(angle +i * 3.14 / 180);
        int y = C.y + r * sin(angle +i* 3.14 / 180);
        DDALine(C, Point(x, y));
    }

    // DDALine(C, Point(x,y));
    // DDALine(C, Point(x,y));

    glFlush();
}
void myDisplay()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    circle(C, 28);
    circle(Point(C.x + 60, C.y), 28);

    glBegin(GL_POLYGON);
    glVertex2f(a, 28);
    glVertex2f(b, 28);
    glVertex2f(b, 130);
    glVertex2f(a, 130);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Wheel");
    glutDisplayFunc(myDisplay);
    glutTimerFunc(1000, Timer, 0);
    init();
    glutMainLoop();
    return 0;
}
void Timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 100, Timer, 0);

    C.x += i;
    angle += i;
    a += i;
    b += i;
    if (C.x == 330 - r)
        i = -1;
    if (C.x == -350 + r)
        i = 1;
}
