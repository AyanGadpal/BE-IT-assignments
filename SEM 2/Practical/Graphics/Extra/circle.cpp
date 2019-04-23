#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;
int theta=60;

void Timer(int);
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
void init()
{
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-250, 250, -250, 250);
}

void putPixel(Point A)
{
    glBegin(GL_POINTS);
    glVertex2f(A.x, A.y);
    glEnd();
}

void circle(Point C, int r)
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

void renderDisplay()
{
    int r = 100;
    int r2 = r / 2;
glClear(GL_COLOR_BUFFER_BIT);
    circle(Point(0, 0), r);
    circle(Point(0, 0), r2);
    int x, y;
    x = r * cos(theta * 3.14 / 180);
    y = r * sin(theta * 3.14 / 180);
    circle(Point(-x, y), r2);

    circle(Point(x, y), r2);

     circle(Point(x, -y), r2);
     
     circle(Point(-x, -y), r2);
 
     x = r * sin((theta+30) * 3.14 / 180);
    y = r * cos((theta+30) * 3.14 / 180);
    circle(Point(x, y), r2);
    circle(Point(-x, y), r2);

    glutSwapBuffers();
}

int main(int agrc, char **argv)
{
    glutInit(&agrc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Pattern");
    init();
    glutDisplayFunc(renderDisplay);
    //glutTimerFunc(1000,Timer,0); // DONT UNCOMMENT IT
    glutMainLoop();
    return 0;
}
// void Timer(int t) // I SAID DONT!
// {
//     glutPostRedisplay();
//     glutTimerFunc(1000 / 60, Timer, 0);
//     theta++;
// }