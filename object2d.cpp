//=============================================================================
//
// Object
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "object2d.h"
#include "manager.h"
#include "input.h"


 const D3DXVECTOR3 CObject2d::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
};
//=============================================================================
// コンストラクト関数
//=============================================================================
CObject2d::CObject2d()
{

}
//=============================================================================
// デストラクト関数
//=============================================================================
CObject2d::~CObject2d()
{

}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CObject2d::Init()
{
	float fSize = 50.0f;
	m_nScale = 10.0f;

	LPDIRECT3DDEVICE9 pDevice = CManeager::GetRenderer()->GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ken.png",
		&m_pTexture);


	VERTEX_2D*pVtx;		//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// 頂点情報の設定
	//------------------------
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 50.0f, 0.0f);

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

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CObject2d::Uninit()
{
	// 破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// 破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CObject2d::Update()
{
	m_nTimer++;
	VERTEX_2D *pVtx; //頂点へのポインタ

	 //頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// 計算用マトリックス

	//マトリックス作成
	D3DXMatrixIdentity(&mtx);

	//回転行数作成
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 2.0f) / 360.0f) * m_nTimer);

	//サイズ変更
	float fSize;
	m_fSize += 0.01f;
	fSize = sinf(m_fSize);

	//頂点座標
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);
		pVtx[i].pos = m_pos + addPos[i] * (85.0f *fSize);//<-サイズ変更
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CObject2d::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;        //デバイスへのポインタ

	 //デバイスの取得
	pDevice = CManeager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,
		2);						//プリミティブ(ポリゴン)数
}

//=============================================================================
// create関数
//=============================================================================
CObject2d *CObject2d::Create()
{
	CObject2d * pObject = nullptr;
	pObject = new CObject2d;

	if (pObject != nullptr)
	{
		pObject->Init();
	
	}

	return pObject;
}

//=============================================================================
// SetPos関数
//=============================================================================
void CObject2d::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

