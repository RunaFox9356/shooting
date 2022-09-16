//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "bosscraziness.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"
#include "game.h"
#include "bg.h"

#include "file.h"
#include "letter.h"

#include "hamada.h"
#include "bossbar.h"
#include "manager.h"
#include "fade.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CBossCraziness::CBossCraziness()
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CBossCraziness::~CBossCraziness()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CBossCraziness::Init(void)
{
	// 現在のモーション番号の保管
	CEnemy::Init();
	CGame::GetBg(0)->SetMove(D3DXVECTOR3(-0.001f, 0.0f, 0.0f));

	CGame::GetBg(1)->SetMove(D3DXVECTOR3(-0.01f, 0.0f, 0.0f));

	m_PopPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);

	m_Stop = false;
	m_Go = false;
	m_keepCount = 0;
	m_SamonEnemy = 0;
	m_PatternCount = 0;
	m_RushCount = 0;
	m_PatternMode = MOVE;
	m_MaxLife = 3000;

	CBg::SetKillMove(D3DXVECTOR3(0.05f, 0.0f, 0.0f));

	m_Life = CBossbar::Create(D3DXVECTOR3(970.0f, 100.0f, 0.0f), 3000);

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 120.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/Kumakai.txt");

	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CBossCraziness::Uninit(void)
{
	// 現在のモーション番号の保管
	CEnemy::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CBossCraziness::Update(void)
{
	// 現在のモーション番号の保管
	CEnemy::Update();

	//ここにmoveをいれる
	Move();

	
}

//------------------------------------
// 描画
//------------------------------------
void CBossCraziness::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CBossCraziness *CBossCraziness::Create()
{
	CBossCraziness * pObject = nullptr;
	pObject = new CBossCraziness;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}

//------------------------------------
// Move
//------------------------------------
void CBossCraziness::Move(void)
{
	if (m_PatternMode == MOVE)
	{
		m_motionType = CObject3d::ANIME_RUN;
		if (m_pos.x <= 300.0f && !m_Go)
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
				m_PatternCount++;
				if (m_PatternCount >= 3)
				{
					m_PatternCount = 0;
					m_PatternMode = POP;

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
			m_pos.y = SCREEN_HEIGHT / 2;
			m_move.y *= -1.0f;

		}

		if (m_pos.y > SCREEN_HEIGHT / 2 - 250.0f)
		{
			m_pos.y = -SCREEN_HEIGHT / 2 - 250.0f;
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
	if (m_PatternMode == POP)
	{
		m_motionType = CObject3d::ANIME_ATTACK;
		m_keepCount++;

		if (m_keepCount >= 150)
		{
			m_keepCount = 0;
			for (int j = 0; j < 2; j++)
			{
				D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);
				m_PopPos.y *= -1.0f;
				for (int i = 0; i < 5; i++)
				{
					CEnemy * Enemy = CEnemy::Create(0);
					Enemy->SetUp(ENEMY);
					Enemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
					Enemy->SetPos(D3DXVECTOR3(m_PopPos.x + (i*50.0f), m_PopPos.y, 0.0f));
					Enemy->SetSize(Size);
					Enemy->SetLife(10);
				}
				for (int i = 0; i < 5; i++)
				{
					CEnemy * Enemy = CEnemy::Create(1);
					Enemy->SetUp(ENEMY);
					Enemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
					Enemy->SetPos(D3DXVECTOR3(m_PopPos.x + (i*80.0f), m_PopPos.y - 50.0f, 0.0f));
					Enemy->SetSize(Size);
					Enemy->SetLife(10);
				}
			}
			m_PatternCount++;
			if (m_PatternCount >= 2)
			{
				m_PatternCount = 0;
				m_PatternMode = RUSH;

			}
		}
	}
	if (m_PatternMode == RUSH)
	{

		m_Speed += 0.05f;
		if (m_Speed >= 1.0f)
		{
			m_Speed = 1.0f;
		}
		m_move.x = -50.0f *  hmd::easeInSine(m_Speed);

		if (m_pos.x <= -SCREEN_WIDTH / 2)
		{
			m_pos.x = SCREEN_WIDTH;
			m_pos.y += SCREEN_HEIGHT / 5;
			m_move.x = -5.0f;
			m_RushCount++;
			if (m_RushCount >= 3)
			{
				m_RushCount = 0;
				m_PatternMode = MOVE;
			}
		}
	}
}


//------------------------------------
// 特殊演出
//-----------------------------------
void CBossCraziness::OnHit()
{
	int Damage = m_MaxLife - GetLife();
	m_MaxLife = GetLife();
	m_Life->SetDamage(Damage);
	if (GetLife() <= 0)
	{
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
	}

}