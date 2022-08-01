//**************************************************
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"

//========================
// �R���X�g���N�^�[
//========================
CTitle::CTitle()
{
}
//========================
// �f�X�g���N�g
//========================
CTitle::~CTitle()
{
}

//================
//����������
//================
HRESULT CTitle::Init(void)
{
	return S_OK;
}

//�j��
void CTitle::Uninit(void)
{


	
}
//==================
//�X�V����
//==================
void CTitle::Update(void)
{
#ifdef _DEBUG

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::SetMode(CManager::MODE_GAME);
	}

	/*if (GetKeyboardPress(DIK_0))
	{
		SetFade(MODE_RESULT);
	}
	if (GetKeyboardPress(DIK_9))
	{
		SetFade(MODE_GAME);
	}*/

#endif // DEBUG
}
//==================
//�`�揈��
//==================
void CTitle::Draw(void)
{

}