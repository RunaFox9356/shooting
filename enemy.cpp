//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "enemy.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "object3d.h"
#include "raccoon.h"
#include "straight.h"
#include "file.h"
#include "letter.h"

namespace nl = nlohmann;

static nl::json j;//リストの生成

//------------------------------------
// static変数
//------------------------------------
const float CEnemy::ATTENUATION = 0.5f;	// 
const float CEnemy::SPEED = 1.0f;			// 移動量
const float CEnemy::WIDTH = 10.0f;			// モデルの半径
const int CEnemy::MAX_PRAYER = 16;			// 最大数
const int CEnemy::MAX_MOVE = 9;			// アニメーションの最大数
const int CEnemy::INVINCIBLE = 300;		// 無敵時間
const int CEnemy::MAX_COPY = 4;			// 最大コピー数

//------------------------------------
// コンストラクタ
//------------------------------------
CEnemy::CEnemy() :
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CEnemy::~CEnemy()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CEnemy::Init(void)
{
	// 現在のモーション番号の保管
	CObject3d::Init();

	//CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//			   D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
	//	           "Data/system/enemy/Raccoon.txt");

	m_motionTypeOld = m_motionType;
	m_rot.y += (D3DX_PI*0.5f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CEnemy::Uninit(void)
{
	// 現在のモーション番号の保管
	CObject3d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CEnemy::Update(void)
{
	// 現在のモーション番号の保管
	CObject3d::Update();

	m_pos += m_move;

	if (m_pos.x <= -SCREEN_WIDTH)
	{
		CObject::Release();
		//m_pos.x = SCREEN_WIDTH;
	}
}

//------------------------------------
// 描画
//------------------------------------
void CEnemy::Draw(void)
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CEnemy *CEnemy::Create(const int Type)
{
	CEnemy * pObject = nullptr;

	switch (Type)
	{
	case TYPE_RACCOONL:
		pObject = new CRaccoon;
		break;
	case TYPE_FOX:
		pObject = new CStraight;
		break;
	default:
		break;
	}
	

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}

//------------------------------------
// Load
//------------------------------------
void  CEnemy::LoadEnemy(const char * pFdata)
{
	std::ifstream ifs(pFdata);

	int nIndex = 0;

	if (ifs)
	{
		ifs >> j;
		nIndex = j["INDEX"];
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
		int Life;
		int Type;
		for (int nCntEnemy = 0; nCntEnemy < nIndex; nCntEnemy++)
		{
			std::string name = "ENEMY";
			std::string Number = std::to_string(nCntEnemy);
			name += Number;
			
			pos = D3DXVECTOR3(j[name]["POS"]["X"], j[name]["POS"]["Y"], j[name]["POS"]["Z"]);
			size = D3DXVECTOR3(j[name]["SIZE"]["X"], j[name]["SIZE"]["Y"], j[name]["SIZE"]["Z"]);
			rot = D3DXVECTOR3(j[name]["ROT"]["X"], j[name]["ROT"]["Y"], j[name]["ROT"]["Z"]);
			Life = j[name]["LIFE"];
			Type = j[name]["TYPE"];

			CEnemy * Enemy = CEnemy::Create(Type);
			Enemy->SetUp(ENEMY); 
			Enemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
			Enemy->SetPos(pos);
			Enemy->SetSize(size);
			Enemy->SetRot(rot);
			Enemy->SetLife(Life);
		}
	}
}

