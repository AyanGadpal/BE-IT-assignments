// SurfaceGrid.cpp: implementation of the SurfaceGrid class.
//
//////////////////////////////////////////////////////////////////////

#include <fstream.h>
#include <math.h>
#include "SurfaceGrid.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SurfaceGrid::SurfaceGrid()  {
	
}

SurfaceGrid::SurfaceGrid(int numPointsX, int numPointsY )  {
	
	this->initSurfacePoints( numPointsX, numPointsY );

}


void SurfaceGrid::initSurfacePoints( int _numPointsX, int _numPointsY ) {

	this->numPointsX = _numPointsX;
	this->numPointsY = _numPointsY;

	vertex = new Vertex3D*[ numPointsX ];

	for (int x=0; x< numPointsX; x++) {
		vertex[x] = new Vertex3D[numPointsY];
	}

}



SurfaceGrid::~SurfaceGrid() {


	for (int x=0; x< numPointsX; x++) {
		delete[] vertex[x];
	}

	delete[] vertex;

}


void SurfaceGrid::genGaussianSurface() {


	const float sigma = 0.25;

	float scale  = 1.0 / sqrt(2.0*22.0/7.0) / sigma;


	ofstream vertexFile("vertex.dat");

	for (int x=0; x< this->numPointsX; x++) {

		for (int y=0; y< this->numPointsY; y++) {

			float xVal = 0.1 * (x - this->numPointsX/2);
			float yVal = 0.1 * (y - this->numPointsY/2);
			float zVal = scale * exp( -0.5*( xVal*xVal + yVal*yVal)/sigma*sigma); // simplified Gaussian

			vertex[x][y].x = xVal;
			vertex[x][y].y = yVal;
			vertex[x][y].z = zVal;

		//	vertexFile << x <<" ";
		//	vertexFile << y <<" ";
			vertexFile << vertex[x][y].z <<" ";
		}

		vertexFile <<"\n";
	}

	vertexFile.close();



	this->initPolygons();
}



void SurfaceGrid::genGaborSurface() {

	const float sigma = 0.25;
	const float omega = 6.0;

	float scale  = 1.0 / sqrt(2.0*22.0/7.0) / sigma;


	ofstream vertexFile("vertex.dat");

	for (int x=0; x< this->numPointsX; x++) {

		for (int y=0; y< this->numPointsY; y++) {

			float xVal = 0.1 * (x - this->numPointsX/2);
			float yVal = 0.1 * (y - this->numPointsY/2);
			float zVal = scale * exp( -0.5*( xVal*xVal + yVal*yVal)/sigma*sigma) * sin(omega*xVal); // simplified Gaussian

			vertex[x][y].x = xVal;
			vertex[x][y].y = yVal;
			vertex[x][y].z = zVal;

		//	vertexFile << x <<" ";
		//	vertexFile << y <<" ";
			vertexFile << vertex[x][y].z <<" ";
		}

		vertexFile <<"\n";
	}

	vertexFile.close();


	this->initPolygons();
}
	








void SurfaceGrid::initPolygons() {

	this->numPolygons = (this->numPointsX -1)*(this->numPointsY -1);

	this->polygon = new Polygon3D[ this->numPolygons];


	int polygonIndex = 0;

	for (int x=0; x< this->numPointsX -1; x++) {

		for (int y=0; y< this->numPointsY -1; y++) {

			polygon[polygonIndex].init(4); // const here 
			polygon[polygonIndex].addVertex3D(0, &vertex[x][y]);
			polygon[polygonIndex].addVertex3D(1, &vertex[x+1][y]);
			polygon[polygonIndex].addVertex3D(2, &vertex[x+1][y+1]);
			polygon[polygonIndex].addVertex3D(3, &vertex[x][y+1]);
	
			polygon[polygonIndex].genNormal();

			polygonIndex++;

		}
	}

}



void SurfaceGrid::drawSurface(const int DrawFlag) {

	for (int i=0; i< this->numPolygons; i++) {

		polygon[i].draw( DrawFlag );

	}

}


