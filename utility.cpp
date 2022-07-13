//**************************************************
// 
// Hackathon ( utility.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "renderer.h"
#include "utility.h"
#include "camera.h"

//--------------------------------------------------
// 角度の正規化
//--------------------------------------------------
void NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14より大きい
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14より小さい
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// ホーミング
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// 速さより長さが小さい時
		*pPosOut = posDest;
		return true;
	}
	else
	{// 速さより長さが大きい時
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// 小数点のランダム
//--------------------------------------------------
float FloatRandam(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// 整数のランダム
//--------------------------------------------------
int IntRandam(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sinカーブの値が1.0f～0.0fで帰ってくる
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cosカーブの値が1.0f～0.0fで帰ってくる
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// カーブの値が帰ってくる
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//---------------------------------------------------------------------------
// スクリーン座標をワールド座標へのキャスト
//---------------------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// スクリーン座標
	D3DXVECTOR3 screenSize,									// スクリーンサイズ
	D3DXMATRIX* mtxView,									// ビューマトリックス
	D3DXMATRIX* mtxProjection)								// プロジェクションマトリックス
{
	// 変数宣言
	D3DXVECTOR3 ScreenPos;

	// 計算用マトリックスの宣言
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;

	// 各行列の逆行列を算出
	D3DXMatrixInverse(&InvView, NULL, mtxView);
	D3DXMatrixInverse(&InvPrj, NULL, mtxProjection);
	D3DXMatrixIdentity(&VP);
	VP._11 = screenSize.x / 2.0f; VP._22 = -screenSize.y / 2.0f;
	VP._41 = screenSize.x / 2.0f; VP._42 = screenSize.y / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// ワールド座標へのキャスト
	D3DXMATRIX mtxWorld = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&ScreenPos, screenPos, &mtxWorld);

	return ScreenPos;
}

//---------------------------------------------------------------------------
// スクリーン座標をワールド座標へのキャスト
//---------------------------------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(D3DXVECTOR3 *screenPos,			// スクリーン座標
	D3DXVECTOR3 screenSize									// スクリーンサイズ
)								// プロジェクションマトリックス
{
	// 変数宣言

	D3DXVECTOR3 pos = *screenPos;

	CAMERA *pCamera = GetCamera()->Get();

	D3DXVECTOR3 Camerapos = pCamera->posV;

	pos.y *= -1;

	pos -= (Camerapos - D3DXVECTOR3(screenSize.x / 2, screenSize.y / 2, 0.0f));

	return pos;
}


