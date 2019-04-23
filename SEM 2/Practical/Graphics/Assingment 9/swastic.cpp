// Auther : Ayan Naresh Gadpal
// Copyright : GNU public libraly


#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
void Timer(int);
class Point
{
public:
    GLfloat x, y;
    Point()
    {
        x = y = 0;
    }
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Point neg() // Negate the points and return
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
Point rotateAC(Point p1, float angle)
{
    Point result;
    float theta = angle * 3.14159265 / (float)180;
    result.x = p1.x * cos(theta) - p1.y * sin(theta);
    result.y = p1.x * sin(theta) + p1.y * cos(theta);
    return result;
}

int size = 100; // HEIGHT OF SW
int dis = 30;   // DISTANCE B/W TWO CENTERS

Point                       /*INITIAL REQ CENTRALS*/
    CTL(-dis / 2, dis / 2), // CENTRAK TOP LEFT
    CTR(dis / 2, dis / 2);  // CENTRAK TOP RIGHT

Point /*TOP HAND*/
    T1(CTL.x, size),
    T2(size, size),
    T3(size, size - dis),
    T4(dis / 2, size - dis);
;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 4; i++)
    {

        DDALine(CTL, T1);
        DDALine(T1, T2);
        DDALine(T2, T3);
        DDALine(T3, T4);
        DDALine(T4, CTR);

        /* ROTATE THE WHOLE HAND BY 90*/
        CTR = CTL; // OBIVIOUS
        CTL = rotateAC(CTL, 90);
        T1 = rotateAC(T1, 90);
        T2 = rotateAC(T2, 90);
        T3 = rotateAC(T3, 90);
        T4 = rotateAC(T4, 90);
    }

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
    glutCreateWindow("HELLO");
    glutTimerFunc(1000, Timer, 0);

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void Timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Timer, 0);

    CTR = rotateAC(CTR, 1);
    CTL = rotateAC(CTL, 1);
    T1 = rotateAC(T1, 1);
    T2 = rotateAC(T2, 1);
    T3 = rotateAC(T3, 1);
    T4 = rotateAC(T4, 1);
}