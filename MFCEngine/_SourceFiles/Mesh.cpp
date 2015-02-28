#include "Mesh.h"
#include "PrimitiveDefinitions.h"
#include <assert.h>
#include <stdio.h>
Mesh::Mesh(Gameobject* object, D3DGraphics& gfx)
	:
	Component(object),
	gfx(gfx)
{
	m_type = CT_DATA;
	m_pCompIdentifier = CTYPE_MESH;
	InitMaterial();
	InitMesh();
	m_pName = new char[5];
	m_pName = { "Mesh" };
}

Mesh::~Mesh()
{}

void Mesh::LoadPrimitive(const PRIMITIVEMESH meshtype,const CUSTOMVERTEX* PRM,const short* PRMIB,const UINT PRM_SIZE,const UINT PRMIB_SIZE)
{
	meshType = meshtype;
	HRESULT result;

	vb_size = PRM_SIZE;
	ib_size = PRMIB_SIZE;

	nTris = PRMIB_SIZE / 3;
	nVerts = PRM_SIZE / 3;
	if (vertexBuffer)
		delete[] vertexBuffer;

	vertexBuffer = new CUSTOMVERTEX[PRM_SIZE];
	for (int i = 0; i < PRM_SIZE; i++)
	{
		vertexBuffer[i] = PRM[i];
	}

	if (indexBuffer)
		delete [] indexBuffer;
	indexBuffer = new short[PRMIB_SIZE];
	for (int i = 0; i < PRMIB_SIZE; i++)
	{
		indexBuffer[i] = PRMIB[i];
	}

	VOID* pVoid;

	result = gfx.GetDevice()->CreateVertexBuffer(PRM_SIZE*sizeof(CUSTOMVERTEX), 0, CUSTOMFVF,
		D3DPOOL_MANAGED, &vb, NULL);
	assert(!FAILED(result));

	vb->Lock(NULL, NULL, (void**)&pVoid, 0);
	memcpy(pVoid, vertexBuffer, PRM_SIZE*sizeof(CUSTOMVERTEX));
	vb->Unlock();

	result = gfx.GetDevice()->CreateIndexBuffer(PRMIB_SIZE*sizeof(short), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &ib, 0);
	assert(!FAILED(result));

	ib->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indexBuffer, PRMIB_SIZE*sizeof(short));
	ib->Unlock();
}

void Mesh::LoadFromFile(const char* filename)
{
	//STRUCTS THAT WILL BE USEFUL FOR STORING THE INFORMATION
	struct vector3 {
		float x;
		float y;
		float z;
	};

	struct faceVertex {
		int vertexIndex;
		int normalIndex;
		int textureIndex;
	};

	struct faceInfo {
		UINT nPoints;
		faceVertex* point;
	};
	//*********************************************************
	//INITIALIZATION OF TEMPORARY BUFFERS
	short* TempIb = NULL;
	vector3* TempVb = NULL;
	vector3* TempNb = NULL;
	faceInfo* faces = NULL;
	CUSTOMVERTEX* FMTINDEXBUFFER = NULL;

	UINT nFaces = 0;
	UINT nVertices = 0;
	UINT nNormals = 0;
	UINT nIndices = 0;
	//*********************************************************
	//LOADING THE INFO FROM THE FILE
	nVerts = 0;
	nTris = 0;

	FILE* pFile;
	pFile = fopen(filename, "r");
	do
	{
		char buffer[32];
		if (!feof(pFile))
		{
			fscanf(pFile, "%s", buffer);
			//***********************
			//LOADING VERTEX INFO//***********************************
			if (!strcmp(buffer, "v"))
			{
				float x = 0, y = 0, z = 0;
				fscanf(pFile, "%f%f%f", &x, &y, &z);

				vector3* temp = new vector3[nVertices + 1];
				for (int i = 0; i < nVertices; i++)
				{
					temp[i] = TempVb[i];
				}
				
				if (TempVb)
					delete[] TempVb;
				TempVb = new vector3[nVertices + 1];
				
				temp[nVertices].x = x;
				temp[nVertices].y = y;
				temp[nVertices].z = z;

				for (int i = 0; i < nVertices + 1; i++)
				{
					TempVb[i] = temp[i];
				}

				nVertices++;
			}//LOADING NORMAL INFO//**********************************
			else if (!strcmp(buffer, "vn"))
			{
				float x = 0, y = 0, z = 0;
				fscanf(pFile, "%f%f%f", &x, &y, &z);

				vector3* temp = new vector3[nNormals + 1];
				for (int i = 0; i < nNormals; i++)
				{
					temp[i] = TempNb[i];
				}

				if (TempNb)
					delete[] TempNb;
				TempNb = new vector3[nNormals + 1];

				temp[nNormals].x = x;
				temp[nNormals].y = y;
				temp[nNormals].z = z;

				for (int i = 0; i < nNormals + 1; i++)
				{
					TempNb[i] = temp[i];
				}

				nNormals++;
			}//LOADING FACE INFO//************************************
			else if (!strcmp(buffer, "f"))
			{
				faceInfo* temp = new faceInfo[nFaces+1];
				temp[nFaces].nPoints = 0;
				temp[nFaces].point = NULL;

				for (int i = 0; i < nFaces; i++)
				{
					temp[i] = faces[i];
				}

				if (faces)
					delete faces;
				faces = new faceInfo[nFaces + 1];

				do
				{
					UINT v = -1, vt = -1, vn = -1;
					fscanf(pFile, "%d%s", &v, buffer);

					if (buffer[0] == '/' && buffer[1] == '/')
					{
						vt = -1;
						vn = atoi(&buffer[2]);
					}
					else
					{
						int i_vt = 1, i_vn = 0;
						for (int i = 1; i < 32; i++, i_vn++)
						{
							if (buffer[i] == '/')
								break;
						}
						vt = atoi(&buffer[i_vt]);
						vn = atoi(&buffer[i_vn]);
					}
					faceVertex* tempPoint = new faceVertex[temp[nFaces].nPoints + 1];

					v  -= 1;
					vn -= 1;
					vt -= 1;

					for (int i = 0; i < temp[nFaces].nPoints; i++)
					{
						tempPoint[i] = temp[nFaces].point[i];
					}

					if (temp[nFaces].point)
						delete[] temp[nFaces].point;
					temp[nFaces].point = new faceVertex[temp[nFaces].nPoints + 1];

					for (int i = 0; i < temp[nFaces].nPoints; i++)
					{
						temp[nFaces].point[i] = tempPoint[i];
					}

					temp[nFaces].point[temp[nFaces].nPoints].vertexIndex = v;
					temp[nFaces].point[temp[nFaces].nPoints].textureIndex = vt;
					temp[nFaces].point[temp[nFaces].nPoints].normalIndex = vn;

					temp[nFaces].nPoints++;

					delete[] tempPoint;
				} while (pFile->_ptr[0] != '\n');
				nFaces++;

				for (int i = 0; i < nFaces; i++)
				{
					faces[i] = temp[i];
				}

				delete[] temp;
			}
		}
	} while (!feof(pFile));


	//*********************************************************
	//FORMATTING THE INFORMATION
	/*short* TempIb = NULL;
	vector3* TempVb = NULL;
	vector3* TempNb = NULL;
	faceInfo* faces = NULL;
	CUSTOMVERTEX* FMTINDEXBUFFER = NULL;

	UINT nFaces = 0;
	UINT nVertices = 0;
	UINT nNormals = 0;
	UINT nIndices = 0;*/

	int VertexBufLen = 0;
	int BufIndex = 0;
	short* t_pSortedIb = NULL;
	CUSTOMVERTEX* t_pSortedVb = new CUSTOMVERTEX[nFaces * 3];

	//Counting the number of vertex indices needed
	int nFaceVerts = 0;
	for (int i = 0; i < nFaces; i++)
	{
		nFaceVerts += faces[i].nPoints;
	}

	t_pSortedIb = new short[nFaceVerts];

	//Looping through all face definitions and creating the neccesary Vertices
	for (int i = 0; i < nFaces; i++)
	{
		faceInfo* face = &faces[i];
		
		for (int p_i = 0; p_i < 3; p_i++)
		{
			int v_i = face->point[p_i].vertexIndex;
			int vn_i = face->point[p_i].normalIndex;
			int vt_i = face->point[p_i].textureIndex;

			vector3 t_norm = TempNb[vn_i];
			vector3 t_vert = TempVb[v_i];

			bool vertExists = false;

			if (!vertExists)
			{

				t_pSortedVb[BufIndex].NORMAL.x = t_norm.x;
				t_pSortedVb[BufIndex].NORMAL.y = t_norm.y;
				t_pSortedVb[BufIndex].NORMAL.z = t_norm.z;
			
				t_pSortedVb[BufIndex].x = t_vert.x;
				t_pSortedVb[BufIndex].y = t_vert.y;
				t_pSortedVb[BufIndex].z = t_vert.z;

				t_pSortedIb[p_i + i * 3] = BufIndex;
				BufIndex++;
			}
		}
	}


	//LOADING SORTED INFORMATION INTO THE BUFFERS USED FOR DRAWING
	if (vertexBuffer)
		delete [] vertexBuffer;
	vertexBuffer = new CUSTOMVERTEX[BufIndex];

	if (indexBuffer)
		delete [] indexBuffer;
	indexBuffer = new short[nFaceVerts];

	for (int i = 0; i < BufIndex; i++)
	{
		vertexBuffer[i] = t_pSortedVb[i];
	}

	for (int i = 0; i < nFaceVerts; i++)
	{
		indexBuffer[i] = t_pSortedIb[i];
	}

	nVerts = BufIndex;
	nIndices = nFaceVerts;

	nTris = nFaces;

	vb_size = nVerts;
	ib_size = nIndices;

	pFile = fopen("primitive.txt", "w");

	fprintf(pFile, "static const CUSTOMVERTEX INSERTNAME[] =\n{\n");
	for (int i = 0; i < nVerts; i++)
	{
		fprintf(pFile, "\t{%ff,%ff,%ff,%ff,%ff,%ff,},\n",vertexBuffer[i].x,
			vertexBuffer[i].y,
			vertexBuffer[i].z,
			vertexBuffer[i].NORMAL.x,
			vertexBuffer[i].NORMAL.y,
			vertexBuffer[i].NORMAL.z);
	}
	fprintf(pFile, "};\n\n");
	fprintf(pFile, "static const short INSERTNAME[] =\n{");
	for (int i = 0; i < nFaces; i++)
	{
		fprintf(pFile, "\t%d,%d,%d,\n", indexBuffer[i * 3],
			indexBuffer[i * 3 + 1],
			indexBuffer[i * 3 + 2]);
	}
	fprintf(pFile, "};\n");

	fclose(pFile);

	//CREATING DIRECTX STUFF
	HRESULT result;
	VOID* pVoid;

	result = gfx.GetDevice()->CreateVertexBuffer(nVerts*sizeof(CUSTOMVERTEX), 0, CUSTOMFVF,
		D3DPOOL_MANAGED, &vb, NULL);
	assert(!FAILED(result));

	vb->Lock(NULL, NULL, (void**)&pVoid, 0);
	memcpy(pVoid, vertexBuffer, nVerts*sizeof(CUSTOMVERTEX));
	vb->Unlock();

	result = gfx.GetDevice()->CreateIndexBuffer(nIndices*sizeof(short), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &ib, 0);
	assert(!FAILED(result));

	ib->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indexBuffer, nIndices*sizeof(short));
	ib->Unlock();
}

void Mesh::Render(D3DGraphics& gfx)
{

}
void Mesh::Update()
{

}

void Mesh::InitMaterial()
{
	ZeroMemory(&mat, sizeof(mat));
	mat.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void Mesh::InitMesh()
{
	HRESULT result;
	vb_size = sizeof(PRM_CUBE) / sizeof(CUSTOMVERTEX);
	ib_size = sizeof(PRMIB_CUBE) / sizeof(short);

	nTris = ib_size / 3;
	nVerts = vb_size / 3;

	if (vertexBuffer)
		delete [] vertexBuffer;
	vertexBuffer = new CUSTOMVERTEX[vb_size];
	for (int i = 0; i < vb_size; i++)
	{
		vertexBuffer[i] = PRM_CUBE[i];
	}

	if (indexBuffer)
		delete[] indexBuffer;
	indexBuffer = new short[ib_size];
	for (int i = 0; i < ib_size; i++)
	{
		indexBuffer[i] = PRMIB_CUBE[i];
	}

	VOID* pVoid;

	result = gfx.GetDevice()->CreateVertexBuffer(vb_size*sizeof(CUSTOMVERTEX), 0, CUSTOMFVF,
		D3DPOOL_MANAGED, &vb, NULL);
	assert(!FAILED(result));

	vb->Lock(NULL, NULL, (void**)&pVoid, 0);
	memcpy(pVoid, vertexBuffer, vb_size*sizeof(CUSTOMVERTEX));
	vb->Unlock();

	result = gfx.GetDevice()->CreateIndexBuffer(ib_size*sizeof(short), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &ib, 0);
	assert(!FAILED(result));

	ib->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indexBuffer, ib_size*sizeof(short));
	ib->Unlock();
}


void Mesh::FreeGFX()
{
	if (vb)
	{
		vb->Release();
		vb = NULL;
	}
	if (ib)
	{
		ib->Release();
		ib = NULL;
	}
}
void Mesh::RestoreGFX()
{
	HRESULT result;
	VOID* pVoid;

	result = gfx.GetDevice()->CreateVertexBuffer(vb_size*sizeof(CUSTOMVERTEX), 0, CUSTOMFVF,
		D3DPOOL_MANAGED, &vb, NULL);
	assert(!FAILED(result));

	vb->Lock(NULL, NULL, (void**)&pVoid, 0);
	memcpy(pVoid, vertexBuffer, vb_size*sizeof(CUSTOMVERTEX));
	vb->Unlock();

	result = gfx.GetDevice()->CreateIndexBuffer(ib_size*sizeof(short), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &ib, 0);
	assert(!FAILED(result));

	ib->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indexBuffer, ib_size*sizeof(short));
	ib->Unlock();
}