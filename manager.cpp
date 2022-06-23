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

CRenderer * CManeager::m_cRenderer = nullptr; 
CTexture * CManeager::m_pTexture = nullptr;
static float s_fAngle = 20.0f;

//=============================================================================
// コンストラクト関数
//=============================================================================
CManeager::CManeager()
{

}
//=============================================================================
// デストラクト関数
//=============================================================================
CManeager::~CManeager()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManeager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
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
	
	bullet::Lood();
	CObject::AllCreate();



	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManeager::Uninit()
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
void CManeager::Update()
{
	//入力処理の更新処理
	m_Input->Update();

	// 更新処理
	m_cRenderer->Update();


}

//=============================================================================
// 描画
//=============================================================================
void CManeager::Draw()
{
	// 描画処理
	m_cRenderer->Draw();

}


//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CManeager::GetRenderer()
{
	return m_cRenderer;
}


//=============================================================================
// GetTexture
//=============================================================================
CTexture *CManeager::GetTexture()
{
	return m_pTexture;
}