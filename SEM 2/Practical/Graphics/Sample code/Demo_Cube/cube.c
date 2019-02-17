// Modified by Vinod Pathangay (vinod@cse.iitm.ernet.in) 17 March 2005
// 1. Added function callbacks for mouse and keyboard
// 2. Added interactive rotation (examine mode) for the cube
// 3. Changes the lighting mode from GL_DIFFUSE to GL_AMBIENT

/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */


#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {0, 0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */


float alpha = 0.0;
float beta = 0.0;

int prevMouseX, prevMouseY; // starting points for rubberbanding



//////////////////////////  drawBox ///////////////////////////////

void drawBox() { 

	int i;

 // glTranslatef(0.0, 0.0, -1.0);
  glRotatef( alpha , 1.0, 0.0, 0.0);
  glRotatef( beta, 0.0, 0.0, 1.0);

  

  for ( i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glColor3f(1,0,0);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void display() {
	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  glutSwapBuffers();
}


/////////////////////////////  init //////////////////////////////

void init(void) {

  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  /* Enable a single OpenGL light. */
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 // glEnable(GL_LIGHT0);
 // glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
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
    beta =  0.7; // positive rotation about Y axis 
  }

  if ( delY > 0) { 
    alpha = 0.7;  // positive rotation about X axis
  }

  if (delX < 0 ) { 
    beta =  -0.7; // negative rotation about Y axis
  }

  if ( delY < 0) { 
    alpha =  -0.7; // negative rotation about X axis
  }


  display();
  printf("\nalpha = %f beta = %f", alpha, beta);
 
}

  



////////////////////////  main //////////////////////////////

int main(int argc, char **argv) {

  // GLUT init stuff
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Interactive rotating cube");

  glutDisplayFunc(display); // display callback

  glutKeyboardFunc(myKeyHandler); // keyborad callback

  glutMouseFunc(myMouseClickHandler); // mouse callback

  glutMotionFunc(myMouseMotionHandler); // mouse move callback

  init();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
