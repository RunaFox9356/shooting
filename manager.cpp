//=============================================================================
//
// �}�l�[�W���[
// Author : �l�c����
//
//=============================================================================

#include "manager.h"
#include "main.h"
#include "object.h"
#include "light.h"
#include "player.h"
#include "renderer.h"
#include "input.h"
#include "file.h"
#include "bullet.h"
#include "texture.h"
#include "magic.h"
#include "game.h"
#include "title.h"
#include "result.h"

CRenderer * CManager::m_cRenderer = nullptr; 
CTexture * CManager::m_pTexture = nullptr;
CMagicBox* CManager::m_MagicBox = nullptr;
CObject*CManager::m_Game = nullptr;

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CManager::CManager()
{

}
//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	
	m_cRenderer = new CRenderer;
	m_Input = CInput::Create();

	// ����������
	if (FAILED(m_cRenderer->Init(hWnd, TRUE)))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return -1;
	}
	//���͏����̏���������
	if (FAILED(m_Input->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pTexture = nullptr;
	m_pTexture = new CTexture;
	
	m_mode = CManager::MODE_TITLE;	//���݂̃��[�h

	//���[�h�̐ݒ�
	SetMode(m_mode);

	CObject::AllCreate();


	
	CObject::AllCreate();
	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(100.0f, 650.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_NONE);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CManager::Uninit()
{
	// �|���S���̏I������
	CObject::AllUninit();

	if (m_pTexture != nullptr)
	{// �I������

		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_cRenderer != nullptr)
	{// �I������

		m_cRenderer->Uninit();
		delete m_cRenderer;
		m_cRenderer = nullptr;
	}
	//���͏����̏I������
	m_Input->Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CManager::Update()
{
	//���͏����̍X�V����
	m_Input->Update();

	// �X�V����
	m_cRenderer->Update();


}

//=============================================================================
// �`��
//=============================================================================
void CManager::Draw()
{
	// �`�揈��
	m_cRenderer->Draw();

}


//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_cRenderer;
}


//=============================================================================
// GetTexture
//=============================================================================
CTexture *CManager::GetTexture()
{
	return m_pTexture;
}

CMagicBox* CManager::GetMagicBox()
{
	return m_MagicBox;
}

//========================
// ���[�h�̐ݒ�
//========================
void CManager::SetMode(MODE mode)
{
	if (m_Game != nullptr)
	{
		m_Game->Uninit();
		delete m_Game;
		m_Game = nullptr;
	}

	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_Game = new CTitle;
		break;
	case CManager::MODE_GAME:
		m_Game = new CGame;
		break;
	case CManager::MODE_RESULT:
		m_Game = new CResult;
		break;
	default:
		break;
	}

	if (FAILED(m_Game->Init()))
	{
		return;
	}
}

