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
void DDALINE(Point A, Point B)
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

void renderDisplay()
{
    float r = 100;
    circle(Point(0,0),200);
    glColor3f(1,1,1);
    
    glFlush();
}


int main(int agrc, char **argv)
{
    glutInit(&agrc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Pattern");
    init();
   
    glutDisplayFunc(renderDisplay);

    //glutTimerFunc(1000,Timer,0); // DONT UNCOMMENT IT
    glutMainLoop();
    return 0;
}