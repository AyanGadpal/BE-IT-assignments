#include <GL/freeglut.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>

#define PI 3.142857143

using namespace std;

float P[4][3] = {0},
      T[3][3], result[4][3];

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

void mult()
{
    int i, j, k;
    int sum;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
        {
            sum = 0;
            for (k = 0; k < 3; k++)
                sum = sum + P[i][k] * T[k][j];
            result[i][j] = sum;
        }
}

void rotate()
{
    float rx, ry, angle, rad;

    angle = 60;
    rad = angle * (PI / 180);

    T[0][0] = cos(rad);
    T[0][1] = sin(rad);
    T[0][2] = 0;
    T[1][0] = -sin(rad);
    T[1][1] = cos(rad);
    T[1][2] = 0;
    T[2][0] = 0;
    T[2][1] = 0;
    T[2][2] = 1;
    mult();
}
void DDALine(Point p1, Point p2)
{
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;

    GLfloat step = 0;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    GLfloat xInc = dx / step;
    GLfloat yInc = dy / step;

    glBegin(GL_POINTS);
    for (float i = 1; i <= step; i++)
    {
        glVertex2i(x1, y1);
        x1 += xInc;
        y1 += yInc;
    }
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-400.0f, 400.0f, -400.0f, 400.0f);
}

void display()
{
    P[0][0] = 0;
    P[0][1] = 0;

    P[1][0] = 200;
    P[1][1] = 0;

    P[2][0] = 200;
    P[2][1] = 200;

    P[3][0] = 0;
    P[3][1] = 200;

    rotate();

    //DDALine(Point(0, 0), Point(result[0], result[1]));
    glColor3f(1.0f, 0.0f, 0.0f);
    DDALine(Point(P[0][0], P[0][1]), Point(P[1][0], P[1][1]));
    DDALine(Point(P[1][0], P[1][1]), Point(P[2][0], P[2][1]));
    DDALine(Point(P[2][0], P[2][1]), Point(P[3][0], P[3][1]));
    DDALine(Point(P[3][0], P[3][1]), Point(P[0][0], P[0][1]));

    glColor3f(0.0f, 0.0f, 1.0f);
    DDALine(Point(result[0][0], result[0][1]), Point(result[1][0], result[1][1]));
    DDALine(Point(result[1][0], result[1][1]), Point(result[2][0], result[2][1]));
    DDALine(Point(result[2][0], result[2][1]), Point(result[3][0], result[3][1]));
    DDALine(Point(result[3][0], result[3][1]), Point(result[0][0], result[0][1]));
    // I REALLY HATE MATRIX

    glFlush();
}

int main(int agrc, char **argv)
{
    glutInit(&agrc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("LINE ROTATION - BY Z-Erian");
    glutDisplayFunc(display);
    init();

    glutMainLoop();
    return 0;
}