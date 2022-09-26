//============================
//
// 倍率//これは開発初期につくった失敗作
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"


int CMultiply::m_Rate;
int CMultiply::m_RateWait;
bool CMultiply::m_Decrease;
CNumber * CMultiply::Fastratio[KETA] = {};

//=============================================================================
// セット関数
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = (int)log10f((float)nModScore);

	for (int i = 0; i < KETA-1; i++)
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
		ratio[nCntScore]->SetNumber(aPosTexU[nCntScore]);
		ratio[nCntScore]->SetMove(false);
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
void CMultiply::FastSet(int Number, D3DXVECTOR3 Pos)
{
	int aPosTexU[3];
	int nModScore = Number;
	int nDigits;

	if (Number != 0)
	{	// 数字桁数を計算
		nDigits = (int)log10f((float)nModScore);
	}
	else
	{
		nDigits = 0;
	}


	//倍率の減少率
	if (m_Decrease)
	{
		m_RateWait = 6000;
	}
	else
	{
		m_RateWait = 6000;
	}

	for (int i = KETA-1; i >= 0; i--)
	{
	
			Fastratio[i] = CNumber::Create();
			Fastratio[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));	
		

		aPosTexU[i] = 0;
		
	}

	//一つの桁数をいれる
	for (int i = nDigits; i >= 0; i--)
	{
		aPosTexU[i] = (nModScore % 10);
   		nModScore /= 10;
	}
	D3DXVECTOR3 ratiopos = Pos;

	// 数字の位置を計算
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = nDigits; nCntScore >= 0; nCntScore--)
	{

		// 数字の位置セット
		Fastratio[nCntScore]->SetPos(ratiopos);
		// 数字の位置の差を出す
		ratiopos -= D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		// 数字のサイズを決定
		Fastratio[nCntScore]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		
		//数値が０かつ減少中なら０を消す
	
		Fastratio[nCntScore]->SetNumber(aPosTexU[nCntScore]);
		if (Number != 0)
		{
			Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}
	


	}
}

//=============================================================================
// 数字を表示する関数
//=============================================================================
CMultiply* CMultiply::Create(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	CMultiply * pObject = new CMultiply;

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
		m_Decrease = false;
		m_Rate = Rete;
		CMultiply::FastSet(m_Rate, D3DXVECTOR3(150.0f, 200.0f, 0.0f));
	}
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
	for (int nCntScore = 0; nCntScore < KETA; nCntScore++)
	{
		if (Fastratio[nCntScore] == nullptr)
		{
			return;
		}

		Fastratio[nCntScore]->Uninit();
		Fastratio[nCntScore] = nullptr;
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CMultiply::Update()
{
	if (m_Rate > 0)
	{
		m_RateWait--;
	
		if (m_RateWait <= 0)
		{

			m_Decrease = false;
			m_Rate--;
			if (m_Rate <= 0)
			{
				m_Rate = 0;
			}
			
			CMultiply::FastSet(m_Rate, D3DXVECTOR3(150.0f, 200.0f, 0.0f));
		}
	}

}
