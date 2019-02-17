all: testSurface

testSurface: testSurface.cpp Polygon3D.o SurfaceGrid.o
	g++ -o testSurface testSurface.cpp Polygon3D.o SurfaceGrid.o -lglut

Polygon3D.o: Polygon3D.cpp
	g++ -c Polygon3D.cpp -Wno-deprecated

SurfaceGrid.o: SurfaceGrid.cpp
	g++ -c SurfaceGrid.cpp -Wno-deprecated


