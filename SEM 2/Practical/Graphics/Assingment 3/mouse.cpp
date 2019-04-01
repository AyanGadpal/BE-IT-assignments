#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
using namespace std;

void myMouseFunc(int, int, int, int); // To handle click event

void seedFill(int , int , COLOR , COLOR ); // Filling

COLOR getPixelColor(int, int); // Get the Pixel Color (IMP) 

void setPixelColor(int, int, COLOR); // Set the Pixel Color

// TO STORE THE COORDINATES
class Point
{
  public:
    GLint x;
    GLint y;
};

// TO STORE COLOR
struct COLOR
{
  public:
    float r, g, b;
};

Point start, p1, p2;
int t = 0;
bool flag = true;
COLOR newcolor;
COLOR oldcolor = {1.0f, 1.0f, 1.0f};

// Simple Line Drawing
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

COLOR getPixelColor(int x, int y)
{
    COLOR temp;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &temp); // Get the Pixel Color
    return temp;
}

void setPixelColor(int X, int Y, COLOR color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(X, Y);
    glEnd();
    glFlush();
}

void seedFill(int X, int Y, COLOR oldColor, COLOR fillColor)
{
    COLOR current;
    current = getPixelColor(X, Y);
    if (current.r == oldColor.r && current.g == oldColor.g && current.b == oldColor.b)
    {
        setPixelColor(X, Y, fillColor);
        seedFill(X + 1, Y, oldColor, fillColor);
        seedFill(X, Y - 1, oldColor, fillColor);
        seedFill(X - 1, Y, oldColor, fillColor);
        seedFill(X, Y + 1, oldColor, fillColor);
    }
}

void myMouseFunc(int button, int state, int x, int y) // CLick Event Handler
{
    if (flag)
    {
        // First Coordinate
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && t == 0)
        {
            p1.x = x;
            p1.y = 500 - y;
            t++;
            start = p1;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            p2.x = x;
            p2.y = 500 - y;
            DDALine(p1, p2);
            p1 = p2;
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            DDALine(p1, start);
            flag = false;
        }
    }
    else
    {
        // Means Polygon is Drawn
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            // Display Color Palate
            glColor3f(1.0, 0.0, 0.0); // Red
            glRecti(10, 30, 60, 10);
            glColor3f(0.0, 1.0, 0.0); // Green
            glRecti(90, 30, 140, 10);
            glColor3f(0.0, 0.0, 1.0); // Blue
            glRecti(170, 30, 220, 10);
            glColor3f(1.0, 1.0, 0.0); // Red-green
            glRecti(250, 30, 300, 10);
            glColor3f(0.0, 1.0, 1.0); // Green-blue
            glRecti(330, 30, 380, 10);
            glColor3f(1.0, 0.0, 1.0); // Blue-red
            glRecti(410, 30, 460, 10);
            glFlush();
            newcolor = getPixelColor(x, 500 - y);
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            seedFill(x, 500 - y,  oldcolor,newcolor);
        }
    }
}

void init()
{

    glClearColor(1.0f, 1.0f, 1.0f, 0); // Background
    glColor3f(0.0f, 0.0f, 0.0f);       // Output Color
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 0, 500);
}

void myDisplay()
{
    // Nothing , Can do copy paste init() code here with glFlush()
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mouse Polygon and Seedfill");
    glutDisplayFunc(myDisplay);

    glutMouseFunc(myMouseFunc); //IMP : mouse event Listener

    init();
    glutMainLoop();

    return 0;
}