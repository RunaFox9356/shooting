//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "boss.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CBoss::CBoss()
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CBoss::~CBoss()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CBoss::Init(void)
{
	// 現在のモーション番号の保管
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/kuma.txt");

	m_rot.y += -(D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CBoss::Uninit(void)
{
	// 現在のモーション番号の保管
	CEnemy::Uninit();

}

//------------------------------------
// 更新
//------------------------------------
void CBoss::Update(void)
{
	// 現在のモーション番号の保管
	CEnemy::Update();

	//ここにmoveをいれる
	m_motionType = CObject3d::ANIME_ATTACK;

	if (m_pos.y <= -SCREEN_HEIGHT / 2)
	{
		m_pos.y = SCREEN_HEIGHT / 2;
		m_move.y *= -1.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2-250.0f)
	{
		m_pos.y = -SCREEN_HEIGHT / 2;
		m_move.y *= -1.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2)
	{
		m_pos.x = SCREEN_WIDTH;

		m_pos.y += SCREEN_HEIGHT / 5;
	}
}

//------------------------------------
// 描画
//------------------------------------
void CBoss::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CBoss *CBoss::Create()
{
	CBoss * pObject = nullptr;
	pObject = new CBoss;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}

