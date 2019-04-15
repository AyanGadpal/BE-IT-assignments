#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>

using namespace std;
void init();
class Point;
void circle(Point, int);
void Timer(int);

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
int r = 60, i = 1;
Point C = {-350 + r, 0};

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluOrtho2D(-350, 350, -350, 350);
}

void myDisplay()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    circle(C, r);

    glFlush();
}

void circle(Point c, int r)
{
    Point t;
    int d; //Decision Parameter
    t.x = 0;
    t.y = r;
    d = 3 - 2 * r; // intial Decision Parameter
    glBegin(GL_POINTS);
    glVertex2i(t.x, t.y);
    glVertex2i(t.x, t.y + c.y);

    while (t.x < t.y)
    {
        if (d < 0)
        {
            t.x++;
            d += 4 * t.x + 6;
        }
        else
        {
            t.x++;
            t.y--;
            d += 4 * (t.x - t.y) + 16;
        }
        glVertex2i(t.x + c.x, t.y + c.y);
        glVertex2i(-t.x + c.x, t.y + c.y);
        glVertex2i(-t.x + c.x, -t.y + c.y);
        glVertex2i(t.x + c.x, -t.y + c.y);
        glVertex2i(t.y + c.x, t.x + c.y);
        glVertex2i(-t.y + c.x, t.x + c.y);
        glVertex2i(-t.y + c.x, -t.x + c.y);
        glVertex2i(t.y + c.x, -t.x + c.y);
    }

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
    glutTimerFunc(1000 / 200, Timer, 0);

    C.x += i;
    if (C.x == 350 - r)
        i = -1;
    if (C.x == -350 + r)
        i = 1;
}
