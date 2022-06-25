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

//	Move();	//�����Z�b�g

//	Collision();//��

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
