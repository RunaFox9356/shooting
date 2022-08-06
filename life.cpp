//============================
//
// ���C�t�ݒ�
// Author:hamada ryuuga
//
//============================

#include "life.h"
#include "hamada.h"
#include "manager.h"
#include "player.h"
#include "game.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CLife::CLife(int list) :CObject2d(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CLife::~CLife()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CLife::Init()
{
	CObject2d::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CLife::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CLife::Update()
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

	 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	GetVtx()->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

					//�}�g���b�N�X�쐬
	D3DXMatrixIdentity(&mtx);

	//���_���W
	for (int i = 0; i < 2; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);
		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_fSize.x);//<-�T�C�Y�ύX
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_fSize.y);//<-�T�C�Y�ύX
		pVtx[i].pos.z = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N
	GetVtx()->Unlock();
}

//------------------------------------
// �`��
//------------------------------------
void CLife::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2d::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CLife *CLife::Create(const D3DXVECTOR3 & pos)
{
	CLife * pObject = nullptr;
	pObject = new CLife(0);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(300.0f, 50.0f, 0.0f));
		pObject->SetPos(pos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CLife::GetPos() const
{
	return &m_pos;
}

void CLife::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

void CLife::SetMove(const D3DXVECTOR3 & move)
{
	//	m_move = move;
}

void CLife::SetDamage(const int Damage)
{
	m_fSize.x -= Damage;
	CPlayer* cPlayer = CGame::GetPlayer();

}
