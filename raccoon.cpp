//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "raccoon.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CRaccoon::CRaccoon() 
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CRaccoon::~CRaccoon()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CRaccoon::Init(void)
{
	// 現在のモーション番号の保管
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/Raccoon.txt");

	
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CRaccoon::Uninit(void)
{
	// 現在のモーション番号の保管
	CEnemy::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CRaccoon::Update(void)
{
	// 現在のモーション番号の保管
	CEnemy::Update();

	//ここにmoveをいれる

}

//------------------------------------
// 描画
//------------------------------------
void CRaccoon::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CRaccoon *CRaccoon::Create()
{
	CRaccoon * pObject = nullptr;
	pObject = new CRaccoon;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}



