//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "motion.h"
#include "object3d.h"

//------------------------------------
// static�ϐ�
//------------------------------------
const float CEnemy::ATTENUATION = 0.5f;	// 
const float CEnemy::SPEED = 1.0f;			// �ړ���
const float CEnemy::WIDTH = 10.0f;			// ���f���̔��a
const int CEnemy::MAX_PRAYER = 16;			// �ő吔
const int CEnemy::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CEnemy::INVINCIBLE = 300;		// ���G����
const int CEnemy::MAX_COPY = 4;			// �ő�R�s�[��

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CEnemy::CEnemy() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL)
{
	//memset(&s_Player, NULL, sizeof(s_Player));
	/*memset(&m_motion, 0, sizeof(m_motion));*/
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CEnemy::~CEnemy()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CEnemy::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Init();
	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				   D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		           "Data/system/enemy/FoxPoizun.txt");
	m_motionTypeOld = m_motionType;

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CEnemy::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CEnemy::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Update();

	//	Move();	//�����Z�b�g

	//	Collision();//��

}

//------------------------------------
// �`��
//------------------------------------
void CEnemy::Draw(void)
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CEnemy *CEnemy::Create()
{
	CEnemy * pObject = nullptr;
	pObject = new CEnemy;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;

}
