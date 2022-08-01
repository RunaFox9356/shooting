//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "object2d.h"
#include "player.h"
#include "manager.h"
#include "enemy.h"
#include "gon.h"
#include "bullet.h"
#include "mesh.h"
#include "magic.h"
#include "score.h"


CObject *CObject::m_pObject[MAX_OBJECT] = {};
int CObject::m_AllMember = 0;
CScore * pScore;
//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{
			m_Type = NONE;
			m_nID = i;
			m_pObject[i] = this;
			m_AllMember++;
			break;
		}
	}
}
//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CObject::~CObject()
{

}


//=============================================================================
// AllUpdate�֐�
//=============================================================================
void CObject::AllUpdate()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Update();
		}
	}
}
//=============================================================================
// AllDraw�֐�
//=============================================================================
void CObject::AllDraw()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Draw();
		}

	}
}

//=============================================================================
// NotBGDraw�֐�
//=============================================================================
void CObject::TypeDraw(EObjectType Type)
{
	
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (Type == BG)
		{
			if (m_pObject[i] != nullptr)
			{
				if (m_pObject[i]->m_Type == BG)
				{
					m_pObject[i]->Draw();
				}
			}
		}
		else
		{
			if (m_pObject[i] != nullptr)
			{
				if (m_pObject[i]->m_Type != BG)
				{
					m_pObject[i]->Draw();
				}
			}
		}
	}
}


//=============================================================================
// AllUninit�֐�
//=============================================================================
void CObject::AllUninit()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Uninit();
			delete m_pObject[i];
			m_pObject[i] = nullptr;
		}

	}
	m_AllMember = 0;
}

//=============================================================================
// ModeNotUninit�֐�
//=============================================================================
void CObject::ModeNotUninit()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			if (m_pObject[i]->m_Type != MODE)
			{
				m_pObject[i]->Uninit();
				delete m_pObject[i];
				m_pObject[i] = nullptr;
			}
		}
	}
	m_AllMember = 1;
}
//=============================================================================
// AllCreate�֐�
//=============================================================================
void CObject::AllCreate()
{

	CMesh::Create();
	CEnemy::LoadEnemy("Data/datatest.json");
	pScore = CScore::Create();
	pScore->Set(0);
	

}

//=============================================================================
// Set�֐�
//=============================================================================
void CObject::SetUp(EObjectType Type)
{
	switch (Type)
	{
	case EObjectType::ENEMY:
	{
		m_Type = ENEMY;
		break;
	}
	case EObjectType::PLAYER:
	{
		m_Type = PLAYER;
		break;
	}
	case EObjectType::BULLET:
		m_Type = BULLET;
		break;
	case EObjectType::GON:
		m_Type = GON;
		break;
	case EObjectType::MAGIC:
		m_Type = MAGIC;
		break;
	case EObjectType::CRYSTAL:
		m_Type = CRYSTAL;
		break;
	case EObjectType::BG:
		m_Type = BG;
		
		break;	
	case EObjectType::MODE:
			m_Type = MODE;

			break;
	default:
		break;
	}
	
}


//=============================================================================
// release�֐�
//=============================================================================
void CObject::Release()
{
	if (m_pObject[m_nID] != nullptr)
	{
		const int nID = m_nID;
		m_pObject[nID]->Uninit();
		delete m_pObject[nID];
		m_pObject[nID] = nullptr;
		m_AllMember--;
	}
}

//=============================================================================
// object�̃f�[�^���擾����֐�
//=============================================================================
CObject*CObject::GetObjectData(int nCount)
{
	return m_pObject[nCount];
}

//=============================================================================
// �X�R�A�̃f�[�^���擾����֐�
//=============================================================================
CScore*CObject::GetScore()
{
	return pScore;
}

//=============================================================================
// object��Id���擾����֐�
//=============================================================================
int * CObject::GetId()
{
	return &m_nID;
}

//=============================================================================
// object�̃^�C�v�̎擾�֐�
//=============================================================================
CObject::EObjectType CObject::GetType()
{
	return m_Type;
}
