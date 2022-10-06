//============================
//
// エネミー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "words.h"

#include "manager.h"
#
#include "object.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CWords::CWords(int list) :CObject(2)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CWords::~CWords()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CWords::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//- 
	// 頂点情報の設定
	//-
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);


	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// フォントを使えるようにする
	DESIGNVECTOR design;

	AddFontResourceEx(
		"data/font/FZゴンタかな.otf", //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);

	// フォントの生成
	int fontsize = 38;

	LOGFONT lf = { fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("FZゴンタかな") };

	if (!(m_hFont = CreateFontIndirect(&lf)))
	{
	
	}

	//// デバッグ情報表示用フォントの生成
	//D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 38, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
	//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("FZゴンタかな"), &m_pFont);

	// デバイスコンテキスト取得
	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont);


	
	std::string words = m_words;
	// 文字コード取得
	const char *c = words.c_str();
	UINT code = 0;
#if _UNICODE
	// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
	code = (UINT)*c;
#else
	// マルチバイト文字の場合、
	// 1バイト文字のコードは1バイト目のUINT変換、
	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
	if (IsDBCSLeadByte(*c))
		code = (BYTE)c[0] << 8 | (BYTE)c[1];
	else
		code = c[0];
#endif

	// フォントビットマップ取得
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 2, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	DeleteObject(m_hFont);
	ReleaseDC(NULL, hdc);

	// テクスチャ作成
	if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTex, NULL)))
		if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTex, NULL)))
		{
			return 0;
		}

	// テクスチャにフォントビットマップ書き込み
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
		if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, 0)))
		{
			return 0;
		}


	// フォント情報の書き込み
	// iOfs_x, iOfs_y : 書き出し位置(左上)
	// iBmp_w, iBmp_h : フォントビットマップの幅高
	// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	FillMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight, 0);
	for (y = iOfs_y; y<iOfs_y + iBmp_h; y++)
		for (x = iOfs_x; x<iOfs_x + GM.gmBlackBoxX; x++) {
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w*(y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
			memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4 * x, &Color, sizeof(DWORD));
		}

	m_pTex->UnlockRect(0);

	delete[] ptr;


	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CWords::Uninit(void)
{

	DESIGNVECTOR design;

	RemoveFontResourceEx(
		TEXT("Data/font/FZゴンタかな.otf"), //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);

	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

	// 破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();

}

//------------------------------------
// 更新
//------------------------------------
void CWords::Update(void)
{


	VERTEX_2D *pVtx; //頂点へのポインタ

					 //頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// 計算用マトリックス

					//マトリックス作成
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_rot.z);
	//頂点座標
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);

		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_Size.x);//<-サイズ変更
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_Size.y);//<-サイズ変更
		pVtx[i].pos.z = 0.0f;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();


	//ここにmoveをいれる

}

//------------------------------------
// 描画
//------------------------------------
void CWords::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;        //デバイスへのポインタ

									  //デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTex);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,
		2);
	//プリミティブ(ポリゴン)数
	pDevice->SetTexture(0, NULL);

}

//------------------------------------
// create
//------------------------------------
CWords *CWords::Create(const char*Text)
{
	CWords * pObject = nullptr;
	pObject = new CWords;

	if (pObject != nullptr)
	{
		pObject->Setwords(Text);
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 100));
		pObject->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
		pObject->Init();
	}
	return pObject;
}



//=============================================================================
// GetPos関数
//=============================================================================
const D3DXVECTOR3 * CWords::GetPos() const
{
	return &m_pos;
}

//=============================================================================
// SetPos関数
//=============================================================================
void CWords::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}
//=============================================================================
// SetPos関数
//=============================================================================
void CWords::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//===========================================================================
//セットカラー
//=============================================================================
void CWords::SetColar(D3DXCOLOR Collar)
{
	VERTEX_2D *pVtx; //頂点へのポインタ

					 //頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[1].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[2].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[3].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);

	m_col = Collar;
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}