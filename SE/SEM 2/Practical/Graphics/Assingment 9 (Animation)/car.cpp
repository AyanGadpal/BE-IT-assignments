// Auther : Ayan Naresh Gadpal
// Copyright : GNU public libraly

#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
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

void Timer(int);
int angle = 60;

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
    int x = C.x + r * cos(angle * 3.14 / 180);
    int y = C.y + r * sin(angle * 3.14 / 180);
    DDALine(C, Point(x,y));

    glFlush();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // /* SKY */
    // glColor3f(0, 0, 0.9);
    // glBegin(GL_POLYGON);
    // glVertex2f(-250, -100);
    // glVertex2f(250, -100);
    // glVertex2f(250, 250);
    // glVertex2f(-250, 250);
    // glEnd();

    // /* Grass */
    // glColor3f(0, 0.7, 0);
    // glBegin(GL_POLYGON);
    // glVertex2f(-250, -100);
    // glVertex2f(250, -100);
    // glVertex2f(250, -250);
    // glVertex2f(-250, -250);
    // glEnd();

    circle(Pon);

    /* WINDMILL */

    // glColor3f(1, 0.5, 0);
    // glBegin(GL_POLYGON);

    // glEnd();

    glutSwapBuffers();
}
void init()
{
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(-250, 250, -250, 250);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("GADIII");
    glutTimerFunc(1000, Timer, 0);

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
Point rotateAC(Point p1, float angle)
{
    Point result;
    float theta = angle * 3.14159265 / (float)180;
    result.x = p1.x * cos(theta) - p1.y * sin(theta);
    result.y = p1.x * sin(theta) + p1.y * cos(theta);
    return result;
}
void Timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Timer, 0);

}