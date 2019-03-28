#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;

void display();
void reshape(int,int);
void putPixel(int,int);
    
class Points
{
    public:
        int x,y;

};
Points p1,p2;
void DDALine(int xs,int ys,int xe,int ye)
{
    int dy,dx;
    int i,step;
    float x,y,xi,yi;
    dx = xe - xs;
    dy = ye - ys;
    step = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
    xi = dx/(float)step;
    yi = dy/(float)step;
    x = xs;
    y = ys;
   
   glClear(GL_COLOR_BUFFER_BIT);
    putPixel(x,y);

    for(i=0;i<step;i++)
    {
        x+=xi;
        y+=yi;
        putPixel(x,y);
    }


    glEnd();
    glFlush();
}

void choohaa(int button,int state,int x,int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        p1.x = x;
        p1.y = y - 500;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        p2.x = x;
        p2.y = y - 500;
        cout << "X" << x<< "Y" << y-500 <<endl;
 
        DDALine(0,0,100,100);
            glFlush();
    }
}


void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    gluOrtho2D(0,500,0,500);
    glPointSize(1.0f);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("DDA LINE ALGO");
   
    glutDisplayFunc(display);
    glutMouseFunc(choohaa);
   
   
    init();
    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

  
    glFlush();
}

void putPixel(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

