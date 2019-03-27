#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

#include <iostream>
using namespace std;

void myMouseFunc(int,int,int,int);

class Point
{
  public:
    GLint x;
    GLint y;
    Point *next;
};
struct COLOR
{
    float r, g, b;
};

Point p1, p2;
int t = 0;
bool flag = true;

COLOR fillcolor;

void seedFill(int , int , COLOR , COLOR );
void draw_dda(Point p1, Point p2)
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
   // glPointSize(3.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}

void display(void)
{
}

COLOR getPixelColor(int x, int y)
{
 	COLOR temp;
	glReadPixels(x,y,1,1,GL_RGB, GL_FLOAT, &temp);
	return temp;
}

void setPixelColor(int X, int Y, COLOR color)
{
   	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
		glVertex2i(X,Y);
	glEnd();
	glFlush();
}
void seedFill(int X, int Y, COLOR oldColor, COLOR fillColor)
{
	COLOR current;
	current= getPixelColor(X,Y);
	if(current.r == oldColor.r && current.g == oldColor.g && current.b == oldColor.b)
	{
		setPixelColor(X,Y, fillColor);
		seedFill(X+1,Y, oldColor, fillColor);
		seedFill(X,Y-1, oldColor, fillColor);
		seedFill(X-1,Y, oldColor, fillColor);
		seedFill(X,Y+1, oldColor, fillColor);
	}
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutDisplayFunc(display);
    glutCreateWindow("Mouse Func");

    glutMouseFunc(myMouseFunc);
    init();
    glutMainLoop();

    return 0;
}

void myMouseFunc(int button, int state, int x, int y)
{
    if (t <= 1)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            p1.x = x;
            p1.y = 480 - y;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            p2.x = x;
            p2.y = 480 - y;
            draw_dda(p1, p2);
        }
        t++;
    }
    else if(flag)
    {
        p1 = p2;
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            p2.x = x;
            p2.y = 480 - y;
            draw_dda(p1, p2);   
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            glColor3f(1.0, 0.0, 0.0); //red
            glRecti(10, 30, 60, 10);
            glColor3f(0.0, 1.0, 0.0); //green
            glRecti(90, 30, 140, 10);
            glColor3f(0.0, 0.0, 1.0); //blue
            glRecti(170, 30, 220, 10);
            glColor3f(1.0, 1.0, 0.0); //red-green
            glRecti(250, 30, 300, 10);
            glColor3f(0.0, 1.0, 1.0); //green-blue
            glRecti(330, 30, 380, 10);
            glColor3f(1.0, 0.0, 1.0); //blue-red
            glRecti(410, 30, 460, 10);
            glFlush();
            flag = false;
        }
    }
    else if(!flag)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
         
	       fillcolor=getPixelColor(x,480-y);

 			
        }
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            COLOR fillColor={fillcolor.r,fillcolor.g,fillcolor.b};
			COLOR oldColor= { 1.0f,1.0f,1.0f};
			seedFill(x,480-y,oldColor,fillColor);
        }
    }
}
