//============================
//
// スコア設定
// Author:hamada ryuuga
//
//============================
#include "score.h"
#include "game.h"


static LPDIRECT3DTEXTURE9 s_pTextureScore = NULL; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffScore = NULL; //頂点バッファの設定
static D3DXVECTOR3 s_posScore; //スコアの位置
static int s_nScore;

//---------------------------------------
//セットポス(2d)
//---------------------------------------
void SetNorotpos2d(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW)
{
	pVtx[0].pos = D3DXVECTOR3(XUP, YUP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(XDW, YUP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(XUP, YDW, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(XDW, YDW, 0.0f);
}

//---------------------------------------
//セットテクスチャ(2d)
//---------------------------------------
void Settex2d(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}

//===================
//初期化処理
//===================
void InitScore(void)
{

	LPDIRECT3DDEVICE9  pDevice;

	

	s_posScore = D3DXVECTOR3(900.0f, 50.0f, 0.0f);
	
	

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Score001.png",
		&s_pTextureScore);
	
	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&s_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx; //頂点へのポインタ
	s_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//頂点バッファをロックし頂点情報へのポインタを取得
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{	
		//頂点座標
		SetNorotpos2d(pVtx,
			s_posScore.x - 30,
			s_posScore.x + 30,
			s_posScore.y - 30,
			s_posScore.y + 30);

		s_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

		//RHWの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	s_pVtxBuffScore->Unlock();
}

//===================
//破棄処理
//===================
void UninitScore(void)
{
		//テクスチャの破棄
	if (s_pTextureScore != NULL)
	{
		s_pTextureScore->Release();
		s_pTextureScore = NULL;
	}
	
	//頂点バッファの破棄
	if (s_pVtxBuffScore != NULL)
	{
		s_pVtxBuffScore->Release();
		s_pVtxBuffScore = NULL;
	}
}

//===================
//更新処理
//===================
void UpdateScore(void)
{
	

		s_posScore = D3DXVECTOR3(900.0f, 50.0f, 0.0f);
	
	

	VERTEX_2D*pVtx; //頂点へのポインタ
	s_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//頂点座標
		SetNorotpos2d(pVtx,
			s_posScore.x - 30,
			s_posScore.x + 30,
			s_posScore.y - 30,
			s_posScore.y + 30);

		s_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	s_pVtxBuffScore->Unlock();

}

//===================
//描画処理
//===================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntScore;

	pDevice = GetDevice();		//代入
								//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntScore * 4,
				2);
	}
}

//===================
//セット
//===================
void SetScore(int nScore)
{
	int nCntScore;
	int aPosTexU[MAX_SCORE]; //各桁の数字を格納

	s_nScore = nScore;

	int nScore = s_nScore;

	for (int i = 7; i >= 0; i--)
	{
		aPosTexU[i] = (nScore % 10);
		nScore /= 10;
	}
	
	VERTEX_2D*pVtx; //頂点へのポインタ
	s_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore]+0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore]+ 0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	s_pVtxBuffScore->Unlock();
}

//===================
//加算
//===================
void AddScore(int nValue)
{
	int nCntScore;
	int aPosTexU[MAX_SCORE]; //各桁の数字を格納

	s_nScore += nValue;


	SetScore(s_nScore);
}

//===================
//情報取得
//===================
int GetScore(void)
{
	return s_nScore;
}

