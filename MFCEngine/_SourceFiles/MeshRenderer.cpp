#include "MeshRenderer.h"
#include "Mesh.h"
#include "Gameobject.h"
#include "D3DGraphics.h"
#include "Transform.h"

MeshRenderer::~MeshRenderer()
{}

void MeshRenderer::SetMeshPointer(Mesh* newmesh, int ID)
{
	mesh = newmesh;
	meshID = ID;
}

void MeshRenderer::Render(D3DGraphics& gfx)
{
	if (mesh)
	{
		D3DXMATRIX matTranslate;
		D3DXMATRIX matRotationX;
		D3DXMATRIX matRotationY;
		D3DXMATRIX matRotationZ;
		D3DXMATRIX matScale;

		if (m_pParent->GetTransform())
		{
			Transform* tnfm = m_pParent->GetTransform();
			D3DXMatrixTranslation(&matTranslate, tnfm->GetTranslation().x,
				tnfm->GetTranslation().y,
				tnfm->GetTranslation().z);
			D3DXMatrixRotationX(&matRotationX, D3DXToRadian(tnfm->GetRotation().x));
			D3DXMatrixRotationY(&matRotationY, D3DXToRadian(tnfm->GetRotation().y));
			D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(tnfm->GetRotation().z + 180));

			D3DXMatrixScaling(&matScale, tnfm->GetScale().x, tnfm->GetScale().y, tnfm->GetScale().z);
		}
		else
		{
			D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, 0.0f);
			D3DXMatrixRotationX(&matRotationX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matRotationY, D3DXToRadian(0));
			D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(0));
			D3DXMatrixScaling(&matScale, 0.0f, 0.0f, 0.0f);
		}

		D3DMATERIAL9* mat = mesh->GetMaterial();
		if (mesh->GetTexture())
			gfx.GetDevice()->SetTexture(0, mesh->GetTexture());
		else
			gfx.GetDevice()->SetTexture(0, NULL);

		if (mat)
			gfx.GetDevice()->SetMaterial(mat);
		else
			gfx.GetDevice()->SetMaterial(&defaultMat);

		gfx.GetDevice()->SetTransform(D3DTS_WORLD,
			&(
			matScale *
			matRotationX *
			matRotationY *
			matRotationZ *
			matTranslate));
		gfx.GetDevice()->SetStreamSource(0, mesh->GetVB(), 0, sizeof(CUSTOMVERTEX));
		gfx.GetDevice()->SetIndices(mesh->GetIB());
		gfx.GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
			mesh->GetNVerts() , 0, mesh->GetNTris());
	}
}


void MeshRenderer::FreeGFX()
{

}
void MeshRenderer::RestoreGFX()
{

}