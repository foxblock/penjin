/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ModelAdjacency.h"

ModelAdjacency::ModelAdjacency()
{

}

ModelAdjacency::ModelAdjacency(string adjacencyFile, L3DS &model)
{
	loadAdjacency(adjacencyFile, model);
}

ModelAdjacency::~ModelAdjacency()
{
	faceObjects.clear();
}

int ModelAdjacency::countMeshes(string file)
{
	int count = 0;
	ifstream ifile(file.c_str());	//load infile
	if(!ifile)
	{
		cout << "Error loading file " << file << endl;
		return false;
	}
	while(!ifile.eof())
	{
		char temp[1024];
		ifile.getline(temp,1024);
		if(strstr(temp, "Mesh"))
		{
			count++;
		}
	}

	ifile.close();

	return count;
}

bool ModelAdjacency::loadAdjacency(string adjFile, L3DS & model)
{
	ifstream ifile(adjFile.c_str());

	if(!ifile)
	{
		cout << "Error loading file " << adjFile << endl;
		return false;
	}

	unsigned int meshCount = model.GetMeshCount();
	faceObjects.resize(meshCount, 0);

	string ID;

	for(unsigned int uiMesh = 0; uiMesh < meshCount; uiMesh++)
	{
		//	Get ID
		ID = "0";
		ifile >> ID;
		if(strstr("Mesh", ID.c_str()))
		{
			//	Then get ID again just to advance to adj info
			ifile >> ID;

			LMesh &mesh = model.GetMesh(uiMesh);
			int iTris = mesh.GetTriangleCount();

			for(int iTri=0; iTri < iTris; iTri++)
			{
				face tempFace;
				for (int i = 0; i < 3; i ++)	//	The adj info is in threes.
					ifile >> tempFace.edgeIndices[i];

				LTriangle tempTri = mesh.GetTriangle(iTri);
				calculatePlane(tempFace,tempTri,mesh);
				faceObjects[uiMesh].push_back(tempFace);
			}
		}
	}
	ifile.close();
}

void ModelAdjacency::calcAdjacency(L3DS & model)
{
	setAdjacency(model);
}

bool ModelAdjacency::saveAdjacency(string adjacencyFile, L3DS & model)
{
	bool result = false;
//////////////////////////////
			FILE * fOutFile;
			int error = fopen_s(&fOutFile,adjacencyFile.c_str(),"wt+");
			if (error)
			{
				std::cout << "Could not open '" << adjacencyFile.c_str() << "' for writing." << std::endl;
				return false;
			}

			for(unsigned int uiMesh = 0; uiMesh < model.GetMeshCount(); uiMesh++)
			{
				LMesh &mesh = model.GetMesh(uiMesh);
				int iTris = mesh.GetTriangleCount();

				fprintf(fOutFile,"Mesh %d\n",uiMesh);
				for(int iTri=0; iTri < iTris; iTri++)
				{
					fprintf(fOutFile,"%d %d %d\n",faceObjects[uiMesh][iTri].edgeIndices[0],
						faceObjects[uiMesh][iTri].edgeIndices[1], faceObjects[uiMesh][iTri].edgeIndices[2]);
				}
			}
			fclose(fOutFile);
/////////////////////////////////////////
	if (faceObjects.size() == 0)
	{
		return false;
	}
	else
	{

		for(int i = 0; i < faceObjects.size(); i ++)
		{
			//	if any of these have data then we have something to save.
			if (faceObjects[i].size() != 0)
			{
				result = true;
			}
		}
	}
return result;
}

bool ModelAdjacency::equal(LVector4 &v1, LVector4 &v2, float fThreshold)
{
	return (((v1.x-v2.x) * (v1.x-v2.x) +
			(v1.y-v2.y) * (v1.y-v2.y) +
			(v1.z-v2.z) * (v1.z-v2.z)) < fThreshold);
}

void ModelAdjacency::setAdjacency(L3DS & theModel)
{
	uint uiMeshes = theModel.GetMeshCount();

	//	Resize the VectorInVector

	faceObjects.resize(uiMeshes, 0);

	// for each mesh in the model
	for (uint uiMesh= 0; uiMesh < uiMeshes; uiMesh++)
    {
		//	Create a temp face object
		face tempFace;


		LMesh &mesh = theModel.GetMesh(uiMesh);
	    int iTris = mesh.GetTriangleCount();

		faceObjects[uiMesh].resize(iTris);

		// initialise the adjacency array to all -1 (no adjacent faces)
		int iTriA;
		for(iTriA=0; iTriA < iTris; iTriA++)
		{
			faceObjects[uiMesh][iTriA].edgeIndices[0] =
			faceObjects[uiMesh][iTriA].edgeIndices[1] =
			faceObjects[uiMesh][iTriA].edgeIndices[3] = -1;
		}

		// for every triangle in this mesh
		for(iTriA=0; iTriA < iTris; iTriA++)
		{
			// for every triangle that has not already been compared with iTriA
			for(int iTriB=iTriA+1; iTriB < iTris; iTriB++)
			{
				const float fT = 0.01f;
			    const LTriangle& triangleA = mesh.GetTriangle(iTriA);
			    const LTriangle& triangleB = mesh.GetTriangle(iTriB);
				LVector4 t1a = mesh.GetVertex(triangleA.a);
				LVector4 t1b = mesh.GetVertex(triangleA.b);
				LVector4 t1c = mesh.GetVertex(triangleA.c);
				LVector4 t2a = mesh.GetVertex(triangleB.a);
				LVector4 t2b = mesh.GetVertex(triangleB.b);
				LVector4 t2c = mesh.GetVertex(triangleB.c);
				// the following if statements check firstly, if the two triangles share a
				// common edge by referring to the same vertices
				// Then they check if they share equivalent edges, i.e. the vertices are
				// very close to each other (within a threshold fT).

				// check this face 0 only if an adjacent face has not been found yet
				if (faceObjects[uiMesh][iTriA].edgeIndices[0] == -1)
				{
					if ((triangleA.a == triangleB.a && triangleA.b == triangleB.b) ||
						(triangleA.a == triangleB.b && triangleA.b == triangleB.a) ||
						(equal(t1a,t2a,fT) && equal(t1b,t2b,fT) ||
							equal(t1a,t2b,fT) && equal(t1b,t2a,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[0] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[0] = iTriA;
						continue;
					}
					else if ((triangleA.a == triangleB.b && triangleA.b == triangleB.c) ||
						(triangleA.a == triangleB.c && triangleA.b == triangleB.b) ||
						(equal(t1a,t2b,fT) && equal(t1b,t2c,fT) ||
							equal(t1a,t2c,fT) && equal(t1b,t2b,fT)))

					{
						faceObjects[uiMesh][iTriA].edgeIndices[0] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[1] = iTriA;
						continue;
					}
					else if ((triangleA.a == triangleB.c && triangleA.b == triangleB.a) ||
						(triangleA.a == triangleB.a && triangleA.b == triangleB.c) ||
						(equal(t1a,t2c,fT) && equal(t1b,t2a,fT) ||
							equal(t1a,t2a,fT) && equal(t1b,t2c,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[0] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[2] = iTriA;
						continue;
					}
				}
				// check this face 1 only if an adjacent face has not been found yet
				if (faceObjects[uiMesh][iTriA].edgeIndices[1] == -1)
				{
					if ((triangleA.b == triangleB.a && triangleA.c == triangleB.b) ||
					(triangleA.b == triangleB.b && triangleA.c == triangleB.a)||
						(equal(t1b,t2a,fT) && equal(t1c,t2b,fT) ||
						 equal(t1b,t2b,fT) && equal(t1c,t2a,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[1] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[0] = iTriA;
						continue;
					}
					else if ((triangleA.b == triangleB.b && triangleA.c == triangleB.c) ||
						(triangleA.b == triangleB.c && triangleA.c == triangleB.b)||
						(equal(t1b,t2b,fT) && equal(t1c,t2c,fT) ||
						 equal(t1b,t2c,fT) && equal(t1c,t2b,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[1] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[1] = iTriA;
						continue;
					}
					else if ((triangleA.b == triangleB.c && triangleA.c == triangleB.a) ||
						(triangleA.b == triangleB.a && triangleA.c == triangleB.c)||
						(equal(t1b,t2c,fT) && equal(t1c,t2a,fT) ||
						 equal(t1b,t2a,fT) && equal(t1c,t2c,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[1] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[2] = iTriA;
						continue;
					}
				}
				// check this face 2 only if an adjacent face has not been found yet
				if (faceObjects[uiMesh][iTriA].edgeIndices[2] == -1)
				{
					if ((triangleA.c == triangleB.a && triangleA.a == triangleB.b) ||
						(triangleA.c == triangleB.b && triangleA.a == triangleB.a)||
						(equal(t1c,t2a,fT) && equal(t1a,t2b,fT) ||
						 equal(t1c,t2b,fT) && equal(t1a,t2a,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[2] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[0] = iTriA;
						continue;
					}
					else if ((triangleA.c == triangleB.b && triangleA.a == triangleB.c) ||
						(triangleA.c == triangleB.c && triangleA.a == triangleB.b)||
						(equal(t1c,t2b,fT) && equal(t1a,t2c,fT) ||
						 equal(t1c,t2c,fT) && equal(t1a,t2b,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[2] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[1] = iTriA;
						continue;
					}
					else if ((triangleA.c == triangleB.c && triangleA.a == triangleB.a) ||
						(triangleA.c == triangleB.a && triangleA.a == triangleB.c)||
						(equal(t1c,t2c,fT) && equal(t1a,t2a,fT) ||
						 equal(t1c,t2a,fT) && equal(t1a,t2c,fT)))
					{
						faceObjects[uiMesh][iTriA].edgeIndices[2] = iTriB;
						faceObjects[uiMesh][iTriB].edgeIndices[2] = iTriA;
						continue;
					}
				}
			}
		}
	}
}

/*
void modelAdjacency::setAdjacency(L3DS &theModel, Face **&ppFaces)
{
	uint uiMeshes = theModel.GetMeshCount();
	ppFaces = new Face*[uiMeshes];
	// for each mesh in the model
	for (uint uiMesh= 0; uiMesh < uiMeshes; uiMesh++)
    {
		LMesh &mesh = theModel.GetMesh(uiMesh);
	    int iTris = mesh.GetTriangleCount();
		ppFaces[uiMesh] = new Face[iTris];
		// initialise the adjacency array to all -1 (no adjacent faces)
		int iTriA;
		for(iTriA=0; iTriA < iTris; iTriA++)
			ppFaces[uiMesh][iTriA][0] = ppFaces[uiMesh][iTriA][1] =
				ppFaces[uiMesh][iTriA][2] = -1;
		// for every triangle in this mesh
		for(iTriA=0; iTriA < iTris; iTriA++)
		{
			// for every triangle that has not already been compared with iTriA
			for(int iTriB=iTriA+1; iTriB < iTris; iTriB++)
			{
				const float fT = 0.01f;
			    const LTriangle& triangleA = mesh.GetTriangle(iTriA);
			    const LTriangle& triangleB = mesh.GetTriangle(iTriB);
				LVector4 t1a = mesh.GetVertex(triangleA.a);
				LVector4 t1b = mesh.GetVertex(triangleA.b);
				LVector4 t1c = mesh.GetVertex(triangleA.c);
				LVector4 t2a = mesh.GetVertex(triangleB.a);
				LVector4 t2b = mesh.GetVertex(triangleB.b);
				LVector4 t2c = mesh.GetVertex(triangleB.c);
				// the following if statements check firstly, if the two triangles share a
				// common edge by referring to the same vertices
				// Then they check if they share equivalent edges, i.e. the vertices are
				// very close to each other (within a threshold fT).

				// check this face 0 only if an adjacent face has not been found yet
				if (ppFaces[uiMesh][iTriA][0] == -1)
				{
					if ((triangleA.a == triangleB.a && triangleA.b == triangleB.b) ||
						(triangleA.a == triangleB.b && triangleA.b == triangleB.a) ||
						(equal(t1a,t2a,fT) && equal(t1b,t2b,fT) ||
							equal(t1a,t2b,fT) && equal(t1b,t2a,fT)))
					{
						ppFaces[uiMesh][iTriA][0] = iTriB;
						ppFaces[uiMesh][iTriB][0] = iTriA;
						continue;
					}
					else if ((triangleA.a == triangleB.b && triangleA.b == triangleB.c) ||
						(triangleA.a == triangleB.c && triangleA.b == triangleB.b) ||
						(equal(t1a,t2b,fT) && equal(t1b,t2c,fT) ||
							equal(t1a,t2c,fT) && equal(t1b,t2b,fT)))

					{
						ppFaces[uiMesh][iTriA][0] = iTriB;
						ppFaces[uiMesh][iTriB][1] = iTriA;
						continue;
					}
					else if ((triangleA.a == triangleB.c && triangleA.b == triangleB.a) ||
						(triangleA.a == triangleB.a && triangleA.b == triangleB.c) ||
						(equal(t1a,t2c,fT) && equal(t1b,t2a,fT) ||
							equal(t1a,t2a,fT) && equal(t1b,t2c,fT)))
					{
						ppFaces[uiMesh][iTriA][0] = iTriB;
						ppFaces[uiMesh][iTriB][2] = iTriA;
						continue;
					}
				}
				// check this face 1 only if an adjacent face has not been found yet
				if (ppFaces[uiMesh][iTriA][1] == -1)
				{
					if ((triangleA.b == triangleB.a && triangleA.c == triangleB.b) ||
					(triangleA.b == triangleB.b && triangleA.c == triangleB.a)||
						(equal(t1b,t2a,fT) && equal(t1c,t2b,fT) ||
						 equal(t1b,t2b,fT) && equal(t1c,t2a,fT)))
					{
						ppFaces[uiMesh][iTriA][1] = iTriB;
						ppFaces[uiMesh][iTriB][0] = iTriA;
						continue;
					}
					else if ((triangleA.b == triangleB.b && triangleA.c == triangleB.c) ||
						(triangleA.b == triangleB.c && triangleA.c == triangleB.b)||
						(equal(t1b,t2b,fT) && equal(t1c,t2c,fT) ||
						 equal(t1b,t2c,fT) && equal(t1c,t2b,fT)))
					{
						ppFaces[uiMesh][iTriA][1] = iTriB;
						ppFaces[uiMesh][iTriB][1] = iTriA;
						continue;
					}
					else if ((triangleA.b == triangleB.c && triangleA.c == triangleB.a) ||
						(triangleA.b == triangleB.a && triangleA.c == triangleB.c)||
						(equal(t1b,t2c,fT) && equal(t1c,t2a,fT) ||
						 equal(t1b,t2a,fT) && equal(t1c,t2c,fT)))
					{
						ppFaces[uiMesh][iTriA][1] = iTriB;
						ppFaces[uiMesh][iTriB][2] = iTriA;
						continue;
					}
				}
				// check this face 2 only if an adjacent face has not been found yet
				if (ppFaces[uiMesh][iTriA][2] == -1)
				{
					if ((triangleA.c == triangleB.a && triangleA.a == triangleB.b) ||
						(triangleA.c == triangleB.b && triangleA.a == triangleB.a)||
						(equal(t1c,t2a,fT) && equal(t1a,t2b,fT) ||
						 equal(t1c,t2b,fT) && equal(t1a,t2a,fT)))
					{
						ppFaces[uiMesh][iTriA][2] = iTriB;
						ppFaces[uiMesh][iTriB][0] = iTriA;
						continue;
					}
					else if ((triangleA.c == triangleB.b && triangleA.a == triangleB.c) ||
						(triangleA.c == triangleB.c && triangleA.a == triangleB.b)||
						(equal(t1c,t2b,fT) && equal(t1a,t2c,fT) ||
						 equal(t1c,t2c,fT) && equal(t1a,t2b,fT)))
					{
						ppFaces[uiMesh][iTriA][2] = iTriB;
						ppFaces[uiMesh][iTriB][1] = iTriA;
						continue;
					}
					else if ((triangleA.c == triangleB.c && triangleA.a == triangleB.a) ||
						(triangleA.c == triangleB.a && triangleA.a == triangleB.c)||
						(equal(t1c,t2c,fT) && equal(t1a,t2a,fT) ||
						 equal(t1c,t2a,fT) && equal(t1a,t2c,fT)))
					{
						ppFaces[uiMesh][iTriA][2] = iTriB;
						ppFaces[uiMesh][iTriB][2] = iTriA;
						continue;
					}
				}
			}
		}
	}
}
*/

void ModelAdjacency::calculatePlane(face &thePlane, const LTriangle &theTri, LMesh &theMesh)
{
	// Get shortened names for each vertex
	LVector4 v1 = theMesh.GetVertex(theTri.a);
	LVector4 v2 = theMesh.GetVertex(theTri.b);
	LVector4 v3 = theMesh.GetVertex(theTri.c);
	thePlane.planeEqn.a = v1.y*(v2.z-v3.z) + v2.y*(v3.z-v1.z) +
				v3.y*(v1.z-v2.z);
	thePlane.planeEqn.b = v1.z*(v2.x-v3.x) + v2.z*(v3.x-v1.x) +
				v3.z*(v1.x-v2.x);
	thePlane.planeEqn.c = v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y) +
				v3.x*(v1.y-v2.y);
	thePlane.planeEqn.d = -( v1.x*( v2.y*v3.z - v3.y*v2.z ) +
				v2.x*(v3.y*v1.z - v1.y*v3.z) +
				v3.x*(v1.y*v2.z - v2.y*v1.z) );
}
