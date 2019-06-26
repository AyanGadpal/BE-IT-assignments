// Code : CG Mock Exam
// Auther : Zahil Shaikh (sahil)
// Batch : H11 SE11
// Roll No: 23376
// Ques No. : ?

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
using namespace std;
class Point;
void myMouseFunc(int, int, int, int); // To handle click event
void DDALine(Point, Point);
void dottedDDA(Point, Point);
bool flag = true, state = true;
int c = 0;

// TO STORE THE COORDINATES
class Point
{
public:
  GLint x;
  GLint y;
  Point() {}
  Point(int x1, int y1)
  {
    x = x1;
    y = y1;
  }
};

Point sP = {0, 0}, eP;

void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  // Output Color
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-250, 250, -250, 250);
}
void myDisplay()
{
  glColor3f(1.0f, 0.0f, 0.0f);            //Red
  DDALine(Point(0, -250), Point(0, 250)); // X axis

  glColor3f(0.0f, 0.0f, 1.0f);            //Blue
  DDALine(Point(250, 0), Point(-250, 0)); // Y axis
  glColor3f(0.0f, 1.0f, 0.0f);

  glPointSize(5); //Thikness Increase

  glFlush();
}

void clickPicker(int b, int s, int x, int y) // Mouse Click Event Handler
{
  if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
  {
    sP.x = x - 250;
    sP.y = 250 - y;
    cout << endl
         << sP.x << " " << sP.y;
  }
  else
  {
    eP.x = x - 250;
    eP.y = 250 - y;
    dottedDDA(sP, eP);
  }
}

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

void dottedDDA(Point p1, Point p2)
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
    if (flag)
    {
      glVertex2i(x1, y1);
      c++;
      if (state)
      {
        if (c == 5)
        {
          flag = false;
          state = false;
        }
      }

      else if (c == 10)
      {
        flag = false;
        state = true;
      }
    }
    else
    {
      c++;
      if (c == 20)
      {
        flag = true; // Enable Pixel
        c = 1;
      }
    }

    x1 += xInc;
    y1 += yInc;
  }
  glEnd();
  glFlush();
}

int main(int agrc, char **agrv)
{
  glutInit(&agrc, agrv);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("Dotted Line Algo");
  init();
  glutDisplayFunc(myDisplay);
  glutMouseFunc(clickPicker);
  glutMainLoop();
  return 0;
}
