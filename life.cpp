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


const D3DXVECTOR3 CLife::m_Vtx[4];
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

	CObject2d::Update();
	if (m_pos.x <= CPlayer::MAXLIFE*0.5f)
	{
		SetCollar(PositionVec4(1.0f, 1.0f, 0.0f, 1.0f));
	}
	if (m_pos.x <= CPlayer::MAXLIFE*0.1f)
	{
		SetCollar(PositionVec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
	//CLife::SetDamage(1);
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
	pObject = new CLife(1);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3((float)CPlayer::MAXLIFE, 20.0f, 0.0f));
		pObject->SetPos(pos);
		
		pObject->SetCollar(PositionVec4(0.0f, 1.0f, 0.0f, 1.0f));
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
	m_Size.x -= Damage;
	m_pos.x -= Damage;
	CPlayer* cPlayer = CGame::GetPlayer();
	cPlayer->HitLife(Damage);
}
