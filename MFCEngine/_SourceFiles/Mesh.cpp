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
	int normalIndex = 0;

	if (vertexBuffer)
		delete [] vertexBuffer;
	vertexBuffer = NULL;
	CUSTOMVERTEX* TEMPVB = NULL;

	if (indexBuffer)
		delete[] indexBuffer;
	indexBuffer = NULL;
	short * TEMPIB = NULL;

	short * TEMPNB = NULL;
	int NBLen = 0;

	int indexBufLen = 0;

	meshType = PM_MESH;
	FILE* pFile;
	fopen_s(&pFile, filename, "r");
	do
	{
		if (!feof(pFile))
		{
			char buffer[16] = { '\0' };
			fscanf(pFile, "%s", &buffer);
			if (!strcmp(buffer,"v"))
			{
				float vx = 0, vy = 0, vz = 0;
				fscanf(pFile, "%f%f%f",&vx, &vy, &vz);
				if (vertexBuffer)
				{
					if (TEMPVB)
						delete [] TEMPVB;
					TEMPVB = new CUSTOMVERTEX[nVerts + 1];
					for (int i = 0; i < nVerts; i++)
					{
						TEMPVB[i] = vertexBuffer[i];
					}
					TEMPVB[nVerts].x = vx;
					TEMPVB[nVerts].y = vy;
					TEMPVB[nVerts].z = vz;

					delete[] vertexBuffer;
					vertexBuffer = new CUSTOMVERTEX[nVerts + 1];
					nVerts++;
					for (int i = 0; i < nVerts; i++)
					{
						vertexBuffer[i] = TEMPVB[i];
					}
				}
				else 
				{
					vertexBuffer = new CUSTOMVERTEX[nVerts + 1];
					vertexBuffer[0].x = vx;
					vertexBuffer[0].y = vy;
					vertexBuffer[0].z = vz;
				}
			}
			else if (!strcmp(buffer, "vn"))
			{
				if (TEMPVB)
				{
					int x = 0, y = 0, z = 0;
					fscanf(pFile, "%f%f%f", &x, &y, &z);
					TEMPVB[normalIndex].NORMAL.x = x;
					TEMPVB[normalIndex].NORMAL.y = y;
					TEMPVB[normalIndex].NORMAL.z = z;
				}
				normalIndex++;
			}
			else if (!strcmp(buffer, "f"))
			{
				int v1 = 0, v2 = 0, v3 = 0;
				int vn1 = 0, vn2 = 0, vn3 = 0;
				int vt1 = 0, vt2 = 0, vt3 = 0;
				fscanf(pFile, "%d/%d/%d%d/%d/%d%d/%d/%d", &v1, &v2, &v3, &vt1,&vt2,&vt3,&vn1,&vn2,&vn3);
				if (indexBuffer)
				{
					if (TEMPIB)
						delete[] TEMPIB;
					TEMPIB = new short[indexBufLen + 3];
					for (int i = 0; i < indexBufLen; i++)
					{
						TEMPIB[i] = indexBuffer[i];
					}
					TEMPIB[indexBufLen] = v1;
					TEMPIB[indexBufLen + 1] = v2;
					TEMPIB[indexBufLen + 2] = v3;

					delete[] indexBuffer;
					indexBuffer = new short[indexBufLen + 3];
					indexBufLen += 3;

					for (int i = 0; i < indexBufLen; i++)
					{
						indexBuffer[i] = TEMPIB[i];
					}
					nTris++;
				}
				else
				{
					indexBuffer = new short[3];
					indexBuffer[0] = v1;
					indexBuffer[1] = v2;
					indexBuffer[2] = v3;
					nTris++;
					indexBufLen = 3;
				}
			}
		}
	} while (!feof(pFile));

	if (vertexBuffer)
		delete[] vertexBuffer;
	vertexBuffer = new CUSTOMVERTEX[nVerts];
	for (int i = 0; i < nVerts; i++)
	{
		vertexBuffer[i] = TEMPVB[i];
	}

	if (indexBuffer)
		delete[] indexBuffer;
	indexBuffer = new short[indexBufLen];

	for (int i = 0; i < indexBufLen; i++)
	{
		indexBuffer[i] = TEMPIB[i];
	}

	HRESULT result;
	VOID* pVoid;

	result = gfx.GetDevice()->CreateVertexBuffer(nVerts*sizeof(CUSTOMVERTEX), 0, CUSTOMFVF,
		D3DPOOL_MANAGED, &vb, NULL);
	assert(!FAILED(result));

	vb->Lock(NULL, NULL, (void**)&pVoid, 0);
	memcpy(pVoid, vertexBuffer, nVerts*sizeof(CUSTOMVERTEX));
	vb->Unlock();

	result = gfx.GetDevice()->CreateIndexBuffer(indexBufLen*sizeof(short), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &ib, 0);
	assert(!FAILED(result));

	ib->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indexBuffer, indexBufLen*sizeof(short));
	ib->Unlock();

	nVerts /= 3;
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