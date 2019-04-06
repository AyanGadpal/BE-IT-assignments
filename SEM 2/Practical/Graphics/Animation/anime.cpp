#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>

using namespace std;

void display();

void reshape(int, int);

void Timer(int);

float x = -10;

void Init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Animation");
    glutDisplayFunc(display); // Display CallBack
    glutReshapeFunc(reshape); // This is called whenever windows is reshape
    glutTimerFunc(1000,Timer,0);
    Init();
    glutMainLoop();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity(); // RESET ALL CURRENT MATRIX
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);

    glVertex2f(x, 1.0);
    glVertex2f(x, -1.0);
    glVertex2f(x+2.0, -1.0);
    glVertex2f(x+2.0, 1.0);
   
    glEnd();

    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void Timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 30, Timer, 0);
    if(x<=8.0)
        x += 0.15; 
}