//============================
//
// 爆発設定
// Author:hamada ryuuga
//
//============================

#include "kitune.h"
#include "utility.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CKitune::CKitune() :CObject2d(4)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CKitune::~CKitune()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CKitune::Init()
{
	m_Timar = 0;
	m_TimaCount = 0;
	CObject2d::Init();

	CObject2d::SetTexture(CTexture::TEXTURE_GON);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CKitune::Uninit()
{

	CObject2d::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CKitune::Update()
{
	m_TimaCount++;
	CObject2d::Update();
	if (m_TimaCount >= m_Timar)
	{
		m_PatternAnimX++;

		if (m_PatternAnimX > m_DivisionX)
		{//アニメーション
			m_PatternAnimX = 0;
			m_PatternAnimY++;
			if (m_PatternAnimY >= m_DivisionY)
			{
				m_PatternAnimY = 0;
				//Uninit();
				return;
			}
		}

		float U = 1.0f / (m_DivisionX);
		float V = 1.0f / (m_DivisionY);

		SetTex(PositionVec4(
			U * (m_PatternAnimX)
			, U *(m_PatternAnimX)+U
			, V * (m_PatternAnimY)
			, V * (m_PatternAnimY)+V));
		SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

//=============================================================================
// 描画
//=============================================================================
void CKitune::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// create
//=============================================================================
CKitune *CKitune::Create(D3DXVECTOR3 pos, int timer, bool b3D)
{
	CKitune * pObject = nullptr;
	pObject = new CKitune;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 Poppos = pos;
		if (b3D)
		{
			Poppos = ScreenCastWorld(&Poppos,			// スクリーン座標
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));								// スクリーンサイズ
		}
		pObject->Init();
		pObject->SetPos(Poppos);
		pObject->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		pObject->SetAnimation(1, 4);
		pObject->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		pObject->m_Timar = timer;
	}
	return pObject;
}

//=============================================================================
// Animationの枚数設定関数
//=============================================================================
void CKitune::SetAnimation(const int U, const int V)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 0;
	m_PatternAnimY = 0;

	//表示座標を更新
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}