//============================
//
// 倍率
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"

//=============================================================================
// セット関数
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = log10f(nModScore);

	for (int i = 0; i < 10; i++)
	{
		test[i] = nullptr;
	}

	for (int i = nDigits; i >= 0; i--)
	{
		
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	D3DXVECTOR3 testpos = Pos;

	testpos = ScreenCastWorld(&testpos,			// スクリーン座標
		D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));									// スクリーンサイズ
	testpos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = 0; nCntScore <= nDigits; nCntScore++)
	{

		CCamera::CAMERA *pCamera = GetCamera()->Get();


		test[nCntScore] = CNumber::Create();
		test[nCntScore]->SetPos(testpos);
		testpos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		test[nCntScore]->SetSize(30);
		test[nCntScore]->SetTex(TexVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
		test[nCntScore]->Releasetimer(360);
	}
}

//=============================================================================
// 数字を表示する関数
//=============================================================================
CMultiply* CMultiply::list(int Number, D3DXVECTOR3 Pos)
{
	CMultiply * pObject = nullptr;
	pObject = new CMultiply;

	if (pObject != nullptr)
	{
		pObject->set(Number, Pos);
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
