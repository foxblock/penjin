#ifndef MODELADJACENCY_H
#define MODELADJACENCY_H

#include "DoubleVector.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct
{
float a, b, c, d;
} planeEquation;

typedef int Face[3];

typedef struct
{
int edgeIndices[3]; // adjacency info
planeEquation planeEqn;
bool bLit;
} face;


#include "l3ds.h"

class ModelAdjacency
{
public:
	ModelAdjacency();											//	Create an empty adjacency object
	ModelAdjacency(string adjacencyFile, L3DS & theModel);			//	Create and load an ajacency object
	~ModelAdjacency();											//	Destroy modelAdjacency object.

	bool loadAdjacency(string adjacencyFile, L3DS & theModel);		//	load an adjacency object for the specified model mesh
																//	Packs data into vectorInVector <face> faceObjects

	void calcAdjacency(L3DS & theModel);						//	calculate the adjacencies from the supplied model object

	bool saveAdjacency(string adjacencyFile, L3DS & theModel);	//	Saves the calculated adjacency information  stored in faceObjects to file relating to the supplied model

	DoubleVector <face> faceObjects;												//	Object to store the face information.

private:
	void calculatePlane(face &thePlane, const LTriangle &theTri, LMesh &theMesh);	//	Calculate the plane equation
	void setAdjacency(L3DS & theModel, Face **& ppFaces);							//	Set the adjacency
	void setAdjacency(L3DS & theModel);
	bool equal(LVector4 &v1,LVector4 &v2, float fThreshold);
	int countMeshes(string file);													//	Counts the number of meshes in an adjacency file
};

#endif	//	MODELAJACENCY_H
