//============================
//
// プレイヤー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "motion.h"
#include "object3d.h"

//------------------------------------
// static変数
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// 移動量
const float CPlayer::WIDTH = 10.0f;			// モデルの半径
const int CPlayer::MAX_PRAYER = 16;			// 最大数
const int CPlayer::MAX_MOVE = 9;			// アニメーションの最大数
const int CPlayer::INVINCIBLE = 300;		// 無敵時間
const int CPlayer::MAX_COPY = 4;			// 最大コピー数

//------------------------------------
// コンストラクタ
//------------------------------------
CPlayer::CPlayer() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL)
{
	//memset(&s_Player, NULL, sizeof(s_Player));
	/*memset(&m_motion, 0, sizeof(m_motion));*/
}

//------------------------------------
// デストラクタ
//------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CPlayer::Init(void)
{
	// 現在のモーション番号の保管
	CObject3d::Init();
	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Data/system/Gon/Fox.txt");
	m_motionTypeOld = m_motionType;

	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CPlayer::Uninit(void)
{
	// 現在のモーション番号の保管
	CObject3d::Uninit();


}

//------------------------------------
// 更新
//------------------------------------
void CPlayer::Update(void)
{
	// 現在のモーション番号の保管
	CObject3d::Update();

//	Move();	//動きセット

//	Collision();//床

}

//------------------------------------
// 描画
//------------------------------------
void CPlayer::Draw(void)
{
	CObject3d::Draw();
}


//------------------------------------
// create
//------------------------------------
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;

}
