//============================
//
// スコア設定
// Author:hamada ryuuga
//
//============================
#include "score.h"
#include "manager.h"
#include "number.h"

CNumber* pNumber[MAX_SCORE] = {};



CScore::CScore()
{
}

CScore::~CScore()
{
}



//===================
//初期化処理
//===================
HRESULT CScore::Init()
{
	m_posScore = D3DXVECTOR3(30.0f, 50.0f, 0.0f);

	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{	
		m_pNumber[nCntScore] = CNumber::Create();
		m_pNumber[nCntScore]->SetPos(m_posScore);
		m_pNumber[nCntScore]->SetSize(30);
		m_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	}

	return S_OK;
}

//===================
//破棄処理
//===================
void  CScore::Uninit(void)
{
	for (int i = 0; i < MAX_SCORE; i++)
	{
		if (pNumber[i] != nullptr)
		{
			pNumber[i]->Uninit();
			delete pNumber[i];
			pNumber[i] = nullptr;
		}
	}

}

//===================
//更新処理
//===================
void  CScore::Update(void)
{
}

//===================
//描画処理
//===================
void  CScore::Draw(void)
{
}

//===================
//セット
//===================
void  CScore::Set(int nScore)
{
	int nCntScore;
	int aPosTexU[MAX_SCORE]; //各桁の数字を格納

	m_nScore = nScore;

	int nModScore = m_nScore;

	for (int i = 7; i >= 0; i--)
	{
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_pNumber[nCntScore]->SetTex(PositionVec4(
	 	0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
	}
}

//===================
//加算
//===================
void CScore::Add(int nValue)
{
	m_nScore += nValue;
	Set(m_nScore);
}

//===================
//情報取得
//===================
int  CScore::Get(void)
{
	return m_nScore;
}

CScore *CScore::Create()
{
	CScore * pObject = nullptr;
	pObject = new CScore;

	if (pObject != nullptr)
	{
		pObject->Init();

	}

	return pObject;
}
