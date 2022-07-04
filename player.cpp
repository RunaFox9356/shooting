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
#include "bullet.h"
#include "enemy.h"	
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
int DATA = 0;
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

	m_MoveSpeed = 3.0f;
	m_rot.y += (-D3DX_PI*0.5f);

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

	Move();	//動きセット
	
	
	//Collision();//床

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

//------------------------------------
// Move
//------------------------------------
void CPlayer::Move()	//動きセット
{
	CInput *CInputpInput = CInput::GetKey();
	CAMERA *pCamera = GetCamera()->Get();
	float consumption = 0.0f;
	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		//CEnemy::Create()->SetUp(ENEMY, D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//CEnemy::Create()->SetUp(ENEMY, D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + pCamera->rot.y;

	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + pCamera->rot.y) * SPEED * m_MoveSpeed;
		
	
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{	
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{	
		m_move.y += m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
		DATA++;
		if (DATA == 20)
		{
			DATA = 0;
			CBullet::Create(m_pos, D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		}
	}
	
	m_move.x += (0.0f - m_move.x)*ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//移動を加算


	//正規化
	if ( consumption > D3DX_PI)
	{
		 consumption += D3DX_PI * 2.0f;
	}
	if ( consumption < -D3DX_PI)
	{
		 consumption += -D3DX_PI * 2.0f;
	}

	//減算設定（感性）
	m_rot.y += (consumption)* ATTENUATION;//目的の値-現在の値）＊減衰係数

	 //正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}