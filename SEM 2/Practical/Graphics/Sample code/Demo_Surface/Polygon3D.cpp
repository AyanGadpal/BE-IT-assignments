// Polygon3D.cpp: implementation of the Polygon3D class.
//
//////////////////////////////////////////////////////////////////////


#include <iostream>
#include <GL/glut.h>

#include "Polygon3D.h"


using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Polygon3D::Polygon3D() {
	
	// dummy
}


Polygon3D::Polygon3D( int numVertices) {

	this->init( numVertices);
}


Polygon3D::~Polygon3D() {

}



void Polygon3D::init( int _numVertices) {

	this->numVertices = _numVertices;

	// init vertex pointers
	pVertex = new Vertex3D*[ this->numVertices];

}


void Polygon3D::addVertex3D( int num,  Vertex3D* tempVertex) {


	if (num >= this->numVertices ) {
		cout<<"Polygon3D::addVertex3D() ==> Cant add more vertices";
		exit(-1); // fatal error
	}
	
	this->pVertex[num] = tempVertex;

}

void Polygon3D::genNormal() {

	// use the first 3 points to form the position vectos and generate normal...

	float A[3];
	float B[3]; 

	// A = P1 - P0
	A[0] = this->pVertex[1]->x  - this->pVertex[0]->x;
	A[1] = this->pVertex[1]->y  - this->pVertex[0]->y;
	A[2] = this->pVertex[1]->z  - this->pVertex[0]->z;


	// B = P2 - P1
	B[0] = this->pVertex[2]->x  - this->pVertex[1]->x;
	B[1] = this->pVertex[2]->y  - this->pVertex[1]->y;
	B[2] = this->pVertex[2]->z  - this->pVertex[1]->z;

	// calculating cross product
	normal[0] = A[1]*B[2] - A[2]*B[1];
	normal[1] = -(A[0]*B[2] - A[2]*B[0]);
	normal[2] = A[0]*B[1] - A[1]*B[0];


}


void Polygon3D::draw( const int DrawFlag ) {

	// doing shaded only now..

	//glBegin(GL_LINE_LOOP);


	if (DrawFlag == 0) { // WireFrame

		glBegin(GL_LINE_LOOP);
			glVertex3f(pVertex[0]->x, pVertex[0]->y, pVertex[0]->z );
			glVertex3f(pVertex[1]->x, pVertex[1]->y, pVertex[1]->z );
			glVertex3f(pVertex[2]->x, pVertex[2]->y, pVertex[2]->z );
			glVertex3f(pVertex[3]->x, pVertex[3]->y, pVertex[3]->z );
		glEnd();	
	}

	if (DrawFlag == 1) { // Shade
		glBegin(GL_POLYGON);
			glNormal3fv(normal);
			glVertex3f(pVertex[0]->x, pVertex[0]->y, pVertex[0]->z );
			glVertex3f(pVertex[1]->x, pVertex[1]->y, pVertex[1]->z );
			glVertex3f(pVertex[2]->x, pVertex[2]->y, pVertex[2]->z );
			glVertex3f(pVertex[3]->x, pVertex[3]->y, pVertex[3]->z );
		glEnd();	
	}

}




