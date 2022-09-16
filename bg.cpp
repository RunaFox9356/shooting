//============================
//
// �w�i�ݒ�
// Author:hamada ryuuga
//
//============================

#include "bg.h"
#include "hamada.h"
#include "manager.h"

D3DXVECTOR3 CBg::m_KillSpeed;
//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBg::CBg(int list):C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBg::~CBg()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBg::Init()
{
	m_Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_AddSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_KillSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CBg::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CBg::Update()
{
	if (BgType == MOVE)
	{
		//���Z�̒l���֐���
		m_Speed += (m_MoveSpeed + m_KillSpeed + m_AddSpeed);
	}
	else
	{	//���Z�̒l���֐���
		m_Speed += (m_MoveSpeed);
	}
	if (m_KillSpeed.x > 0.0f)
	{
		m_KillSpeed.x -= m_KillSpeed.x*0.01f;

		if (m_KillSpeed <= 0)
		{
			m_KillSpeed.x = 0;
		}
	}
	if (m_AddSpeed.x >  0.0f)
	{
		m_AddSpeed.x--;
		if (m_AddSpeed <= 0)
		{
			m_AddSpeed.x = 0;
		}
	}
	C3dpolygon::SetTex(PositionVec4(0.0f+ m_Speed.x, 1.0f+ m_Speed.x,0.0f + m_Speed.y,1.0f + m_Speed.y));
	C3dpolygon::Update();
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 1000.0f));
}

//------------------------------------
// �`��
//------------------------------------
void CBg::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CBg *CBg::Create()
{
	CBg * pObject = nullptr;
	pObject = new CBg(0);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f,0.0f));
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f,10200.0f));
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.5f));

	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CBg::GetPos() const
{
	return &m_pos;
}

void CBg::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

void CBg::SetMove(const D3DXVECTOR3 & move)
{
	m_MoveSpeed = move;
}

void CBg::SetKillMove(const D3DXVECTOR3 & move)
{
	m_KillSpeed = move;
}

D3DXVECTOR3 CBg::GetKillMove()
{
	return m_KillSpeed;
}
