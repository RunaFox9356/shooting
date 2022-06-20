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

CObject *CObject::m_pObject[MAX_OBJECT] = {};
int CObject::m_AllMember = 0;

//=============================================================================
// コンストラクト関数
//=============================================================================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{

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
void CObject::AllCreate()
{
	// ポリゴンの初期化処理
	CObject2d::Create();	
	m_pObject[0]->SetPos(D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0.0f)));
	CObject2d::Create();
	m_pObject[1]->SetPos(D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, 0.0f)));
	CObject2d::Create();
	m_pObject[2]->SetPos(D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 0.0f)));
	CObject2d::Create();
	m_pObject[3]->SetPos(D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, 0.0f)));
	CPlayer::Create();
	
}

//=============================================================================
// reset関数
//=============================================================================
void CObject::release()
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