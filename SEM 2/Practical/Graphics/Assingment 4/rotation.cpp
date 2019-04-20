#include <GL/freeglut.h>
#include <GL/glu.h>

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

void DDALine(Point p1, Point p2)
{
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;

    GLfloat step = 0;

    if (abs(dx) > abs(dy))
    {
        step = abs(dx);
    }
    else
    {
        step = abs(dy);
    }

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
    gluOrtho2D(-400.0f, 400.0f, -400.0f, 400.0f);
}

void display()
{
   
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-400.0f, 400.0f, -400.0f, 400.0f);
    DDALine(Point(0,0),Point(200,200));
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

    glutMainLoop();
    return 0;
}