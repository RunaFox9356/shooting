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
#include "game.h"
#include "bg.h"

#include "file.h"
#include "letter.h"

#include "hamada.h"



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
	CGame::GetBg(0)->SetMove(D3DXVECTOR3(-0.001f, 0.0f, 0.0f));

	CGame::GetBg(1)->SetMove(D3DXVECTOR3(-0.01f, 0.0f, 0.0f));

	m_PopPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Stop = false;
	m_Go = false;
	m_keepCount = 0;
	m_SamonEnemy = 0;

	CBg::SetKillMove(D3DXVECTOR3(0.05f, 0.0f, 0.0f));

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
	Move();

	m_motionType = CObject3d::ANIME_ATTACK;



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

//------------------------------------
// Move
//------------------------------------
void CBoss::Move(void)
{

	if (m_pos.x <= 300.0f&&!m_Go)
	{
		m_Stop = true;
		m_move.x = 0.5f;
	}
	if (m_Stop)
	{
		m_keepCount++;
		if (m_keepCount >= 60)
		{
			m_Stop = false;
			m_Go = true;
			m_move.x = -5.0f;
			m_Speed = 0.0f;
			for (int i = 0; i < 3; i++)
			{
				CEnemy * Enemy = CEnemy::Create(m_SamonEnemy);
				Enemy->SetUp(ENEMY);
				Enemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
				Enemy->SetPos(D3DXVECTOR3(SCREEN_WIDTH*0.5f + (50.0f*i), m_pos.y, 0.0f));
				Enemy->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
				Enemy->SetLife(30);
			}

		}
	}
	if (m_Go)
	{
		m_Speed += 0.05f;
		if (m_Speed >= 1.0f)
		{
			m_Speed = 1.0f;
		}
		m_move.x = -50.0f *  hmd::easeInSine(m_Speed);
	}
	

	if (m_pos.y < -SCREEN_HEIGHT / 2)
	{
		m_pos.y = SCREEN_HEIGHT / 2 ;
		m_move.y *= -1.0f;

	}

	if (m_pos.y > SCREEN_HEIGHT / 2 - 250.0f)
	{
		m_pos.y = -SCREEN_HEIGHT / 2-10.0f;
		m_move.y *= -1.0f;
		
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2)
	{
		m_pos.x = SCREEN_WIDTH;

		m_pos.y += SCREEN_HEIGHT / 5;
		m_Go = false;
		m_keepCount = 0;
		m_move.x = -5.0f;
	}


}

