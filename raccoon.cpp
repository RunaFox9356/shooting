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
	m_counter = 50;
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

	if (m_pos.x <= SCREEN_WIDTH / 2)
	{
		EnemyPattern4();
	}

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

//------------------------------------
// �~�������Ĉړ�
//------------------------------------
void CRaccoon::EnemyPattern4()
{
	m_counter++;
	
	m_move.y = -sin(D3DX_PI*(m_counter - 100.0f) / 50.0f)*2.5f;
	m_move.x = -5.0f;
	
	m_pos += m_move;
}