#include <GL/freeglut.h>
#include <GL/gl.h>

void renderFunction()
{
	
	float max = 0.6f;
	float n = 0.6f/2;
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.5);
	

	
	
	

	glBegin(GL_LINES);
	  
	  glVertex2f(0.0f, 0.0f); 
	  glVertex2f(max, 0.0f);
	  
	  glVertex2f(0.0f, 0.0f); 
	  glVertex2f(0.0f, max); 		
	  
	  glVertex2f(0.0f, max); 
	  glVertex2f(max, max); 
	  
	  glVertex2f(max, 0.0f); 
	  glVertex2f(max, max); 
	  
	  glVertex2f(n, 0.0f); 
	  glVertex2f(0, n); 
	  
	  glVertex2f(n, 0.0f); 
	  glVertex2f(max, n); 
	  
	  glVertex2f(max, n);
	  glVertex2f(n, max);
	  
	  glVertex2f(n, max);
	  glVertex2f(0.0f, max/2);
	  
	  glVertex2f(n/2, n/2);
	  glVertex2f(n+n/2, n/2);
	  
	  glVertex2f(n/2, n/2);
	  glVertex2f(n/2,n+n/2);
	  
	  glVertex2f(n+n/2, n/2);
	  glVertex2f(n+n/2, n+n/2);
	    
	  glVertex2f(n/2,n+n/2);
	  glVertex2f(n+n/2, n+n/2);
	   
	  glVertex2f(n, 0);
	  glVertex2f(n, n);
	  
	  glVertex2f(0, n);
	  glVertex2f(n, n);
	    
	  glVertex2f(n, max);
	  glVertex2f(n, n);
	    
	  glVertex2f(max, n);
	  glVertex2f(n, n);
	    
	glEnd();
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(00,100);
	glutCreateWindow("Hello my First Windows");
	glutDisplayFunc(renderFunction);
	glutMainLoop();
	return 0;
}
