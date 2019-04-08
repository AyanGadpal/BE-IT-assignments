#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

using namespace std;

class Point;
void putPixel(Point);
void BCircle(Point,int r);

class Point
{
	public:
		int x,y;
	Point()
	{
		x=y=0;
	}
	Point(int x,int y)
	{
		this->x = x;
		this->y = y;
	}

};

void BCircle(Point C,int r)
{
	Point p;
	p.x = 0;
	p.y = r;
	putPixel(C);
	putPixel(Point(p.x+C.x,p.y+C.y));

	float Pi = 3 - 2*r;

	while(p.x <= p.y)
	{
		if(Pi < 0)
		{
			p.x++;
			Pi += 4 * p.x + 6;
		}
		else
		{
			p.x++;
			p.y--;
			Pi += 4 * (p.x-p.y) + 16;
		}

		putPixel(Point(C.x + p.x,C.y + p.y));
		putPixel(Point(C.x + p.y,C.y + p.x));
		putPixel(Point(C.x + p.y,C.y - p.x));
		putPixel(Point(C.x + p.x,C.y - p.y));
		putPixel(Point(C.x - p.x,C.y - p.y));
		putPixel(Point(C.x - p.y,C.y - p.x));
		putPixel(Point(C.x - p.y,C.y + p.x));
		putPixel(Point(C.x - p.x,C.y + p.y));
	}
}

void init()
{
	glClearColor(1,1,1,1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	int r;
	cout<<"\nEnter The radius : ";
	cin>>r;

	Point C(400,400);
	
	glColor3f(1,0,0);
	BCircle(C,r);
	glColor3f(0,1,0);
	r= r/2;
	BCircle(C,r);
	glColor3f(0,0,1);
	BCircle(Point(C.x,C.y+r),r);
	BCircle(Point(C.x+r,C.y),r);
	BCircle(Point(C.x,C.y-r),r);
	BCircle(Point(C.x-r,C.y),r);
	
	BCircle(Point(C.x+(7*(r/10)),C.y+(7*(r/10))),r);
	BCircle(Point(C.x+(7*(r/10)),C.y-(7*(r/10))),r);
	BCircle(Point(C.x-(7*(r/10)),C.y-(7*(r/10))),r);
	BCircle(Point(C.x-(7*(r/10)),C.y+(7*(r/10))),r);


	glFlush();
}

void putPixel(Point P)
{
	glBegin(GL_POINTS);
		glVertex2i(P.x,P.y);
	glEnd();	
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,800,0,800);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** agrv)
{
	glutInit(&argc,agrv);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(800,800);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Bresenham's CIRCLE BY AYAN");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
