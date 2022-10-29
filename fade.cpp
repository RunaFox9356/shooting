//============================
//
// フェード設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "fade.h"
#include "font.h"
#include "words.h"
#include "kitune.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade() :CObject2d(4)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CFade::Init(void)
{
	// 現在のモーション番号の保管
	CObject2d::Init();
	m_FadeSp = 0.04f;
	m_FadeSet = 0.0f;
	CObject2d::SetTexture(CTexture::TEXTURE_NONE);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CFade::Uninit(void)
{
	// 現在のモーション番号の保管
	 CObject2d::Uninit();

}

//=============================================================================
// 更新
//=============================================================================
void CFade::Update(void)
{
	
	if (fade != FADENON)
	{
		// 現在のモーション番号の保管
		CObject2d::Update();
		if (fade == FADEOUT)
		{
			m_FadeSet -= m_FadeSp;
		}
		if (fade == FADEIN)
		{
			m_FadeSet += m_FadeSp;
		}

		if (m_FadeSet >= 1.0f)
		{
			fade = FADEOUT;
			m_FadeSet = 1.0f;
			CManager::SetMode(m_NextMode);

		}
		if (m_FadeSet <= 0.0f)
		{
			fade = FADENON;
			m_FadeSet = 0.0f;
			return;
		}
		//m_object2d[0]->SetColar(PositionVec4(0.0f, 0.0f, 0.0f, m_FadeSet));
		SetColar(PositionVec4(0.0f, 0.0f, 0.0f, m_FadeSet));		
	}
}

//=============================================================================
// 描画
//=============================================================================
void CFade::Draw(void)
{//αブレンディングを元に戻す
 //デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

CObject2d::Draw();//αブレンディングを元に戻す
	 pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	 pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	 pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create
//=============================================================================
CFade* CFade::Create()
{
	CFade * pObject = nullptr;
	pObject = new CFade;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->m_NextMode = CManager::MODE_TITLE;
		pObject->SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
		pObject->SetColar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));
		pObject->SetUp(CObject::MODE);

		pObject->fade = FADENON;
	}
	return pObject;
}


//=============================================================================
// 次のモードにいくね
//=============================================================================
void CFade::NextMode(CManager::MODE nextMode)
{
	if (fade == FADENON)
	{
		Init();
		m_NextMode = nextMode;
		SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
		SetColar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));
		m_FadeSet = 0.0f;
		SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		fade = FADEIN;

		
		//m_Words[0] = CWords::Create("N", D3DXVECTOR3(300.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[1] = CWords::Create("o", D3DXVECTOR3(350.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[2] = CWords::Create("w", D3DXVECTOR3(400.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[3] = CWords::Create("L", D3DXVECTOR3(450.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[4] = CWords::Create("o", D3DXVECTOR3(500.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[5] = CWords::Create("a", D3DXVECTOR3(550.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[6] = CWords::Create("d", D3DXVECTOR3(600.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[7] = CWords::Create("i", D3DXVECTOR3(650.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[8] = CWords::Create("n", D3DXVECTOR3(700.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);
		//m_Words[9] = CWords::Create("g", D3DXVECTOR3(750.0f, 650.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), CFont::FONT_GON);

		//m_object2d[0] = CKitune::Create(D3DXVECTOR3(200.0f, 600.0f, 0.0f), 5, false);

	}
}
