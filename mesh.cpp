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
	m_Mesh.pos = D3DXVECTOR3(-580.0f, 590.0f, 10.0f);
	m_Mesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

													//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/rand.png",
		&m_pTextureEmesh);


	//初期化
	m_Mesh.xsiz = MAX_EMESH;
	m_Mesh.zsiz = MAX_EMESH;

	//辺の頂点数
	m_Mesh.X = m_Mesh.xsiz + 1;//1多い数字
	m_Mesh.Z = m_Mesh.zsiz + 1;//1多い数字

								 //頂点数
	m_Mesh.nVtx = m_Mesh.X* m_Mesh.Z;//頂点数を使ってるよ

										//インデックス数
	m_Mesh.Index = (2 * m_Mesh.X * m_Mesh.zsiz + 2 * (m_Mesh.zsiz - 1));

	m_Mesh.por = m_Mesh.Index - 2;
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_Mesh.nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_Mesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < m_Mesh.nVtx; i++)
	{
		float posx = ((i % m_Mesh.X) - 1.0f);
		float posz = ((i / m_Mesh.Z) - 1.0f)*-1.0f;

		float texU = 1.0f / m_Mesh.xsiz*(i % m_Mesh.X);
		float texV = 1.0f / m_Mesh.zsiz*(i / m_Mesh.Z);


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
	for (int z = 0; z < m_Mesh.zsiz; z++)
	{
		int linetop = z * (m_Mesh.X * 2 + 2);
		for (int x = 0; x < m_Mesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * m_Mesh.X));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + m_Mesh.X);
		}
		//縮退ポリゴン設定
		if (z < m_Mesh.xsiz - 1)
		{
			pIdx[m_Mesh.X * 2 + 0 + linetop] = (WORD)(m_Mesh.xsiz + m_Mesh.X*z);
			pIdx[m_Mesh.X * 2 + 1 + linetop] = (WORD)(m_Mesh.X * 2 + m_Mesh.X * z);
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
	////モデルの切り替え
	//if (GetKeyboardTrigger(DIK_N))
	//{

	//	s_Emesh.zsiz++;
	//	s_Emesh.xsiz++;
	//	SetEmesh(s_Emesh.xsiz, s_Emesh.zsiz);
	//}

	////モデルの切り替え
	//if (GetKeyboardTrigger(DIK_M) && s_Emesh.xsiz > 1)
	//{
	//	s_Emesh.zsiz--;
	//	s_Emesh.xsiz--;
	//	SetEmesh(s_Emesh.xsiz, s_Emesh.zsiz);
	//}
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
	D3DXMatrixIdentity(&m_Mesh.mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Mesh.rot.y, m_Mesh.rot.x, m_Mesh.rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_Mesh.mtxWorld, &m_Mesh.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_Mesh.pos.x, m_Mesh.pos.y, m_Mesh.pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_Mesh.mtxWorld, &m_Mesh.mtxWorld, &mtxTrans);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Mesh.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファ設定
	pDevice->SetIndices(m_pIdxBuff);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureEmesh);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_Mesh.nVtx, 0, m_Mesh.por);

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