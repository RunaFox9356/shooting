//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "maruneko.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CMaru::CMaru()
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CMaru::~CMaru()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CMaru::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/neko.txt");

	backOn = false;
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CMaru::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CMaru::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Update();

	if (m_pos.x <= CManager::Pos.x/4)
	{
		//������move�������
		m_move.x++;
		backOn = true;
	}

	if (m_pos.x >= CManager::Pos.x  && backOn)
	{
		//������move�������
		Uninit();
	}
}

//------------------------------------
// �`��
//------------------------------------
void CMaru::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CMaru *CMaru::Create()
{
	CMaru * pObject = nullptr;
	pObject = new CMaru;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}
