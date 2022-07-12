//============================
//
// 倍率
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"

//=============================================================================
// セット関数
//=============================================================================
void CMultiply::set(int Number, int Digits, D3DXVECTOR3 Pos)
{
	int aPosTexU[100];
	int nModScore = Number;
	for (int i = 0; i < 10; i++)
	{
		test[i] = nullptr;
	}

	for (int i = Digits-1; i >= 0; i--)
	{
		
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	D3DXVECTOR3 testpos = Pos;
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = 0; nCntScore < Digits; nCntScore++)
	{
		test[nCntScore] = CNumber::Create();
		test[nCntScore]->SetPos(testpos);
		test[nCntScore]->SetSize(30);
		testpos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		test[nCntScore]->SetTex(TexVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
		test[nCntScore]->Releasetimer(360);
	}
}

//=============================================================================
// 数字を表示する関数
//=============================================================================
CMultiply* CMultiply::list(int Number, int Digits, D3DXVECTOR3 Pos)
{
	CMultiply * pObject = nullptr;
	pObject = new CMultiply;

	if (pObject != nullptr)
	{
		pObject->set(Number,Digits, Pos);
	}

	return pObject;
}

CMultiply::CMultiply()
{
}

CMultiply::~CMultiply()
{
}

void CMultiply::Uninit()
{
	for (int i = 0; i < 10; i++)
	{
		if (test[i] != nullptr)
		{
			//test[i]->Uninit();
			//delete test[i];
			//test[i] = nullptr;
		}
	}
}
