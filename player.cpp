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
#include "magic.h"
#include "multiply.h"
#include "sorcery.h"
#include "particle_manager.h"
#include "utility.h"

//------------------------------------
// static変数
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// 移動量
const float CPlayer::WIDTH = 10.0f;			// モデルの半径
const int CPlayer::MAX_PRAYER = 16;			// 最大数
const int CPlayer::MAX_MOVE = 9;			// アニメーションの最大数
const int CPlayer::INVINCIBLE = 300;		// 無敵時間
CPlayer::NOWMAGIC CPlayer::m_NowMagic = NOW_NON;		// 無敵時間
CPlayer::NOWMAGIC CPlayer::m_CastMagic = NOW_NON;		// 無敵時間


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
	SetSize(D3DXVECTOR3(2.0f,2.0f,2.0f));


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
		pObject->SetLife(5);
	}

	return pObject;
}

//------------------------------------
// Move
//------------------------------------
void CPlayer::Move()	//動きセット
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;
	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;

	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		
	
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
		m_Pow++;
		if (m_Pow >=20)
		{
			m_Pow = 0;
			switch (m_NowMagic)
			{

			case CPlayer::NOW_FIRE:
				CBullet::Create(m_pos, D3DXVECTOR3(3.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
				break;
			case CPlayer::NOW_ICE:

				CBullet::Create(m_pos, D3DXVECTOR3(5.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
				break;
			case CPlayer::NOW_STORM:
				CBullet::Create(m_pos, D3DXVECTOR3(3.0f, 3.0f, 0.0f))->SetUp(EObjectType::BULLET);
				CBullet::Create(m_pos, D3DXVECTOR3(5.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
				CBullet::Create(m_pos, D3DXVECTOR3(3.0f, -3.0f, 0.0f))->SetUp(EObjectType::BULLET);
				break;
			case CPlayer::NOW_SUN:
				CBullet::Create(m_pos, D3DXVECTOR3(15.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(15.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.z), D3DXVECTOR3(15.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
	
				break;
			case CPlayer::NOW_NON:
				CBullet::Create(m_pos, D3DXVECTOR3(5.0f, 0.0f, 0.0f))->SetUp(EObjectType::BULLET);
				break;
			default:
				break;
			}
		}
	}
 	else
	{
		m_Pow = 20;
	}
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		CParticleManager* particleManager = CManager::GetParticleManager();

		if (particleManager->GetEmitter().size() == 0)
		{
		
			D3DXVECTOR3 Pos = ScreenCastWorld(
				&m_pos,			// スクリーン座標
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
			m_CastMagic = m_NowMagic;
			CParticleManager* particleManager = CManager::GetParticleManager();

			switch (m_NowMagic)
			{	
			case CPlayer::NOW_FIRE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_FIRE);
				break;
			case CPlayer::NOW_ICE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_ICE);
				break;
			case CPlayer::NOW_STORM:

				particleManager->Create(Pos, 0, CParticleManager::NOW_STORM);
				break;
			case CPlayer::NOW_SUN:
				particleManager->Create(Pos, 0, CParticleManager::NOW_SUN);
				break;
			case CPlayer::NOW_NON:

				break;
			default:
				break;
			}
			CSorcey::Create(m_pos, m_NowMagic)->SetUp(EObjectType::SORCERY);
			CManager::GetMagicBox()->CMagicBox::MagicRelease();
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


//------------------------------------
// SetMagic
//------------------------------------
void CPlayer::SetMagic(CPlayer::NOWMAGIC NextMagic)
{
	if (NOW_MAX >= NextMagic)
	{
 		m_NowMagic = NextMagic;
	}
	else
	{
		m_NowMagic = NOW_NON;
	}
}

//------------------------------------
// GetMagic 
//------------------------------------
CPlayer::NOWMAGIC * CPlayer::GetMagic()
{
	return &m_NowMagic;
}


//------------------------------------
// GetMagic 
//------------------------------------
CPlayer::NOWMAGIC * CPlayer::GetCastMagic()
{
	return &m_CastMagic;
}