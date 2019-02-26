
#include <stdio.h>
#include<GLUT.h>
#include<math.h>
#include<string.h>
#include<iostream.h>


int a;

const int screenwidth=640;
const int screenheight=480;

GLdouble A,B,C,D;

void myInit(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0f,0.0f,1.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,GLdouble(screenwidth),0.0,GLdouble(screenheight));
	A=screenwidth/4.0;
	B=0.0;
	C=D=screenheight/2.0;

}



void output()
{
	if(a==0)
	{
		char *string="Demo Of OpenGl Curves";
		glRasterPos2f(200, 250);

		int len = (int) strlen(string);
		
		for (int i = 0; i < len; i++) 
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	else if(a==1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0f,1.0f,0.0f);
		glBegin(GL_POINTS);
		for(GLdouble x=0;x<4.0;x+=0.005)
		{	
			GLdouble func=exp(-x)*cos(2*3.14159*x);
			glVertex2d(A*x+B,C*func+D);
		}
		glEnd();
		glFlush();
	}

	else if(a==2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		GLdouble mean,sum=0.0,var=0.0;
		GLdouble stddev;
		glBegin(GL_POINTS);
		
		for(GLdouble x=0.0;x<640;x+=0.005)
			sum+=x;

		mean=sum/128000;


		for(x=0.0;x<640;x+=0.005)
		{
			var+=pow((x-mean),2);

		}

		var=var/128000;
	
		stddev=sqrt(var);

		for(x=0.0;x<640;x+=0.005)
		{	
			
			GLdouble func=(double)(1/(sqrt(2*3.14)*stddev))*(exp(-pow((x-mean),2)/(2*pow(stddev,2))));
			glVertex2d(x,func*200000);
		}
		glEnd();
		glFlush();

	}

	else if(a==3)
		exit(1);
}


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	output();
	
}


void myMenu( int value ) 
{
	printf("\nSelected menu value = %d", value);
	a=value;
	glutPostRedisplay();
}


void main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Curves ");
	glutDisplayFunc(myDisplay);

	const int MenuID = glutCreateMenu (myMenu); 
	glutAddMenuEntry( "Example Curve ", 1);
	glutAddMenuEntry( "Gaussian Curve", 2);
//	glutAddMenuEntry( "Gabor Curve", 3);
	glutAddMenuEntry( "Exit", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	myInit();
	glutMainLoop();
}