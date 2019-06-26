#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>

using namespace std;
void init();
class Point;
void circle(Point, int);

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
    circle(Point(0, 0), 100);

    glFlush();
}

void circle(Point c, int r)
{
    Point t;
    int d; //Decision Parameter
    t.x = c.x;
    t.y = c.y + r;
    d = 3 - 2 * r; // intial Decision Parameter
    glBegin(GL_POINTS);
    glVertex2i(t.x, t.y);

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
        glVertex2i(t.x, t.y);
        glVertex2i(-t.x, t.y);
        glVertex2i(-t.x, -t.y);
        glVertex2i(t.x, -t.y);
        glVertex2i(t.y, t.x);
        glVertex2i(-t.y, t.x);
        glVertex2i(-t.y, -t.x);
        glVertex2i(t.y, -t.x);
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
    glutCreateWindow("CHESS");
    glutDisplayFunc(myDisplay);
    init();
    glutMainLoop();
    return 0;
}
