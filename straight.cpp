//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "straight.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"

#include "file.h"
#include "letter.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CStraight::CStraight()
{
	
}

//------------------------------------
// デストラクタ
//------------------------------------
CStraight::~CStraight()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CStraight::Init(void)
{
	// 現在のモーション番号の保管
	CEnemy::Init();

	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/enemy/FoxPoizun.txt");


	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CStraight::Uninit(void)
{
	// 現在のモーション番号の保管
	CEnemy::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CStraight::Update(void)
{
	// 現在のモーション番号の保管
	CEnemy::Update();


}

//------------------------------------
// 描画
//------------------------------------
void CStraight::Draw(void)
{
	CEnemy::Draw();
}

//------------------------------------
// create
//------------------------------------
CStraight *CStraight::Create()
{
	CStraight * pObject = nullptr;
	pObject = new CStraight;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}



