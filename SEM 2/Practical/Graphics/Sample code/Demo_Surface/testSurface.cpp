
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


#include "SurfaceGrid.h"


GLfloat light_diffuse0[] = {1, 1.0, 1, 1.0};  /* Red diffuse light. */
GLfloat light_diffuse1[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light0_position[] = {0.0, 3.0, 0.0, 1.0}; 
GLfloat light1_position[] = {3.0, 3.0, 0.0, 1.0};  /* Infinite light location. */


//GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
 // {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
 // {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
//GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
//  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
//  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
//GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */


float alpha = 0.0;
float beta = 0.0;

int prevMouseX, prevMouseY; // starting points for rubberbanding


SurfaceGrid surface;



const int WireFrame = 0;
const int FlatShade = 1;

const int Gaussian= 2;
const int Gabor = 3;


int currChoice = WireFrame;
int currSurface = Gaussian;


//////////////////////////	drawBox ///////////////////////////////

void drawSurface() { 

//	int i;

 // glTranslatef(0.0, 0.0, -1.0);
  glRotatef( alpha , 1.0, 0.0, 0.0);
  glRotatef( beta, 0.0, 0.0, 1.0);


  surface.drawSurface(currChoice); // 1 = shading; 0 = wireframe
  
 /* for ( i = 0; i < 6; i++) {
	glBegin(GL_QUADS);
	glNormal3fv(&n[i][0]);
	glVertex3fv(&v[faces[i][0]][0]);
	glVertex3fv(&v[faces[i][1]][0]);
	glVertex3fv(&v[faces[i][2]][0]);
	glVertex3fv(&v[faces[i][3]][0]);
	glEnd();
  }*/
}

void display() {
	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawSurface();
  glutSwapBuffers();
}


/////////////////////////////  init //////////////////////////////

void init(void) {



	surface.initSurfacePoints(100,100);
	surface.genGaussianSurface();

	

  /* Enable a single OpenGL light. */
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_LIGHT0);

  
  glLightfv(GL_LIGHT1, GL_AMBIENT, light_diffuse1);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glEnable(GL_LIGHT1);

  glEnable(GL_LIGHTING);

  glShadeModel(GL_SMOOTH);



  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
	/* aspect ratio */ 1.0,
	/* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 6.0,	/* eye is at (0,0,5) */
	0.0, 0.0, 0.0,		/* center is at (0,0,0) */
	0.0, 1.0, 0.);		/* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.5);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);


}


////////////////////////  myKeyHandler /////////////////

void myKeyHandler( unsigned char key, int x, int y) {

  if (key == 27) {
	// Hitting ESC quits
	exit(1);
  }

  printf("\n key pressed is %c at (%d, %d)", key , x, y);

}

///////////////////// myMouseClickHandler //////////////////


void myMouseClickHandler( int button, int state, int x, int y ) {

  static int prevX;
  static int prevY;

  if (state == GLUT_DOWN) {
	printf("\nMouse down at %d, %d", x, y);
	prevMouseX = x;
	prevMouseY = y;
	
  } else {
	printf("\nMouse up at %d, %d", x, y);
  }
  
 
}


/////////////////// myMouseMotionHandler  /////////////////

void myMouseMotionHandler( int x, int y) {

  int delX = prevMouseX - x;
  int delY = prevMouseY - y;

  if (delX >0 ) { 
	beta =	0.9; // positive rotation about Y axis 
  }

  if ( delY > 0) { 
	alpha = 0.9;  // positive rotation about X axis
  }

  if (delX < 0 ) { 
	beta =	-0.9; // negative rotation about Y axis
  }

  if ( delY < 0) { 
	alpha =  -0.9; // negative rotation about X axis
  }


  display();
  printf("\nalpha = %f beta = %f", alpha, beta);
 
}

  

// ****************************************************

void myMenu( int value ) {

	printf("\nSelected menu value = %d", value);
	

	if (value ==1) { // 
		currChoice = WireFrame;
		display();
	}

	if (value ==2 ) {
		currChoice = FlatShade;
		display();
	}
	

	if (value ==3) { // 
		currSurface = Gaussian;
		surface.genGaussianSurface();
		display();
	}

	if (value ==4 ) {
		currSurface = Gabor;
		surface.genGaborSurface();
		display();
	}
	

	if (value == 0) { // exit
		exit(1);
	}


}



////////////////////////  main //////////////////////////////

int main(int argc, char **argv) {

  // GLUT init stuff
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Interactive rotating surface");

  glutDisplayFunc(display); // display callback

  glutKeyboardFunc(myKeyHandler); // keyborad callback

  glutMouseFunc(myMouseClickHandler); // mouse callback

  glutMotionFunc(myMouseMotionHandler); // mouse move callback


  // set up menu
	const int MenuID = glutCreateMenu (myMenu); 
	glutAddMenuEntry("Wireframe", 1);
	glutAddMenuEntry("Shading", 2);
	glutAddMenuEntry("Gaussian", 3);
	glutAddMenuEntry("Gabor", 4);
	glutAddMenuEntry( "Exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


  init();
  glutMainLoop();
  return 0; 			/* ANSI C requires main to return int. */
}
