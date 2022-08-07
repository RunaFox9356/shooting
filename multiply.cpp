//============================
//
// 倍率
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"


int CMultiply::m_Rate = 0;
int CMultiply::m_RateWait = 0;
bool CMultiply::m_Decrease;
CNumber * CMultiply::Fastratio[MAXRATE] = {};
//=============================================================================
// セット関数
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = (int)log10f((float)nModScore);

	for (int i = 0; i < RATE; i++)
	{
		ratio[i] = nullptr;
	}

	for (int i = nDigits; i >= 0; i--)
	{
		
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	D3DXVECTOR3 ratiopos = Pos;

	ratiopos = ScreenCastWorld(&ratiopos,			// スクリーン座標
		D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));									// スクリーンサイズ
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);

	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = 0; nCntScore <= nDigits; nCntScore++)
	{
		ratio[nCntScore] = CNumber::Create();
		ratio[nCntScore]->SetPos(ratiopos);
		ratiopos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		ratio[nCntScore]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	

		ratio[nCntScore]->SetTex(PositionVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
		if (extinction)
		{
			ratio[nCntScore]->Releasetimer(90);
		}
	}
 	
}

//=============================================================================
//スコアの設置
//=============================================================================
CMultiply* CMultiply::FastSet(int Number, D3DXVECTOR3 Pos)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	if (Number != 0)
	{	// 数字桁数を計算
		nDigits = (int)log10f((float)nModScore);
	}
	else
	{
		nDigits = 8;
	}

	for (int i = RATE; i >= 0; i--)
	{
		if (Fastratio[i] == nullptr)
		{//数字のデータをなかったらつくる
			Fastratio[i] = CNumber::Create();
			Fastratio[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}

		aPosTexU[i] = 0;
		
	}
	for (int i = nDigits; i >= 0; i--)
	{
		aPosTexU[i] = (nModScore % 10);
   		nModScore /= 10;
	}
	D3DXVECTOR3 ratiopos = Pos;

	// 数字の位置を計算
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = 0; nCntScore <= nDigits; nCntScore++)
	{

		// 数字の位置セット
		Fastratio[nCntScore]->SetPos(ratiopos);
		// 数字の位置の差を出す
		ratiopos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		// 数字のサイズを決定
		Fastratio[nCntScore]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		
		//数値が０かつ減少中なら０を消す
		if (aPosTexU[nCntScore] == 0 && Number == 0 && m_Decrease == true)
		{
			Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else
		{
			Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// 数字のテクスチャの位置を調整
		Fastratio[nCntScore]->SetTex(PositionVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
	}
	return nullptr;
}

//=============================================================================
// 数字を表示する関数
//=============================================================================
CMultiply* CMultiply::list(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	CMultiply * pObject = nullptr;
	pObject = new CMultiply;

	if (pObject != nullptr)
	{
		pObject->set(Number, Pos, extinction);
	}

	return pObject;
}


//=============================================================================
// スコアを表示する関数
//=============================================================================
void CMultiply::SetRate(int Rete)
{
	if (m_Rate <= 256)
	{
		m_Rate = Rete;
		CMultiply::FastSet(m_Rate, D3DXVECTOR3(100.0f, 200.0f, 0.0f));
	}
	m_Decrease = false;
	m_RateWait = 6000;
}

CMultiply::CMultiply()
{
}

CMultiply::~CMultiply()
{
}

//=============================================================================
// 破棄関数
//=============================================================================
void CMultiply::Uninit()
{
	m_Rate = 0;
	m_RateWait = 0;
	for (int nCntScore = 0; nCntScore <= RATE; nCntScore++)
	{
		if (Fastratio[nCntScore] == nullptr)
		{
			return;
		}

		Fastratio[nCntScore] = nullptr;
		
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CMultiply::Update()
{
 	m_RateWait--; 

	if (m_RateWait <= 0)
	{
		if (m_Rate >= 0)
		{
			m_Decrease = true;
			m_Rate--;
			
			if (m_Rate <= 0)
			{
				m_Rate = 0;
			}
			CMultiply::FastSet(m_Rate, D3DXVECTOR3(100.0f, 200.0f, 0.0f));
		}

		m_RateWait = 20;
	}
}
