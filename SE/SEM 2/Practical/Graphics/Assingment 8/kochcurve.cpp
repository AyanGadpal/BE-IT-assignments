// NOT DONE


#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
float x1, y1, x2, y2;
void drawKoch()
{
    float ang = 60;
    ang = ang * 3.14 / 180;
    float x3 = (2 * x1 + x2) / 3;
    float y3 = (2 * y1 + y2) / 3;
    float x4 = (x1 + 2 * x2) / 3;
    float y4 = (y1 + 2 * y2) / 3;
}

void display()
{

    glEnd();
}

int main(int argc, char **agrv)
{
    glutInit(&argc, agrv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("KOCH CURVE");
    glutDisplayFunc(display);
    //  glutMouseFunc(mydisplay);
    glutMainLoop();
    return 0;
}
