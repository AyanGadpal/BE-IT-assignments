// SurfaceGrid.h: interface for the SurfaceGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "Polygon3D.h"


class SurfaceGrid {

	int numPointsX, numPointsY;
	Vertex3D** vertex;// 2D array 

	int numPolygons; 
	Polygon3D* polygon; // 1D array

	void initPolygons();

public:
	
	SurfaceGrid();
	SurfaceGrid(int numPointsX, int numPointsY);
	
	void initSurfacePoints(int numPointsX, int numPointsY);




	void genGaussianSurface();
	void genGaborSurface();
	//void genRippleSurface();


	~SurfaceGrid();


	void drawSurface(const int);

};
