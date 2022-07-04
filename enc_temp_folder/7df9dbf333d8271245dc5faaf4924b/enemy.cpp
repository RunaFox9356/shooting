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



#include "file.h"
#include "letter.h"


//Particle DataEffect;
namespace nl = nlohmann;

static nl::json j;//���X�g�̐���

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
	m_rot.y += (D3DX_PI*0.5f);
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

	m_pos += m_move;

	if (m_pos.x <= -SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH;
	}
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
void  CEnemy::LoadEnemy(const char * pFdata)
{
	std::ifstream ifs(pFdata);

	int nIndex = 0;

	if (ifs)
	{
		ifs >> j;
		nIndex = j["INDEX"];
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
		for (int nCntEnemy = 0; nCntEnemy < nIndex; nCntEnemy++)
		{
			std::string name = "ENEMY";
			std::string Number = std::to_string(nCntEnemy);
			name += Number;
			
			pos = D3DXVECTOR3(j[name]["POS"]["X"], j[name]["POS"]["Y"], j[name]["POS"]["Z"]);
			size = D3DXVECTOR3(j[name]["SIZE"]["X"], j[name]["SIZE"]["Y"], j[name]["SIZE"]["Z"]);
			rot = D3DXVECTOR3(j[name]["ROT"]["X"], j[name]["ROT"]["Y"], j[name]["ROT"]["Z"]);
			
			CEnemy::Create()->SetUp(ENEMY, pos, D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
			
		}
	}
}