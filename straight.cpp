//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "straight.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CStraight::CStraight()
{
	
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CStraight::~CStraight()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CStraight::Init()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/ponske.txt");


	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CStraight::Uninit()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CStraight::Update()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Update();


}

//------------------------------------
// �`��
//------------------------------------
void CStraight::Draw()
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CStraight *CStraight::Create()
{
	CStraight * pObject = nullptr;
	pObject = new CStraight;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}



