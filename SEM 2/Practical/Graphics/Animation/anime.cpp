#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>

using namespace std;
class Point;
void display();

void reshape(int, int);

void Timer(int);

void BCircle(Point, int);

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
void putPixel(Point P)
{
    glBegin(GL_POINTS);
    glVertex2i(P.x, P.y);
    glEnd();
}

float x = -10;
Point C = {0, 2};
bool flag = true;

void Init()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Animation");
    glutDisplayFunc(display); // Display CallBack
    glutReshapeFunc(reshape); // This is called whenever windows is reshape
    glutTimerFunc(1000, Timer, 0);
    Init();
    glutMainLoop();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); // RESET ALL CURRENT MATRIX
    glColor3f(0.0, 0.0, 1.0);
    int r = 5;
    Point p;
    p.x = 0;
    p.y = r; //radius
    putPixel(C);
    putPixel(Point(p.x + C.x, p.y + C.y));

    float Pi = 3 - 2 * r;

    while (p.x <= p.y)
    {
        if (Pi < 0)
        {
            p.x++;
            Pi += 4 * p.x + 6;
        }
        else
        {
            p.x++;
            p.y--;
            Pi += 4 * (p.x - p.y) + 16;
        }

        putPixel(Point(C.x + p.x, C.y + p.y));
        putPixel(Point(C.x + p.y, C.y + p.x));
        putPixel(Point(C.x + p.y, C.y - p.x));
        putPixel(Point(C.x + p.x, C.y - p.y));
        putPixel(Point(C.x - p.x, C.y - p.y));
        putPixel(Point(C.x - p.y, C.y - p.x));
        putPixel(Point(C.x - p.y, C.y + p.x));
        putPixel(Point(C.x - p.x, C.y + p.y));
    }

    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void Timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Timer, 0);

    if (flag)
    {
        x += 0.15;
        if (x > 8.0)
            flag = false;
    }
    else
    {
        x -= 0.15;
        if (x < -10)
            flag = true;
    }
}

void BCircle(Point C, int r)
{
    Point p;
    p.x = 0;
    p.y = r;
    putPixel(C);
    putPixel(Point(p.x + C.x, p.y + C.y));

    float Pi = 3 - 2 * r;

    while (p.x <= p.y)
    {
        if (Pi < 0)
        {
            p.x++;
            Pi += 4 * p.x + 6;
        }
        else
        {
            p.x++;
            p.y--;
            Pi += 4 * (p.x - p.y) + 16;
        }

        putPixel(Point(C.x + p.x, C.y + p.y));
        putPixel(Point(C.x + p.y, C.y + p.x));
        putPixel(Point(C.x + p.y, C.y - p.x));
        putPixel(Point(C.x + p.x, C.y - p.y));
        putPixel(Point(C.x - p.x, C.y - p.y));
        putPixel(Point(C.x - p.y, C.y - p.x));
        putPixel(Point(C.x - p.y, C.y + p.x));
        putPixel(Point(C.x - p.x, C.y + p.y));
    }
}z