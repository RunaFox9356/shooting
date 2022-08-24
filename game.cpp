//============================
//
// �Q�[�����
// Author:hamada ryuuga
//
//============================

//------------------------
// �C���N���[�h
//------------------------
#include "game.h"
#include "input.h"
#include "manager.h"
#include "object.h"
#include "light.h"
#include "player.h"
#include "file.h"
#include "bullet.h"

#include "magic.h"
#include "enemy.h"
#include "fade.h"

#include "multiply.h"
#include "particle_manager.h"
#include "ranking.h"

#include "score.h"

CMagicBox* CGame::m_MagicBox = nullptr;
CParticleManager*CGame::paticleManager = nullptr;
CPlayer*CGame::m_Player = nullptr;

//========================
// �R���X�g���N�^�[
//========================
CGame::CGame()
{
}
//========================
// �f�X�g���N�g
//========================
CGame::~CGame()
{
}

//========================
// �Q�[���̏���������
//========================
HRESULT CGame::Init(void)
{

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	paticleManager = new CParticleManager;
	// �p�[�e�B�N��
	if (FAILED(paticleManager->Init()))
	{
		return E_FAIL;
	}

	CObject::AllCreate();

	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(150.0f, 620.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_THUNDER);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_ICE);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_FIRE);


	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);
	
	return S_OK;
}

//========================
// �Q�[���̏I������
//========================
void CGame::Uninit(void)
{
	CModelManager::ReleaseAll();
	CRanking::SetScore(CScore::GetScore());
}

//========================
// �Q�[���̍X�V����
//========================
void CGame::Update(void)
{
	// �X�V����

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::GetFade()->NextMode(CManager::MODE_RESULT);
		//CManager::SetMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//���[�h�̐ݒ�
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}
	if (GetMaxEnemy() <= 0)
	{
		if (GetMaxBoss())
		{
			//���[�h�̐ݒ�

			CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
			return;
		}
		CEnemy::SetBoss();
	
	}
	paticleManager->Update();
}

//========================
// �Q�[���̕`�揈��
//========================
void CGame::Draw(void)
{
	// �X�V����
	//CManager::GetRenderer()->Draw();
}
