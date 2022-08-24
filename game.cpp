//============================
//
// ゲーム画面
// Author:hamada ryuuga
//
//============================

//------------------------
// インクルード
//------------------------
#include "game.h"
#include "input.h"
#include "manager.h"
#include "object.h"
#include "light.h"
#include "player.h"
#include "file.h"
#include "bullet.h"

#include "magic.h"
#include "enemy.h"
#include "fade.h"

#include "multiply.h"
#include "particle_manager.h"
#include "ranking.h"

#include "score.h"

CMagicBox* CGame::m_MagicBox = nullptr;
CParticleManager*CGame::paticleManager = nullptr;
CPlayer*CGame::m_Player = nullptr;

//========================
// コンストラクター
//========================
CGame::CGame()
{
}
//========================
// デストラクト
//========================
CGame::~CGame()
{
}

//========================
// ゲームの初期化処理
//========================
HRESULT CGame::Init(void)
{

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	paticleManager = new CParticleManager;
	// パーティクル
	if (FAILED(paticleManager->Init()))
	{
		return E_FAIL;
	}

	CObject::AllCreate();

	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(150.0f, 620.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_THUNDER);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_ICE);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_FIRE);


	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);
	
	return S_OK;
}

//========================
// ゲームの終了処理
//========================
void CGame::Uninit(void)
{
	CModelManager::ReleaseAll();
	CRanking::SetScore(CScore::GetScore());
}

//========================
// ゲームの更新処理
//========================
void CGame::Update(void)
{
	// 更新処理

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_RESULT);
		//CManager::SetMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}
	if (GetMaxEnemy() <= 0)
	{
		if (GetMaxBoss())
		{
			//モードの設定

			CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
			return;
		}
		CEnemy::SetBoss();
	
	}
	paticleManager->Update();
}

//========================
// ゲームの描画処理
//========================
void CGame::Draw(void)
{
	// 更新処理
	//CManager::GetRenderer()->Draw();
}
