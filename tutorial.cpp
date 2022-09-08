//============================
//
// ���U���g���
// Author:hamada ryuuga
//
//============================




//------------------------
// �C���N���[�h
//------------------------
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "player.h"
#include "motion.h"
#include "bg.h"
#include "magic.h"
#include "particle_manager.h"
#include "score.h"
#include "life.h"

CMagicBox* CTutorial::m_MagicBox;	
CParticleManager* CTutorial::paticleManager;
CPlayer * CTutorial::m_Player;

//========================
// �R���X�g���N�^�[
//========================
CTutorial::CTutorial()
{
}

//========================
// �f�X�g���N�g
//========================
CTutorial::~CTutorial()
{
}

//========================
// ����������
//========================
HRESULT CTutorial::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 0.0f;
	m_Magic = 2;
	m_Bg[0] = CBg::Create();
	m_Bg[0]->SetTexture(CTexture::TEXTURE_TUTORIAL);
	m_Bg[0]->SetSize(CManager::Pos);
	m_Bg[0]->SetPos(BGPos);
	m_Bg[0]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_Player = nullptr;
	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);


	paticleManager = new CParticleManager;
	// �p�[�e�B�N��
	if (FAILED(paticleManager->Init()))
	{
		return E_FAIL;
	}

	CScore* pScore = CScore::Create(D3DXVECTOR3(900.0f, 100.0f, 0.0f));
	pScore->Set(0);

	CLife*pLife = CLife::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f));

	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(150.0f, 620.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_THUNDER);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_ICE);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_FIRE);

	return S_OK;

}

//========================
// �I������
//========================
void CTutorial::Uninit(void)
{
	CManager::GetSound()->Stop();
	
	if (m_Bg[0] != nullptr)
	{
		m_Bg[0]->Uninit();
	}
	

	if (m_MagicBox != nullptr)
	{
		m_MagicBox->Uninit();
		m_MagicBox = nullptr;
	}

	if (paticleManager != nullptr)
	{
		paticleManager->Uninit();
		delete paticleManager;
		paticleManager = nullptr;

	}


	CModelManager::ReleaseAll();
}

//========================
// �X�V����
//========================
void CTutorial::Update(void)
{
	
	paticleManager->Update();

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		//���[�h�̐ݒ�
		CManager::GetFade()->NextMode(CManager::MODE_TITLE);
	}

	if (CInputpInput->Trigger(CInput::KEY_RELOAD))
	{
		if (paticleManager->GetEmitter().size() == 0)
		{
			m_Magic++; 
			if (m_Magic >= 6)
			{
				m_Magic = 2;
			}
			m_MagicBox->CMagicBox::Magicplay((CTexture::TEXTURE)m_Magic);
		}

	}
#ifdef _DEBUG

	

#endif // DEBUG
}

//========================
// �`�揈��
//========================
void CTutorial::Draw(void)
{

}