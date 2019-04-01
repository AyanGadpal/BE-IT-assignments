// Auther : Ayan N Gadpal 
// Copyright : GNU public libraly
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include "DDALINE.h"

using namespace std;



int rotatex(int x, int y, double angle)
{
	return x*cos( angle * PI / 180.0 ) - y*sin( angle * PI / 180.0 );
}

int rotatey(int x, int y, double angle)
{
	return x*sin( angle * PI / 180.0 ) + y*cos( angle * PI / 180.0 );    
}

int translatex(int x, int tx)
{
	return x - tx;
}

int translatey(int y, int ty)
{
	return y - ty;
}



void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}


void display()
{
    
    glFlush()
}

void mouseEventListener(int button, int state, int x, int y)
{}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);   
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(200,200);
    glutCreateWindow("CHESS");
    glutDisplayFunc(display);
    glutMouseFunc(mouseEventListener);
    init();
    glutMainLoop();
    return 0;
}
