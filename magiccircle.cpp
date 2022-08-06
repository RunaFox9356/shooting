//=============================================================================
//
// CRYSTAL
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "magiccircle.h"
#include "manager.h"
#include "utility.h"
#include "camera.h"
#include "hamada.h"
#include "hit.h"
#include "player.h"
#include "game.h"
#include "particle_manager.h"
int CMagicCircleManager::CMagicCircle::m_popType = 2;

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CMagicCircleManager::CMagicCircle::CMagicCircle() :C3dpolygon(1)
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CMagicCircleManager::CMagicCircle::~CMagicCircle()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CMagicCircleManager::CMagicCircle::Init()
{
	C3dpolygon::Init();
	m_isEndAnimation = true;

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CMagicCircleManager::CMagicCircle::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CMagicCircleManager::CMagicCircle::Update()
{
	C3dpolygon::Update();

	if (m_Size.x <= m_DefaultSize.x)
	{
		m_Size += m_DefaultSize / m_DecreasingRate;
		m_nTimer++;
		SetSize(m_Size);
	}
	CPlayer* cPlayer = CGame::GetPlayer();  // �_�E���L���X�g
	const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
	m_pos = *PlayerPos;

	CParticleManager* particleManager = CGame::GetParticleManager();
	if (particleManager->GetEmitter().size() == 0)
	{
		m_isEndAnimation = false;
	}
	if (!m_isEndAnimation)
	{
		m_Size -= m_DefaultSize / (m_DecreasingRate*0.5f);

		if (m_Size.x <= 0.0f)
		{
			Release();
		}
	}

}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CMagicCircleManager::CMagicCircle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);

	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create�֐�
//=============================================================================
CMagicCircleManager::CMagicCircle *CMagicCircleManager::CMagicCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CMagicCircle * pObject = nullptr;
	pObject = new CMagicCircle;

	if (pObject != nullptr)
	{
		pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
		pObject->Init();

		//�o�Ă���^�C�v�̐ݒ�
		m_popType++;

		if (m_popType >= 6)
		{
			m_popType = 2;
		}

		pObject->SetType(m_popType);

		//�F�̐ݒ�
		switch (m_popType)
		{
		case NOW_FIRE:
			pObject->SetCollar(PositionVec4(1.0f, 0.0f, 0.0f, 0.8f));
			break;
		case NOW_ICE:
			pObject->SetCollar(PositionVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case NOW_STORM:
			pObject->SetCollar(PositionVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case NOW_SUN:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		default:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			break;
		}
	}

	return pObject;
}
//=============================================================================
// Setmove�֐�
//=============================================================================
void CMagicCircleManager::CMagicCircle::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// SetType�֐�
//=============================================================================
void CMagicCircleManager::CMagicCircle::SetType(const int&myType)
{
	m_myType = myType;
}

//=============================================================================
// create�֐�
//=============================================================================
CMagicCircleManager * CMagicCircleManager::Create(D3DXVECTOR3 pos)
{

	CMagicCircleManager*object = nullptr;
	object = new CMagicCircleManager;

	for (int i = 0; i < 3; i++)
	{
		object->MagicCircle[i] = nullptr;
		object->MagicCircle[i] = CMagicCircle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		
		if (object->MagicCircle[i] != nullptr)
		{
			object->MagicCircle[i]->Init();
			object->MagicCircle[i]->SetPos(pos);
			object->MagicCircle[i]->SetDecreasingRate(30.0f + (20.0f*i));
			object->MagicCircle[i]->SetTexture((CTexture::TEXTURE)((int)CTexture::TEXTURE_MAGICCIRCLE1+ rand() % 4 + 0));
			object->MagicCircle[i]->SetSize(D3DXVECTOR3(1.0f + (10.0f*i), 1.0f + (10.0f*i), 0.0f));
			object->MagicCircle[i]->SetDefaultSize(D3DXVECTOR3(100.0f+(70.0f*i), 100.0f + (70.0f * i), 0.0f));
			object->MagicCircle[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));

		}
	}

	return object;
}
