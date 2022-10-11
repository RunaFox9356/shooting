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
#include "sound.h"
#include "bg.h"

#include "pause.h"
#include "dangerous.h"
#include "text.h"

#include "bossdeath.h"
#include "words.h"

CMagicBox* CGame::m_MagicBox = nullptr;
CParticleManager*CGame::m_PaticleManager = nullptr;
CPlayer*CGame::m_Player = nullptr;
CPause *CGame::m_Pause = nullptr;
CMultiply* CGame::m_Multiply = nullptr;

//========================
// �R���X�g���N�^�[
//========================
CGame::CGame()
{
}
//========================
// �f�X�g���N�^
//========================
CGame::~CGame()
{
}

//========================
// �Q�[���̏���������
//========================
HRESULT CGame::Init(void)
{
	m_GameCount = 0;
	m_SpeedUp = 300;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	m_PaticleManager = new CParticleManager;
	// �p�[�e�B�N��
	if (FAILED(m_PaticleManager->Init()))
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

	SetBossPop(false);
	CManager::GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_Pause = new CPause;
	m_Pause->Init();
	m_Pause->SetUp(CObject::PAUSE);

	
	m_Multiply = CMultiply::Create(0, D3DXVECTOR3(150.0f, 200.0f, 0.0f),false,false);
	m_Multiply->SetRateFast(0);
	return S_OK;
}

//========================
// �Q�[���̏I������
//========================
void CGame::Uninit(void)
{
	CManager::GetSound()->Stop();
	CModelManager::ReleaseAll();
	
	CRanking::SetScore(CScore::GetScore());

	if (m_PaticleManager != nullptr)
	{
		m_PaticleManager->Uninit();
		delete m_PaticleManager;
		m_PaticleManager = nullptr;

	}

	if (m_MagicBox != nullptr)
	{
		m_MagicBox->Uninit();
		m_MagicBox = nullptr;
	}

	if (m_Pause != nullptr)
	{
		m_Pause->Uninit();
		m_Pause = nullptr;
	}

}

//========================
// �Q�[���̍X�V����
//========================
void CGame::Update(void)
{
	m_GameCount++;
	// �X�V����
	if (m_GameCount == m_SpeedUp&&!GetMaxBoss())
	{
		m_GameCount = 0;
		m_SpeedUp += 250;
		CBg::SetKillMove(D3DXVECTOR3(0.05f, 0.0f, 0.0f));
	}

	CInput *CInputpInput = CInput::GetKey();

#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CWords::Create("��", D3DXVECTOR3(450, 300, 0), D3DXVECTOR3(100, 100, 0), CFont::FONT::FONT_GON);
		CWords::Create("��", D3DXVECTOR3(650, 300, 0), D3DXVECTOR3(100, 200, 0), CFont::FONT::FONT_MEIRIO);
		CWords::Create("��", D3DXVECTOR3(850, 300, 0), D3DXVECTOR3(100, 100, 0), CFont::FONT::FONT_SOUEIKAKU);
		//CManager::GetFade()->NextMode(CManager::MODE_RESULT);
		//CManager::SetMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{


		//CDeathManager::Create(10, 25);
		//CText::Create(CText::GON,120, 10, "�����n�����̂���...");
		//CDangerousManager::BossPopStaging();
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}

#endif // DEBUG
	if (GetMaxEnemy() <= 0)
	{
		if (GetMaxBoss())
		{
		}
		else
		{
			CDangerousManager::BossPopStaging(); 
		}
	
	}
	m_PaticleManager->Update();
}

//========================
// �Q�[���̕`�揈��
//========================
void CGame::Draw(void)
{
	// �X�V����
	//CManager::GetRenderer()->Draw();
}

