#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
using namespace std;

void myMouseFunc(int, int, int, int); // To handle click event

// TO STORE THE COORDINATES
class Point
{
  public:
    GLint x;
    GLint y;
};

int main(int agrc,char **agrv)
{
    glutInit(&agrc,argv);
    glutInitWindowSize(500, 500);
    glutDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Dotted Line Algo");
    glutDisplayFunc();
    glutWi
    return 0;
}
