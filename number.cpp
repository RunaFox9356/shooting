//============================
//
// NUMBER
// Author:hamada ryuuga
//
//============================

#include "number.h"
#include "manager.h"

CNumber * test[10]={};

//=============================================================================
// コンストラクト関数
//=============================================================================
CNumber::CNumber(int list) : CObject2d(list)
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
	col = PositionVec4(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(
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

		m_pos.y -= 1.0f;
		
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();

	// 新規深度値 <= Zバッファ深度値 (初期設定)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 生成関数
//=============================================================================
CNumber *CNumber::Create()
{
	CNumber * pObject = nullptr;
	pObject = new CNumber(1);

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

