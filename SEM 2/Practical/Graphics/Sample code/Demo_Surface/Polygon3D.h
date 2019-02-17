
////////////////////////////////////////////////////////////
// Polygon3D.h: interface for the Polygon3D class.
//
//////////////////////////////////////////////////////////////////////


class Vertex3D { 
public:
	float x, y, z;
};



class Polygon3D  {

private:

	Vertex3D** pVertex; // array of vertex pointers
	int numVertices;
	float normal[3]; // 3D vector

public:
	Polygon3D();
	Polygon3D( int);
	~Polygon3D();

	void init( int numVertices);

	void addVertex3D( int, Vertex3D* );
	void genNormal();
	// use 1, 2, 3 vertices to generate normal..
	
	//void drawFill();
	//void drawEdge();

	void draw(const int drawFlag);

};
