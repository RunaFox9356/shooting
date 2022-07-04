//============================
//
// �v���C���[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "motion.h"
#include "object3d.h"
#include "bullet.h"
#include "enemy.h"	
//------------------------------------
// static�ϐ�
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// �ړ���
const float CPlayer::WIDTH = 10.0f;			// ���f���̔��a
const int CPlayer::MAX_PRAYER = 16;			// �ő吔
const int CPlayer::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CPlayer::INVINCIBLE = 300;		// ���G����
const int CPlayer::MAX_COPY = 4;			// �ő�R�s�[��
int DATA = 0;
//------------------------------------
// �R���X�g���N�^
//------------------------------------
CPlayer::CPlayer() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL)
{
	//memset(&s_Player, NULL, sizeof(s_Player));
	/*memset(&m_motion, 0, sizeof(m_motion));*/
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------
// ������
//------------------------------------
HRESULT CPlayer::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Init();
	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Data/system/Gon/Fox.txt");
	m_motionTypeOld = m_motionType;

	m_MoveSpeed = 3.0f;
	m_rot.y += (-D3DX_PI*0.5f);

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CPlayer::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CPlayer::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Update();

	Move();	//�����Z�b�g
	
	
	//Collision();//��

}

//------------------------------------
// �`��
//------------------------------------
void CPlayer::Draw(void)
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer;

	if (pObject != nullptr)
	{
		pObject->Init();

	}

	return pObject;
}

//------------------------------------
// Move
//------------------------------------
void CPlayer::Move()	//�����Z�b�g
{
	CInput *CInputpInput = CInput::GetKey();
	CAMERA *pCamera = GetCamera()->Get();
	float consumption = 0.0f;
	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		//CEnemy::Create()->SetUp(ENEMY, D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//CEnemy::Create()->SetUp(ENEMY, D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + pCamera->rot.y;

	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		
	
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{	
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{	
		m_move.y += m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
		DATA++;
		if (DATA == 20)
		{
			DATA = 0;
			CBullet::Create(m_pos, D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		}
	}
	
	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z


	//���K��
	if ( consumption > D3DX_PI)
	{
		 consumption += D3DX_PI * 2.0f;
	}
	if ( consumption < -D3DX_PI)
	{
		 consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

	 //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}