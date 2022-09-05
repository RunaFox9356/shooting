//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "boss.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBoss::CBoss()
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBoss::~CBoss()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBoss::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/kuma.txt");

	m_rot.y += -(D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CBoss::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Uninit();

}

//------------------------------------
// �X�V
//------------------------------------
void CBoss::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CEnemy::Update();

	//������move�������
	m_motionType = CObject3d::ANIME_ATTACK;

	if (m_pos.y <= -SCREEN_HEIGHT / 2)
	{
		m_pos.y = SCREEN_HEIGHT / 2;
		m_move.y *= -1.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2-250.0f)
	{
		m_pos.y = -SCREEN_HEIGHT / 2;
		m_move.y *= -1.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2)
	{
		m_pos.x = SCREEN_WIDTH;

		m_pos.y += SCREEN_HEIGHT / 5;
	}
}

//------------------------------------
// �`��
//------------------------------------
void CBoss::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CBoss *CBoss::Create()
{
	CBoss * pObject = nullptr;
	pObject = new CBoss;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}

