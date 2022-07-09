//=============================================================================
//
// マネージャー
// Author : 浜田琉雅
//
//=============================================================================

#include "manager.h"
#include "main.h"
#include "object.h"
#include "light.h"
#include "player.h"
#include "renderer.h"
#include "input.h"
#include "file.h"
#include "bullet.h"
#include "texture.h"
#include "magic.h"
#include "game.h"
#include "title.h"
#include "result.h"

CRenderer * CManager::m_cRenderer = nullptr; 
CTexture * CManager::m_pTexture = nullptr;
CMagicBox* CManager::m_MagicBox = nullptr;
CObject*CManager::m_Game = nullptr;

//=============================================================================
// コンストラクト関数
//=============================================================================
CManager::CManager()
{

}
//=============================================================================
// デストラクト関数
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	
	m_cRenderer = new CRenderer;
	m_Input = CInput::Create();

	// 初期化処理
	if (FAILED(m_cRenderer->Init(hWnd, TRUE)))	//画面サイズ
	{//初期化処理が失敗した場合
		return -1;
	}
	//入力処理の初期化処理
	if (FAILED(m_Input->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pTexture = nullptr;
	m_pTexture = new CTexture;
	
	m_mode = CManager::MODE_TITLE;	//現在のモード

	//モードの設定
	SetMode(m_mode);

	CObject::AllCreate();


	
	CObject::AllCreate();
	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(100.0f, 650.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_NONE);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManager::Uninit()
{
	// ポリゴンの終了処理
	CObject::AllUninit();

	if (m_pTexture != nullptr)
	{// 終了処理

		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_cRenderer != nullptr)
	{// 終了処理

		m_cRenderer->Uninit();
		delete m_cRenderer;
		m_cRenderer = nullptr;
	}
	//入力処理の終了処理
	m_Input->Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CManager::Update()
{
	//入力処理の更新処理
	m_Input->Update();

	// 更新処理
	m_cRenderer->Update();


}

//=============================================================================
// 描画
//=============================================================================
void CManager::Draw()
{
	// 描画処理
	m_cRenderer->Draw();

}


//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_cRenderer;
}


//=============================================================================
// GetTexture
//=============================================================================
CTexture *CManager::GetTexture()
{
	return m_pTexture;
}

CMagicBox* CManager::GetMagicBox()
{
	return m_MagicBox;
}

//========================
// モードの設定
//========================
void CManager::SetMode(MODE mode)
{
	if (m_Game != nullptr)
	{
		m_Game->Uninit();
		delete m_Game;
		m_Game = nullptr;
	}

	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_Game = new CTitle;
		break;
	case CManager::MODE_GAME:
		m_Game = new CGame;
		break;
	case CManager::MODE_RESULT:
		m_Game = new CResult;
		break;
	default:
		break;
	}

	if (FAILED(m_Game->Init()))
	{
		return;
	}
}

