//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "bell.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"
#include "file.h"
#include "letter.h"



//------------------------------------
// static�ϐ�
//------------------------------------
const float CBell::ATTENUATION = 0.5f;	// 
const float CBell::SPEED = 1.0f;			// �ړ���
const float CBell::WIDTH = 10.0f;			// ���f���̔��a
const int CBell::MAX_PRAYER = 16;			// �ő吔
const int CBell::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CBell::INVINCIBLE = 300;		// ���G����
const int CBell::MAX_COPY = 4;			// �ő�R�s�[��

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBell::CBell() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBell::~CBell()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBell::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Init();

      CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/item/Bell.txt");

	m_motionTypeOld = m_motionType;
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CBell::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CBell::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Update();

	m_pos += m_move;

	if (m_pos.x <= -SCREEN_WIDTH)
	{
		CObject::Release();
		//m_pos.x = SCREEN_WIDTH;
	}
}

//------------------------------------
// �`��
//------------------------------------
void CBell::Draw(void)
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBell *CBell::Create()
{
	CBell * pObject = nullptr;
	pObject = new CBell;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}



