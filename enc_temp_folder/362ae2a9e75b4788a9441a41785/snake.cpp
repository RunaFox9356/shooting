//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "snake.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CSnake::CSnake()
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CSnake::~CSnake()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CSnake::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/snake.txt");


	m_rot.y -= (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CSnake::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Uninit();

}

//------------------------------------
// �X�V
//------------------------------------
void CSnake::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Update();
	m_motionType = CObject3d::ANIME_NORMAL;
}

//------------------------------------
// �`��
//------------------------------------
void CSnake::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CSnake *CSnake::Create()
{
	CSnake * pObject = nullptr;
	pObject = new CSnake;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}

