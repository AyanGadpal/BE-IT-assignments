#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
/*
    Assingment No. 1    
    Name : Ayan Gadpal / H11 / 23370

*/

using namespace std;

void display();
void reshape(int,int);
void putPixel(int,int);

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
    putPixel(x,y);
    for(i=0;i<step;i++)
    {
        x+=xi;
        y+=yi;
        putPixel(x,y);
    }
}
void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("DDA LINE ALGO");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
    return 0;
}

int midPoint(int x,int y)
{
    return (x+y)/2;
}

void drawShape()
{
    int xmax = glutGet(GLUT_WINDOW_WIDTH);
    int ymax = glutGet(GLUT_WINDOW_HEIGHT);
    
    int m = 400;
    DDALine(0,0,0,m);
    DDALine(0,0,m,0);
    DDALine(0,m,m,m);
    DDALine(m,0,m,m);
    
    int n = midPoint(0,m);

    DDALine(0,n,n,0);
    DDALine(n,0,m,n);
    DDALine(0,n,n,m);
    DDALine(m,n,n,m);

    m = n;
    n = midPoint(0,n);

    DDALine(n,n,m+n,n);
    DDALine(n,n,n,m+n);
    DDALine(m+n,n,m+n,m+n);
    DDALine(n,m+n,m+n,m+n);

    DDALine(m,0,m,ymax);
    DDALine(0,m,xmax,m);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //for x and y Axis
    glColor3f(1.0,0,0);
    int xmax = glutGet(GLUT_WINDOW_WIDTH);
    int ymax = glutGet(GLUT_WINDOW_HEIGHT);
    DDALine(0,0,0,ymax);
    DDALine(0,0,xmax,0);
    glColor3f(1,1,1);
    drawShape();
    glFlush();
}

void putPixel(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}