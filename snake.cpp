//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "snake.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"

#include "bell.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CSnake::CSnake()
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CSnake::~CSnake()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CSnake::Init()
{
	// 現在のモーション番号の保管
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/snake.txt");


	m_rot.y -= (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CSnake::Uninit()
{
	// 現在のモーション番号の保管
	CEnemy::Uninit();

}

//------------------------------------
// 更新
//------------------------------------
void CSnake::Update()
{
	SetLife(100);
	// 現在のモーション番号の保管
	CEnemy::Update();
	m_motionType = CObject3d::ANIME_NORMAL;
}

//------------------------------------
// 描画
//------------------------------------
void CSnake::Draw()
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CSnake *CSnake::Create()
{
	CSnake * pObject = nullptr;
	pObject = new CSnake;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}

//------------------------------------
// 特殊演出
//-----------------------------------
void CSnake::OnHit()
{
	

		D3DXVECTOR3 scale(3.8f, 3.8f, 3.8f);
		CBell * Bell = CBell::Create();
		Bell->SetUp(BELL);

		Bell->SetMove(D3DXVECTOR3((float)-(rand() % 10 + 1), (float)(rand() % 10 + 5), 0.0f));
		Bell->SetPos(m_pos);
		Bell->SetSize(scale);

		Bell->SetLife(10);
	
}
