//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "maruneko.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CMaru::CMaru()
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CMaru::~CMaru()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CMaru::Init(void)
{
	// 現在のモーション番号の保管
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/neko.txt");


	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CMaru::Uninit(void)
{
	// 現在のモーション番号の保管
	CEnemy::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CMaru::Update(void)
{
	// 現在のモーション番号の保管
	CEnemy::Update();

	//ここにmoveをいれる

}

//------------------------------------
// 描画
//------------------------------------
void CMaru::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CMaru *CMaru::Create()
{
	CMaru * pObject = nullptr;
	pObject = new CMaru;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}

