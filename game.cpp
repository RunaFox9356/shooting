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

#include "multiply.h"
#include "particle_manager.h"

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

	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(100.0f, 650.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_THUNDER);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_ICE);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_FIRE);

	//CMultiply::FastSet(0, D3DXVECTOR3(100.0f, 200.0f, 0.0f));

	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	return S_OK;
}

//========================
// ゲームの終了処理
//========================
void CGame::Uninit(void)
{
	// ポリゴンの終了処理
	CObject::ModeNotUninit();
}

//========================
// ゲームの更新処理
//========================
void CGame::Update(void)
{
	// 更新処理
	//CManager::GetRenderer()->Update();
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_RESULT);
	}
	paticleManager->Update();
}

//========================
// ゲームの描画処理
//========================
void CGame::Draw(void)
{
	// 更新処理
	CManager::GetRenderer()->Draw();
}

CMagicBox* CGame::GetMagicBox()
{
	return m_MagicBox;
}
