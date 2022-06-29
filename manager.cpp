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

CRenderer * CManager::m_cRenderer = nullptr; 
CTexture * CManager::m_pTexture = nullptr;
static float s_fAngle = 20.0f;

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
	
	CBullet::Lood();
	CObject::AllCreate();



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