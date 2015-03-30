#include "Mesh.h"
#include "PrimitiveDefinitions.h"
#include <assert.h>
#include <stdio.h>
Mesh::Mesh(Gameobject* object, D3DGraphics& gfx)
	:
	Component(object),
	gfx(gfx),
	tex(NULL),
	TextureFilePath(NULL)
{
	m_type = CT_DATA;
	m_pCompIdentifier = CTYPE_MESH;
	InitMaterial();
	InitMesh();
	m_pName = new char[5];
	m_pName = { "Mesh" };
}

Mesh::~Mesh()
{
	if (vertexBuffer)
		delete vertexBuffer;
	if (indexBuffer)
		delete indexBuffer;
	if (vb)
		vb->Release();
	if (ib)
		ib->Release();
	if (tex)
		tex->Release();

	vertexBuffer = NULL;
	indexBuffer = NULL;
	vb = NULL;
	ib = NULL;
	tex = NULL;
}

void Mesh::RemoveTexture()
{
	if (tex)
		tex->Release();
	tex = NULL;
}

void Mesh::SetMaterial(D3DMATERIAL9 newMat)
{
	ZeroMemory(&mat, sizeof(D3DMATERIAL9));
	mat.Ambient = D3DXCOLOR(newMat.Ambient.r, newMat.Ambient.g, newMat.Ambient.b, newMat.Ambient.a);

	mat.Specular = D3DXCOLOR(newMat.Specular.r, newMat.Specular.g, newMat.Specular.b, newMat.Specular.a);

	mat.Diffuse = D3DXCOLOR(newMat.Diffuse.r, newMat.Diffuse.g, newMat.Diffuse.b, newMat.Diffuse.a);
}

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

	//GETTING THE NAME OF THE MATERIAL (MTL) FILE AND STORING IT IN A SEPERATE STRING
	int nameLen = 0;
	int matExtensionStart = 0;
	int dirLen = 0;
	for (; filename[nameLen] != '\0'; nameLen++);
	dirLen = nameLen;
	char* matFilepath = new char[nameLen + 1];

	for (; filename[dirLen] != '\\'; dirLen--);
	dirLen += 2;
	char* curDirectory = new char[dirLen];

	for (int i = 0; i < dirLen-1; i++)
	{
		curDirectory[i] = filename[i];
	}
	curDirectory[dirLen - 1] = '\0';

	for (int i = 0; i < nameLen; i++)
	{
		matFilepath[i] = filename[i]; 
		if (filename[i] == '.')
		{
			matExtensionStart = i;
			break;
		}
	}

	matFilepath[matExtensionStart + 1] = 'm';
	matFilepath[matExtensionStart + 2] = 't';
	matFilepath[matExtensionStart + 3] = 'l';
	matFilepath[matExtensionStart + 4] = '\0';
	//******************************************************************************

	//*********************************************************
	//INITIALIZATION OF TEMPORARY BUFFERS
	short*			TempIb			= NULL;
	vector3*		TempVb			= NULL;
	vector3*		TempNb			= NULL;
	UV*				TempTb			= NULL;
	faceInfo*		faces			= NULL;
	CUSTOMVERTEX*	FMTINDEXBUFFER	= NULL;

	UINT nFaces		= 0;
	UINT nVertices	= 0;
	UINT nNormals	= 0;
	UINT nIndices	= 0;
	UINT nTexCoord	= 0;

	bool isVtParse	= false;
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

				delete[] temp;
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

				delete[] temp;
				nNormals++;
			}//LOADING FACE INFO//************************************
			else if (!strcmp(buffer, "vt"))
			{
				UV* temp = new UV[nTexCoord + 1];
				for (int i = 0; i < nTexCoord; i++){ temp[i] = TempTb[i]; }
				float tu = -1, tv = -1;
				fscanf(pFile, "%f%f", &tu, &tv);

				temp[nTexCoord].U = tu;
				temp[nTexCoord].V = tv;

				nTexCoord++;

				if (TempTb)
					delete[] TempTb;
				TempTb = new UV[nTexCoord];

				for (int i = 0; i < nTexCoord; i++){ TempTb[i] = temp[i]; }
				delete[] temp;
			}
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
						int i_vt = 1, i_vn = 2;
						for (int i = 1; i < 32; i++, i_vn++)
						{
							if (buffer[i_vn - 1] == '/')
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

	fclose(pFile);

	pFile = fopen(matFilepath, "r");
	do
	{
		char buffer[128] = { 0 };
		if (!feof(pFile))
		{
			fscanf(pFile, "%s", buffer);
			if (!strcmp(buffer,"map_Kd") )
			{
				fscanf(pFile, "%s", buffer);
				if (buffer)
				{
					int filepathLen = 0;
					int texLen = 0;
					for (; buffer[texLen] != '\0'; texLen++);
					filepathLen = dirLen + texLen;

					TextureFilePath = new char[filepathLen];

					for (int i = 0; i < dirLen - 1; i++)
					{
						TextureFilePath[i] = curDirectory[i];
					}

					for (int i = 0; i < texLen; i++)
					{
						TextureFilePath[i + dirLen - 1] = buffer[i];
					}
					TextureFilePath[filepathLen - 1] = '\0';
				}
				else
				{
					TextureFilePath = { 0 };
				}
			}
		}
	} while (!feof(pFile));

	//**************************
	//FORMATTING THE INFORMATION
	//**************************
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

	faces = TriangulateFaces(faces,&nFaces);

	//Looping through all face definitions and creating the neccesary Vertices
	for (int i = 0; i < nFaces; i++)
	{
		faceInfo* face = &faces[i];
		
		for (int p_i = 0; p_i < 3; p_i++)
		{
			int v_i = face->point[p_i].vertexIndex;
			int vn_i = face->point[p_i].normalIndex;
			int vt_i = face->point[p_i].textureIndex;

			vector3* t_norm = NULL;
			vector3* t_vert = NULL;
			UV*		 t_uv = NULL;
			if (TempNb)
				t_norm = new vector3;
				*t_norm = TempNb[vn_i];
			if (TempVb)
				t_vert = new vector3;
				*t_vert = TempVb[v_i];
			if (TempTb)
			{
				t_uv = new UV; 
				*t_uv = TempTb[vt_i];
			}

			bool vertExists = false;
			for (int i_v = 0; i_v < BufIndex; i_v++)
			{
				if (t_pSortedVb[i_v].NORMAL.x == -t_norm->x &&
					t_pSortedVb[i_v].NORMAL.y == -t_norm->y &&
					t_pSortedVb[i_v].NORMAL.z == -t_norm->z &&
					t_pSortedVb[i_v].x == -t_vert->x &&
					t_pSortedVb[i_v].y == -t_vert->y &&
					t_pSortedVb[i_v].z == -t_vert->z &&
					t_pSortedVb[i_v].tu == t_uv->U &&
					t_pSortedVb[i_v].tv == 1 - t_uv->V)
				{
					t_pSortedIb[p_i + i * 3] = i_v;
				}
			}

			if (!vertExists)
			{
				if (t_norm)
				{
					t_pSortedVb[BufIndex].NORMAL.x = -t_norm->x;
					t_pSortedVb[BufIndex].NORMAL.y = -t_norm->y;
					t_pSortedVb[BufIndex].NORMAL.z = -t_norm->z;
				}
				
				if (t_vert)
				{
					t_pSortedVb[BufIndex].x = -t_vert->x;
					t_pSortedVb[BufIndex].y = -t_vert->y;
					t_pSortedVb[BufIndex].z = -t_vert->z;
				}

				if (t_uv)
				{
					t_pSortedVb[BufIndex].tu = t_uv->U;
					t_pSortedVb[BufIndex].tv = 1 - t_uv->V;
				}

				t_pSortedIb[p_i + i * 3] = BufIndex;
				BufIndex++;

				if (t_norm)
					delete t_norm;
				if (t_vert)
					delete t_vert;
				if (t_uv)
					delete t_uv;
			}
		}
	}


	for (int i = 0; i < nFaces; i++)
	{
		int i_1 = 0, i_2 = 0, i_3 = 0;
		i_1 = t_pSortedIb[i * 3];
		i_2 = t_pSortedIb[i * 3 + 1];
		i_3 = t_pSortedIb[i * 3 + 2];

		t_pSortedIb[i * 3] = i_1;
		t_pSortedIb[i * 3 + 1] = i_3;
		t_pSortedIb[i * 3 + 2] = i_2;
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
		fprintf(pFile, "\t{%ff,%ff,%ff,%ff,%ff,%ff,\t%ff,%ff,},\n",vertexBuffer[i].x,
			vertexBuffer[i].y,
			vertexBuffer[i].z,
			vertexBuffer[i].NORMAL.x,
			vertexBuffer[i].NORMAL.y,
			vertexBuffer[i].NORMAL.z,
			vertexBuffer[i].tu,
			vertexBuffer[i].tv);
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

	if (TextureFilePath)
		LoadTextureFromFile(TextureFilePath);

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

Mesh::faceInfo* Mesh::TriangulateFaces(faceInfo* faceIndex,	UINT* nFaces)
{
	if (!faceIndex)
		return NULL;

	int nTriangles = 0;
	for (int i = 0; i < *nFaces; i++)
	{
		nTriangles += faceIndex[i].nPoints - 2;
	}

	faceInfo* newFaces = new faceInfo[nTriangles];

	for (int i = 0, t_i = 0; i < *nFaces; i++)
	{
		if (faceIndex[i].nPoints <= 3)
		{
			newFaces[t_i] = faceIndex[i];
		}
		else
		{
			for (int i_l = 0; i_l < faceIndex[i].nPoints - 2;i_l++, t_i++)
			{
				newFaces[t_i].nPoints = 3;
				newFaces[t_i].point = new faceVertex[3];
				newFaces[t_i].point[0] = faceIndex[i].point[0];
				newFaces[t_i].point[1] = faceIndex[i].point[i_l + 1];
				newFaces[t_i].point[2] = faceIndex[i].point[i_l + 2];
			}
		}
	}

	return newFaces;
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
	mat.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void Mesh::LoadTextureFromFile(char* filepath)
{
	RemoveTexture();
	if (!filepath)
		return;
	HRESULT result;
	result = D3DXCreateTextureFromFile(gfx.GetDevice(), filepath, &tex);
	
	int fileLen = 0;
	for (; filepath[fileLen] != '\0'; fileLen++);

	char* temp = new char[fileLen + 1];
	for (int i = 0; i < fileLen + 1; i++){ temp[i] = filepath[i]; }

	if (TextureFilePath)
		delete TextureFilePath;
	
	TextureFilePath = new char[fileLen + 1];
	for (int i = 0; i < fileLen + 1; i++)
	{
		TextureFilePath[i] = temp[i];
	}

	if (result != D3D_OK)
		MessageBox(NULL, "Failed To Create Texture \n(function: Mesh::LoadTextureFromFile File: Mesh.cpp)",
		"Error", MB_OK | MB_ICONEXCLAMATION);
}

void Mesh::GetTextureFilePath(char* buffer, const int buflen) const
{
	if (!TextureFilePath)
	{
		buffer[0] = '\0';
		return;
	}

	for (int i = 0; i < buflen; i++)
	{
		buffer[i] = TextureFilePath[i];
		if (TextureFilePath[i] == '\0')
			break;
	}
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
	if (tex)
	{
		tex->Release();
		tex = NULL;
	}
}
void Mesh::RestoreGFX()
{
	HRESULT result;
	VOID* pVoid;

	if (TextureFilePath)
		LoadTextureFromFile(TextureFilePath);

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