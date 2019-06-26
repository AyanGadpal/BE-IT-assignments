#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    int x1,y1,x2,y2;

    cout<<"\nEnter Starting x,y : ";
    cin>>x1;
    cin>>y1;
    cout<<"\nEnter Ending x,y : ";
    cin>>x2;
    cin>>y2;

    DDALine(x1,y1,x2,y2);
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