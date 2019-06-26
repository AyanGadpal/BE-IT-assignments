#include<iostream>
#include<math.h>
#include<GL/glut.h>
#define PI 3.142857143
using namespace std;
 
double P1[3][3],P2[3][3],T[3][3];
 
void autoInit();
void Display();
void menu(int item);
 
int main(int argc , char **argv)
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
 
	P1[0][0]=0;
	P1[0][1]=0;
	P1[0][2]=1;
	P1[1][0]=100;
	P1[1][1]=0;
	P1[1][2]=1;
	P1[2][0]=50;
	P1[2][1]=86.6025;
	P1[2][2]=1;
 
	glutCreateWindow("TRANSFORMATIONS");
	autoInit();
	glutDisplayFunc(Display);
	
	glutCreateMenu(menu);
		glutAddMenuEntry("1.Scaling",1);
		glutAddMenuEntry("2.Translation",2);
		glutAddMenuEntry("3.Rotation",3);
		glutAddMenuEntry("4.Reflection",4);
		glutAddMenuEntry("5.Shear",5);
		glutAddMenuEntry("0.EXIT",0);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();	
}
 
void autoInit()
{
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(4.0);
    gluOrtho2D( -320 , 320 , -240 , 240 );
 
}
 
void poly(double P[3][3])
{
	int i;
	glBegin(GL_LINE_LOOP);
		for(i=0;i<3;i++)
			glVertex2d(P[i][0],P[i][1]);
	glEnd();
	glFlush();
}
void mult(double P[3][3],double T[3][3])
{
	double sum;
	int i,j,k;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{	
			sum=0;
			for(k=0;k<3;k++)
				sum=sum+P[i][k]*T[k][j];
			P2[i][j]=sum;
		}
	}
}
void scaling()
{
	double sx,sy;
	
	cout<<"\n\t**SCALING**\n";
	cout<<"\n\tSx : ";
	cin>>sx;
	cout<<"\n\tSy : ";
	cin>>sy;
	
	T[0][0]=sx;
	T[0][1]=0;
	T[0][2]=0;
	T[1][0]=0;
	T[1][1]=sy;
	T[1][2]=0;
	T[2][0]=0;
	T[2][1]=0;
	T[2][2]=1;
	
	mult(P1,T);
	
	glColor3f(1.0,1.0,0.0);
	poly(P2);
}
void translation()
{
	double tx,ty;
	
	cout<<"\n\t**TRANSLATION**\n";
	cout<<"\n\tTx : ";
	cin>>tx;
	cout<<"\n\tTy : ";
	cin>>ty;
	
	T[0][0]=1;
	T[0][1]=0;
	T[0][2]=0;
	T[1][0]=0;
	T[1][1]=1;
	T[1][2]=0;
	T[2][0]=tx;
	T[2][1]=ty;
	T[2][2]=1;
	
	mult(P1,T);
	
	glColor3f(0.0,1.0,0.0);
	poly(P2);
}
void rotation()
{
	double rx,ry,angle,rad;
	
	cout<<"\n\t**ROTATION**\n";
				
	cout<<"\n\tArbitary Point (x,y) : ";
	cin>>rx>>ry;
	
	cout<<"\n\tAngle (in degree) : ";
	cin>>angle;
					
	rad=angle*(PI/180);
					
	T[0][0]=cos(rad);
	T[0][1]=sin(rad);
	T[0][2]=0;
	T[1][0]=-sin(rad);
	T[1][1]=cos(rad);
	T[1][2]=0;
	T[2][0]=(-(rx*cos(rad))+(ry*sin(rad))+rx);
	T[2][1]=(-(rx*sin(rad))-(ry*cos(rad))+ry);
	T[2][2]=1;
	
	mult(P1,T);
	
	glColor3f(0.0,1.0,0.0);
	poly(P2);
}
void reflection()
{
	int choice;
	cout<<"\n\t**REFLECTION**\n\t1.X-Axis\n\t2.Y-Axis\n\t3.ORIGIN\n\t4.about Y = X\n\t5.about Y = -X \n\tCHOICE>>";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
			T[0][0]=1;
			T[0][1]=0;
			T[0][2]=0;
			T[1][0]=0;
			T[1][1]=-1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
		case 2:
			T[0][0]=-1;
			T[0][1]=0;
			T[0][2]=0;
			T[1][0]=0;
			T[1][1]=1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
		case 3:
			T[0][0]=-1;
			T[0][1]=0;
			T[0][2]=0;
			T[1][0]=0;
			T[1][1]=-1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
		case 4:
			T[0][0]=0;
			T[0][1]=1;
			T[0][2]=0;
			T[1][0]=1;
			T[1][1]=0;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
		case 5:
			T[0][0]=0;
			T[0][1]=-1;
			T[0][2]=0;
			T[1][0]=-1;
			T[1][1]=0;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
	}
	
	mult(P1,T);
	glColor3f(0.0,1.0,0.0);
	poly(P2);
}
void shear()
{
	double xs,ys;
	int choice;
	cout<<"\n\t**SHEAR**";
	cout<<"\n\t1.X - Shear\n\t2.Y - Shear\n\tCHOICE >>";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
			cout<<"\n\tX-shear value : ";
			cin>>xs;
			
			T[0][0]=1;
			T[0][1]=0;
			T[0][2]=0;
			T[1][0]=xs;
			T[1][1]=1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
		case 2:
			cout<<"\n\tY-shear value : ";
			cin>>ys;
			T[0][0]=1;
			T[0][1]=ys;
			T[0][2]=0;
			T[1][0]=0;
			T[1][1]=1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
	}
	
	mult(P1,T);
	glColor3f(0.0,1.0,0.0);
	poly(P2);
}
 
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_LINES);
		glVertex2d(-320,0);	glVertex2d(320,0);
		glVertex2d(0,-240);	glVertex2d(0,240);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	poly(P1);
	glFlush();
}
void menu(int item)
{	
	switch(item)
	{
		case 1:
			scaling();
			break;
		
		case 2:
			translation();
			break;
			
		case 3:
			rotation();
			break;
			
		case 4:
			reflection();
			break;
			
		case 5:
			shear();
			break;
			
		case 0:
			exit(0);
	}
}