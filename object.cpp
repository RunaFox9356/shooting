//=============================================================================
//
// Object
// Author : 浜田琉雅
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
// コンストラクト関数
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
// デストラクト関数
//=============================================================================
CObject::~CObject()
{

}


//=============================================================================
// AllUpdate関数
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
// AllDraw関数
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
// AllUninit関数
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
// AllCreate関数
//=============================================================================
void CObject::AllCreate()
{

	CMesh::Create();
	CPlayer::Create()->SetUp(PLAYER, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CEnemy::LoadEnemy("Data/datatest.json");
	pScore = CScore::Create();
	pScore->Set(0);
	pScore-> Add(20);

}

//=============================================================================
// Set関数
//=============================================================================
void CObject::SetUp(EObjectType Type, D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	switch (Type)
	{
	case EObjectType::ENEMY:
		m_pObject[m_nID]->SetMove(move);
		m_pObject[m_nID]->SetPos(pos);
		m_Type = ENEMY;
		break;
	case EObjectType::PLAYER:
		m_pObject[m_nID]->SetPos(pos);
		m_Type = PLAYER;
		break;
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
	default:
		break;
	}
	
}


//=============================================================================
// release関数
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
// objectのデータを取得する関数
//=============================================================================
CObject*CObject::GetObjectData(int nCount)
{
	return m_pObject[nCount];
}

//=============================================================================
// スコアのデータを取得する関数
//=============================================================================
CScore*CObject::GetScore()
{
	return pScore;
}

//=============================================================================
// objectのIdを取得する関数
//=============================================================================
int * CObject::GetId()
{
	return &m_nID;
}

//=============================================================================
// objectのタイプの取得関数
//=============================================================================
CObject::EObjectType CObject::GetType()
{
	return m_Type;
}
