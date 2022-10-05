//=============================================================================
//
// ���@�w
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "magiccircle.h"
#include "manager.h"
#include "magic.h"
#include "utility.h"
#include "camera.h"
#include "hamada.h"
#include "hit.h"
#include "player.h"
#include "game.h"
#include "particle_manager.h"
#include "tutorial.h"

int CMagicCircleManager::CMagicCircle::m_popType = 2;

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CMagicCircleManager::CMagicCircle::CMagicCircle() :C3dpolygon(1)
{
}

//=============================================================================
// �f�X�g���N�^�֐�
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

	CParticleManager* particleManager = nullptr;


	CPlayer* cPlayer = nullptr;
	if (*CManager::GetMode() == CManager::MODE_GAME)
	{
		cPlayer = CGame::GetPlayer();  // �_�E���L���X�g
		particleManager = CGame::GetParticleManager();
		
	}
	else if (*CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		cPlayer = CTutorial::GetPlayer();  // �_�E���L���X�g
		particleManager = CTutorial::GetParticleManager();
	}

	const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
	
	SetPos(*PlayerPos);


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
CMagicCircleManager::CMagicCircle *CMagicCircleManager::CMagicCircle::Create(D3DXVECTOR3 pos)
{
	CMagicCircle * pObject = nullptr;
	pObject = new CMagicCircle;

	if (pObject != nullptr)
	{
		pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
		pObject->Init();
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
		object->MagicCircle[i] = CMagicCircle::Create(pos);

		if (object->MagicCircle[i] != nullptr)
		{
			object->MagicCircle[i]->Init();
			object->MagicCircle[i]->SetPos(pos);
			object->MagicCircle[i]->SetDecreasingRate(30.0f + (20.0f*i));
			object->MagicCircle[i]->SetTexture((CTexture::TEXTURE)((int)CTexture::TEXTURE_MAGICCIRCLE1 + rand() % 4 + 0));
			object->MagicCircle[i]->SetSize(D3DXVECTOR3(1.0f + (10.0f*i), 1.0f + (10.0f*i), 0.0f));
			object->MagicCircle[i]->SetDefaultSize(D3DXVECTOR3(100.0f + (70.0f*i), 100.0f + (70.0f * i), 0.0f));
			//object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			//�F�̐ݒ�

			if (*CManager::GetMode() == CManager::MODE_GAME)
			{
				switch (CGame::GetMagicBox()->GetcMagic(i).GetTexture())
				{
				case CTexture::TEXTURE_FIRE:
					object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 0.2f, 0.2f, 0.8f));
					break;
				case CTexture::TEXTURE_ICE:
					object->MagicCircle[i]->SetColar(PositionVec4(0.2f, 0.2f, 1.0f, 0.8f));
					break;
				case CTexture::TEXTURE_STORM:
					object->MagicCircle[i]->SetColar(PositionVec4(0.0f, 1.0f, 0.2f, 0.8f));
					break;
				case CTexture::TEXTURE_THUNDER:
					object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 1.0f, 0.2f, 0.8f));
					break;
				default:
					object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
					break;
				}
			}
			else if (*CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				switch (CTutorial::GetMagicBox()->GetcMagic(i).GetTexture())
				{
				case CTexture::TEXTURE_FIRE:
					object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 0.2f, 0.2f, 0.8f));
					break;
				case CTexture::TEXTURE_ICE:
					object->MagicCircle[i]->SetColar(PositionVec4(0.2f, 0.2f, 1.0f, 0.8f));
					break;
				case CTexture::TEXTURE_STORM:
					object->MagicCircle[i]->SetColar(PositionVec4(0.0f, 1.0f, 0.2f, 0.8f));
					break;
				case CTexture::TEXTURE_THUNDER:
					object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 1.0f, 0.2f, 0.8f));
					break;
				default:
					object->MagicCircle[i]->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
					break;
				}
			}
			else
			{
				object = nullptr;
			}




		}

		
	}
	return object;
}