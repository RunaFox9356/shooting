//============================
//
// NUMBER
// Author:hamada ryuuga
//
//============================

#include "number.h"


CNumber * test[10]={};

//=============================================================================
// コンストラクト関数
//=============================================================================
CNumber::CNumber()
{
}

//=============================================================================
// デストラクト関数
//=============================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CNumber::Init()
{
	CObject2d::Init();
	CObject2d::SetTexture(CTexture::TEXTURE_SCORE);
	col = TexVec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	SetTex(TexVec4(
		0.0f, 0.1f, 0.0f, 1.0f));
	isRelease = false;
	m_DesTimar = 0;
	return S_OK;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CNumber::Uninit()
{
	CObject2d::Uninit();
}


//=============================================================================
// 更新関数
//=============================================================================
void CNumber::Update()
{
	CObject2d::Update();

	if (isRelease)
	{
		m_DesTimar--;

		col.P3 -= 1.0f / m_DesTimarMax;

		CObject2d::SetCollar(col);

		if (m_DesTimar<=0)
		{
			Release();
		}
	}

}

//=============================================================================
// 描画関数
//=============================================================================
void CNumber::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// 生成関数
//=============================================================================
CNumber *CNumber::Create()
{
	CNumber * pObject = nullptr;
	pObject = new CNumber;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}



//=============================================================================
// けすまでの時間設定関数
//=============================================================================
void CNumber::Releasetimer(int nTimar)
{
	m_DesTimar = nTimar;
	m_DesTimarMax = m_DesTimar;
	isRelease = true;
}

