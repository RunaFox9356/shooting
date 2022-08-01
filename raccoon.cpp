//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "raccoon.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CRaccoon::CRaccoon() 
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CRaccoon::~CRaccoon()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CRaccoon::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/Raccoon.txt");

	
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CRaccoon::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CRaccoon::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Update();

	//������move�������

}

//------------------------------------
// �`��
//------------------------------------
void CRaccoon::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CRaccoon *CRaccoon::Create()
{
	CRaccoon * pObject = nullptr;
	pObject = new CRaccoon;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}



