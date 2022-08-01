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

#include "multiply.h"
#include "particle_manager.h"

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

	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(100.0f, 650.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_THUNDER);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_ICE);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_FIRE);

	//CMultiply::FastSet(0, D3DXVECTOR3(100.0f, 200.0f, 0.0f));

	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	return S_OK;
}

//========================
// �Q�[���̏I������
//========================
void CGame::Uninit(void)
{
	// �|���S���̏I������
	CObject::ModeNotUninit();
}

//========================
// �Q�[���̍X�V����
//========================
void CGame::Update(void)
{
	// �X�V����
	//CManager::GetRenderer()->Update();
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::SetMode(CManager::MODE_RESULT);
	}
	paticleManager->Update();
}

//========================
// �Q�[���̕`�揈��
//========================
void CGame::Draw(void)
{
	// �X�V����
	CManager::GetRenderer()->Draw();
}

CMagicBox* CGame::GetMagicBox()
{
	return m_MagicBox;
}
