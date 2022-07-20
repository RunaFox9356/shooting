//============================
//
// メッシュ設定(まっすぐ)
// Author:hamada ryuuga
//
//============================


#include "mesh.h"
#include "manager.h"


CMesh::CMesh()
{

}
CMesh::~CMesh()
{

}

//=========================================
// 初期化処理
//=========================================
HRESULT CMesh:: Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 初期化処理
	m_pos = D3DXVECTOR3(-580.0f, 590.0f, 10.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

													//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/rand.png",
		&m_pTextureEmesh);


	//初期化
	m_xsiz = MAX_EMESH;
	m_zsiz = MAX_EMESH;

	//辺の頂点数
	m_X = m_xsiz + 1;//1多い数字
	m_Z = m_zsiz + 1;//1多い数字

								 //頂点数
	m_nVtx = m_X* m_Z;//頂点数を使ってるよ

										//インデックス数
	m_Index = (2 * m_X * m_zsiz + 2 * (m_zsiz - 1));

	m_por = m_Index - 2;
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < m_nVtx; i++)
	{
		float posx = ((i % m_X) - 1.0f);
		float posz = ((i / m_Z) - 1.0f)*-1.0f;

		float texU = 1.0f / m_xsiz*(i % m_X);
		float texV = 1.0f / m_zsiz*(i / m_Z);


		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZEMESH, posz * MAX_SIZEMESH, 0.0f / D3DX_PI);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// 頂点座標をアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < m_zsiz; z++)
	{
		int linetop = z * (m_X * 2 + 2);
		for (int x = 0; x < m_X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * m_X));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + m_X);
		}
		//縮退ポリゴン設定
		if (z < m_xsiz - 1)
		{
			pIdx[m_X * 2 + 0 + linetop] = (WORD)(m_xsiz + m_X*z);
			pIdx[m_X * 2 + 1 + linetop] = (WORD)(m_X * 2 + m_X * z);
		}
	}

	// 頂点座標をアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=========================================
// 終了処理
//=========================================
void CMesh::Uninit(void)
{
	// 頂点バッファーの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTextureEmesh != NULL)
	{
		m_pTextureEmesh->Release();
		m_pTextureEmesh = NULL;
	}
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=========================================
// 更新処理
//=========================================
void CMesh:: Update(void)
{

}

//=========================================
// 描画処理
//=========================================
void CMesh::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	
	//ライト設定falseにするとライトと食らわない
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファ設定
	pDevice->SetIndices(m_pIdxBuff);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureEmesh);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtx, 0, m_por);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}



//=============================================================================
// GetPos関数
//=============================================================================
const D3DXVECTOR3 *CMesh::GetPos() const
{
	return nullptr;
}

//=============================================================================
// SetPos関数
//=============================================================================
void CMesh::SetPos(const D3DXVECTOR3 &pos)
{
	//m_pos = pos;
}
//=============================================================================
// SetPos関数
//=============================================================================
void CMesh::SetMove(const D3DXVECTOR3 &move)
{
	//m_pos = pos;
}
//=============================================================================
// Create関数
//=============================================================================
CMesh* CMesh::Create()
{
	CMesh * pObject = nullptr;
	pObject = new CMesh;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}