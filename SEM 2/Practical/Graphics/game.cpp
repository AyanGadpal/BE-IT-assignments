#include<iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
 
using namespace std;

void display();

void reshape(int,int);

void Init()
{

    glClearColor(0.0,0.0,0.0,1.0);


}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("GAME");
    glutDisplayFunc(display);  // Display CallBack 
    glutReshapeFunc(reshape); // this is called whenever windows is reshape
    Init();
    glutMainLoop();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); // RESET ALL CURRENT MATRIX


    //glPointSize(10.0);
    //draw
    glBegin(GL_POLYGON);

    glVertex2f(5,5);
    glVertex2f(-5,-5);
    glVertex2f(-5,3);

    glEnd();

    glFlush();
}
void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);//x,y,w,h of viewport
    glMatrixMode(GL_PROJECTION); //By default we are in model View matrix
    glLoadIdentity(); // RESET ALL P
    gluOrtho2D(-10,10,-10,10);//set 2D coordinate system
    glMatrixMode(GL_MODELVIEW);     

}