//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "loading.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "playfab.h"
#include "words.h"
#include "kitune.h"
#include "utility.h"


//========================
// コンストラクター
//========================
CLoading::CLoading()
{
}
//========================
// デストラクタ
//========================
CLoading::~CLoading()
{
}

//================
//初期化処理
//================
HRESULT CLoading::Init(void)
{
	m_Sin = 0;
	m_moveType = 0;
	m_timer = 0;
	m_Words[0] = CWords::Create("N", D3DXVECTOR3(300.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[1] = CWords::Create("o", D3DXVECTOR3(350.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[2] = CWords::Create("w", D3DXVECTOR3(400.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[3] = CWords::Create("L", D3DXVECTOR3(450.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[4] = CWords::Create("o", D3DXVECTOR3(500.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[5] = CWords::Create("a", D3DXVECTOR3(550.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[6] = CWords::Create("d", D3DXVECTOR3(600.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[7] = CWords::Create("i", D3DXVECTOR3(650.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[8] = CWords::Create("n", D3DXVECTOR3(700.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
	m_Words[9] = CWords::Create("g", D3DXVECTOR3(750.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);

	m_object2d[0] = CKitune::Create(D3DXVECTOR3(200.0f, 650.0f, 0.0f), 5, false);

	CPlayfab::GetMasterData([]()
	{
		CManager::GetFade()->NextMode(CManager::MODE_TITLE);
	});
	return S_OK;
}

//================
//破棄
//================
void CLoading::Uninit(void)
{

	Release();
}

//==================
//更新処理
//==================
void CLoading::Update(void)
{
	m_Sin++;
	D3DXVECTOR3 move;
	m_timer++;
	if (m_timer>=m_timerCount)
	{
		m_timer = 0;
		
		if (m_moveType >= 10)
		{
			m_moveType = 0;
		}
		else
		{
			
			
			
			move.x = -5.0f;
			
			
			
		}
		

	}
	for (int i = 0; i < 10; i++)
	{
		move.y = cosf((D3DX_PI*2.0f) * 0.01f * (m_Sin + (i * 10)));

		m_Words[i]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
	}

	
	
#ifdef _DEBUG
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
	}


#endif // DEBUG
}
//==================
//描画処理
//==================
void CLoading::Draw(void)
{

}