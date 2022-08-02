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
#include "score.h"
#include "player.h"
#include "multiply.h"


const int CBell::BOUNDPOWER = 10;

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBell::CBell() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL),
	m_bound(BOUNDPOWER),
	m_dist(false)
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
	for (int i = 0; i < MAX_OBJECT; i++)
	{	// �����蔻��
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::PLAYER)
			{	// Player�Ƃ̓����蔻��
				CPlayer* cPlayer = dynamic_cast<CPlayer*>(pObject);  // �_�E���L���X�g
				const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
				float Size = 30.0f;

				D3DXVECTOR3 vecPlayerDist = *PlayerPos - m_pos;
				float distPlayer = D3DXVec3Length(&vecPlayerDist);
				if ((PlayerPos->y >= 50.0f|| PlayerPos->y <= -270.0f)&& 620.0f >= m_pos.x)
				{
					m_dist = true;
				}
				if (m_dist)
				{
					m_pos += vecPlayerDist / distPlayer * 30.0f;
				}
				if (distPlayer <= 1.0f)
				{
					m_pos = *PlayerPos;
					
				}
				if (((m_pos.y - Size) <= (PlayerPos->y + Size)) &&
					((m_pos.y + Size) >= (PlayerPos->y - Size)) &&
					((m_pos.x - Size) <= (PlayerPos->x + Size)) &&
					((m_pos.x + Size) >= (PlayerPos->x - Size)))
				{
					
					GetScore()->Add(10 * (*CMultiply::GetRate()+1));
					
					CObject::Release();

					return;
				}
			}
		}
	}
	if (!m_dist)
	{
		
		m_move.y -= 0.5f;
		if (m_pos.y <= -360.0f)
		{
			m_pos.y = -360.0f;
			m_move.y = (-m_move.y)*((rand() % 5 + 1)*0.1f);
			if (m_move.y <= 1.0f)
			{
				m_move.y = 0;
			}
		}
	}

	if (m_pos.x <= -1280.0f)
	{
		CObject::Release();
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



