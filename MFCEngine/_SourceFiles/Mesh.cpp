#include "Mesh.h"
#include "PrimitiveDefinitions.h"
#include <assert.h>
Mesh::Mesh(Gameobject* object, D3DGraphics& gfx)
	:
	Component(object),
	gfx(gfx)
{
	m_type = CT_DATA;
	InitMaterial();
	InitMesh();
}

Mesh::~Mesh()
{}

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
	int size_cube = sizeof(PRM_CUBE) / sizeof(CUSTOMVERTEX);
	int size_cubeib = sizeof(PRMIB_CUBE) / sizeof(short);

	nTris = size_cubeib / 3;
	nVerts = size_cube / 3;

	vertexBuffer = new CUSTOMVERTEX[size_cube];
	for (int i = 0; i < size_cube; i++)
	{
		vertexBuffer[i] = PRM_CUBE[i];
	}

	short * INDEXBUFFER = new short[size_cubeib];
	for (int i = 0; i < size_cubeib; i++)
	{
		INDEXBUFFER[i] = PRMIB_CUBE[i];
	}

	VOID* pVoid;

	result = gfx.GetDevice()->CreateVertexBuffer(size_cube*sizeof(CUSTOMVERTEX), 0, CUSTOMFVF,
		D3DPOOL_MANAGED, &vb, NULL);
	assert(!FAILED(result));

	vb->Lock(NULL, NULL, (void**)&pVoid, 0);
	memcpy(pVoid, vertexBuffer, size_cube*sizeof(CUSTOMVERTEX));
	vb->Unlock();

	result = gfx.GetDevice()->CreateIndexBuffer(size_cubeib*sizeof(short), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &ib, 0);
	assert(!FAILED(result));

	ib->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, INDEXBUFFER, size_cubeib*sizeof(short));
	ib->Unlock();
}