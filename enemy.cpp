//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "enemy.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"
#include "raccoon.h"
#include "straight.h"
#include "file.h"
#include "letter.h"
#include "player.h"
#include "game.h"
#include "life.h"
#include "boss.h"
#include "snake.h"
#include "maruneko.h"
#include "life.h"
#include "bosscraziness.h"

namespace nl = nlohmann;

static nl::json EnemyList;//リストの生成


//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CEnemy::Init()
{
	// 現在のモーション番号の保管
	CObject3d::Init();

	m_motionTypeOld = m_motionType;
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CEnemy::Uninit()
{
	m_AllEnemy--;
	
	// 現在のモーション番号の保管
	CObject3d::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CEnemy::Update()
{
		// 現在のモーション番号の保管
		CObject3d::Update();

		m_motionType = CObject3d::ANIME_RUN;

	
		switch (*CManager::GetMode())
		{
		case CManager::MODE_TITLE:
			TitleMove();	//動きセット
			break;
		case CManager::MODE_GAME:

			if (CLife::GetMaxLife())
			{
				Move();	//動きセット
				Collision();
			}
			break;

		case CManager::MODE_RESULT:
			ResetMove();
			break;
		case CManager::MODE_RANKING:
			break;
		case CManager::MODE_TUTORIAL:
			Move();	//動きセット
			break;
		default:
			break;
		}
}

//=============================================================================
// 描画
//=============================================================================
void CEnemy::Draw()
{
	CObject3d::Draw();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CEnemy::Collision()
{

	CPlayer* cPlayer = CGame::GetPlayer();
	const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
	float Size = 30.0f;
	
	if (cPlayer->GetDamegeData() == DAMEGE_NORMAL)
	{
		if (((m_pos.y - Size) <= (PlayerPos->y + Size)) &&
			((m_pos.y + Size) >= (PlayerPos->y - Size)) &&
			((m_pos.x - Size) <= (PlayerPos->x + Size)) &&
			((m_pos.x + Size) >= (PlayerPos->x - Size)))
		{

			CObject::GetLife()->CLife::SetDamage(50);

			return;
		}
	}
}

//=============================================================================
// create
//=============================================================================
CEnemy *CEnemy::Create(const int Type)
{
	CEnemy * pObject = nullptr;

	switch (Type)
	{
	case TYPE_RACCOONL:
		pObject = new CRaccoon;
		break;
	case TYPE_NEKO:
		pObject = new CStraight;
		break;
	case TYPE_SNAKE:
		pObject = new CSnake;
		break;
	case TYPE_MARU:
		pObject = new CMaru;
		break;
	case TYPE_BOSS:
		pObject = new CBoss;
		break;
	case TYPE_CRAZINESS:
		pObject = new CBossCraziness;
		break;
	default:
		pObject = new CRaccoon;
		break;
	}

	pObject->m_EnemyType = (TYPE)Type;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}
//=============================================================================
// Boss
//=============================================================================
void CEnemy::SetBoss()
{
	D3DXVECTOR3 Size(5.0f, 5.0f, 5.0f);
	CEnemy * Model = CEnemy::Create(TYPE_BOSS);
	Model->SetUp(ENEMY);
	Model->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	Model->SetPos(D3DXVECTOR3(CManager::Pos.x*3.5f, 0.0f,0.0f));
	Model->SetSize(Size);
	Model->SetLife(3000);
	
}

//=============================================================================
// Boss
//=============================================================================
void CEnemy::SetBossCraziness()
{
	D3DXVECTOR3 Size(5.0f, 5.0f, 5.0f);
	CEnemy * Model = CEnemy::Create(TYPE_CRAZINESS);
	Model->SetUp(ENEMY);
	Model->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	Model->SetPos(D3DXVECTOR3(CManager::Pos.x*3.5f, 350.0f, 0.0f));
	Model->SetSize(Size);
	Model->SetLife(3000);

}

//=============================================================================
// Load
//=============================================================================
void  CEnemy::LoadEnemy(const char * pFdata)
{
	std::ifstream ifs(pFdata);
	
	int nIndex = 0;
	
	if (ifs)
	{
		ifs >> EnemyList;
		nIndex = EnemyList["INDEX"];
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
		int Life;
		int Type;
		for (int nCntEnemy = 0; nCntEnemy < nIndex; nCntEnemy++)
		{
			std::string name = "ENEMY";
			std::string Number = std::to_string(nCntEnemy);
			name += Number;
			
			pos = D3DXVECTOR3(EnemyList[name]["POS"]["X"], EnemyList[name]["POS"]["Y"], EnemyList[name]["POS"]["Z"]);
			size = D3DXVECTOR3(EnemyList[name]["SIZE"]["X"], EnemyList[name]["SIZE"]["Y"], EnemyList[name]["SIZE"]["Z"]);
			rot = D3DXVECTOR3(EnemyList[name]["ROT"]["X"], EnemyList[name]["ROT"]["Y"], EnemyList[name]["ROT"]["Z"]);
			Life = EnemyList[name]["LIFE"];
			Type = EnemyList[name]["TYPE"];
			
			CEnemy * Enemy = CEnemy::Create(Type);
			Enemy->SetUp(ENEMY); 
			Enemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
			Enemy->SetPos(pos);
			Enemy->SetSize(size);
			Enemy->SetLife(10* (int)size.x);
		}
	}
}



//=============================================================================
// TitleのときのMove
//=============================================================================
void CEnemy::TitleMove()
{
	m_pos.x += m_move.x;

//  if (m_pos.y < -SCREEN_HEIGHT*0.5f)
//	{
//		m_pos.y = (SCREEN_HEIGHT *0.5f) - 100.0f;
//	}
	if (m_pos.y > SCREEN_HEIGHT *0.5f - 100.0f)
	{
		m_pos.y = -SCREEN_HEIGHT*0.5f;
	}

	if (m_pos.x <= -SCREEN_WIDTH*0.5f - 200.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f + 200.0f;
	}
	

}
//=============================================================================
// Move
//=============================================================================
void CEnemy::Move(void)
{
	
		if (m_pos.x <= SCREEN_WIDTH / 2)
		{
			m_pos += m_move;
		}
		else
		{
			m_pos.x += -5.0f;
		}
		if (m_pos.x <= -SCREEN_WIDTH)
		{
			Uninit();
			//m_pos.x = SCREEN_WIDTH;
		}
	
}
//=============================================================================
// TitleのときのMove
//=============================================================================
void CEnemy::ResetMove()
{
	m_pos.x += m_move.x;

	//  if (m_pos.y < -SCREEN_HEIGHT*0.5f)
	//	{
	//		m_pos.y = (SCREEN_HEIGHT *0.5f) - 100.0f;
	//	}
	if (m_pos.y > SCREEN_HEIGHT *0.5f - 100.0f)
	{
		m_pos.y = -SCREEN_HEIGHT*0.5f;
	}

	if (m_pos.x <= -SCREEN_WIDTH*0.5f - 200.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f + 200.0f;
	}
}
