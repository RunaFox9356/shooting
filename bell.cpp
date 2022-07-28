//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "bell.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"
#include "file.h"
#include "letter.h"
#include "score.h"
#include "player.h"
#include "multiply.h"

//------------------------------------
// static変数
//------------------------------------
const float CBell::ATTENUATION = 0.5f;	// 
const float CBell::SPEED = 1.0f;			// 移動量
const float CBell::WIDTH = 10.0f;			// モデルの半径
const int CBell::MAX_PRAYER = 16;			// 最大数
const int CBell::MAX_MOVE = 9;			// アニメーションの最大数
const int CBell::INVINCIBLE = 300;		// 無敵時間
const int CBell::MAX_COPY = 4;			// 最大コピー数

//------------------------------------
// コンストラクタ
//------------------------------------
CBell::CBell() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CBell::~CBell()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CBell::Init(void)
{
	// 現在のモーション番号の保管
	CObject3d::Init();

      CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"Data/system/item/Bell.txt");

	m_motionTypeOld = m_motionType;
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CBell::Uninit(void)
{
	// 現在のモーション番号の保管
	CObject3d::Uninit();


}

//------------------------------------
// 更新
//------------------------------------
void CBell::Update(void)
{
	// 現在のモーション番号の保管
	CObject3d::Update();

	m_pos += m_move;

	m_move.y -= 0.5f;

	for (int i = 0; i < MAX_OBJECT; i++)
	{	// 当たり判定
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::PLAYER)
			{	// Playerとの当たり判定
				CPlayer* cPlayer = dynamic_cast<CPlayer*>(pObject);  // ダウンキャスト
				const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
				float Size = 30.0f;

				if (((m_pos.y - Size) <= (PlayerPos->y + Size)) &&
					((m_pos.y + Size) >= (PlayerPos->y - Size)) &&
					((m_pos.x - Size) <= (PlayerPos->x + Size)) &&
					((m_pos.x + Size) >= (PlayerPos->x - Size)))
				{
					
					GetScore()->Add(10 * (*CMultiply::GetRate()+1));
					

					CObject::Release();

					return;
				}
			}
		}
	}
	if (m_pos.y <= -360.0f)
	{
		m_pos.y = -360.0f;
		m_move.y = 0.0f;
	}
	if (m_pos.x <= -1280.0f)
	{
		CObject::Release();
	}
}

//------------------------------------
// 描画
//------------------------------------
void CBell::Draw(void)
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBell *CBell::Create()
{
	CBell * pObject = nullptr;
	pObject = new CBell;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}



