//============================
//
// メッシュ設定(まっすぐ)
// Author:hamada ryuuga
//
//============================


#include "mesh.h"
#include "manager.h"
#define EMESHMAX (12800)
//------------------------------------
// static変数
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// 頂点バッファーへのポインタ
static LPDIRECT3DTEXTURE9 s_pTextureEmesh = {}; //テクスチャのポインタ
static LPDIRECT3DINDEXBUFFER9 s_pIdxBuff = {};  //インデックスバッファ
static EMESH s_Emesh;								// ポリゴンの構造体



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
	s_Emesh.pos = D3DXVECTOR3(-580.0f, 590.0f, 10.0f);
	s_Emesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

													//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/rand.png",
		&s_pTextureEmesh);


	//初期化
	s_Emesh.xsiz = MAX_EMESH;
	s_Emesh.zsiz = MAX_EMESH;

	//辺の頂点数
	s_Emesh.X = s_Emesh.xsiz + 1;//1多い数字
	s_Emesh.Z = s_Emesh.zsiz + 1;//1多い数字

								 //頂点数
	s_Emesh.nVtx = s_Emesh.X* s_Emesh.Z;//頂点数を使ってるよ

										//インデックス数
	s_Emesh.Index = (2 * s_Emesh.X * s_Emesh.zsiz + 2 * (s_Emesh.zsiz - 1));

	s_Emesh.por = s_Emesh.Index - 2;
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Emesh.nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Emesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < s_Emesh.nVtx; i++)
	{
		float posx = ((i % s_Emesh.X) - 1.0f);
		float posz = ((i / s_Emesh.Z) - 1.0f)*-1.0f;

		float texU = 1.0f / s_Emesh.xsiz*(i % s_Emesh.X);
		float texV = 1.0f / s_Emesh.zsiz*(i / s_Emesh.Z);


		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZEMESH, posz * MAX_SIZEMESH, 0.0f / D3DX_PI);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Emesh.zsiz; z++)
	{
		int linetop = z * (s_Emesh.X * 2 + 2);
		for (int x = 0; x < s_Emesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * s_Emesh.X));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + s_Emesh.X);
		}
		//縮退ポリゴン設定
		if (z < s_Emesh.xsiz - 1)
		{
			pIdx[s_Emesh.X * 2 + 0 + linetop] = (WORD)(s_Emesh.xsiz + s_Emesh.X*z);
			pIdx[s_Emesh.X * 2 + 1 + linetop] = (WORD)(s_Emesh.X * 2 + s_Emesh.X * z);
		}
	}

	// 頂点座標をアンロック
	s_pIdxBuff->Unlock();

	return S_OK;
}

//=========================================
// 終了処理
//=========================================
void CMesh::Uninit(void)
{
	// 頂点バッファーの解放
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureEmesh != NULL)
	{
		s_pTextureEmesh->Release();
		s_pTextureEmesh = NULL;
	}
	if (s_pIdxBuff != NULL)
	{
		s_pIdxBuff->Release();
		s_pIdxBuff = NULL;
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
	D3DXMatrixIdentity(&s_Emesh.mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Emesh.rot.y, s_Emesh.rot.x, s_Emesh.rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&s_Emesh.mtxWorld, &s_Emesh.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, s_Emesh.pos.x, s_Emesh.pos.y, s_Emesh.pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&s_Emesh.mtxWorld, &s_Emesh.mtxWorld, &mtxTrans);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &s_Emesh.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファ設定
	pDevice->SetIndices(s_pIdxBuff);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureEmesh);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, s_Emesh.nVtx, 0, s_Emesh.por);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//
//bool CollisionEmesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
//{
//	VERTEX_3D* pVtx = NULL;
//
//	const int nTri = 3;
//	// 頂点座標をロック
//	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//インデックスバッファのロック
//	WORD* pIdx;
//	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
//
//	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
//	D3DXMATRIX mtxWorld;
//
//	// ワールドマトリックスの初期化
//	// 行列初期化関数(第1引数の行列を単位行列に初期化)
//	D3DXMatrixIdentity(&mtxWorld);
//
//	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
//	D3DXMatrixTranslation(&mtxTrans, s_Emesh.pos.x, s_Emesh.pos.y, s_Emesh.pos.z);
//	// 行列掛け算関数(第2引数×第3引数を第１引数に格納)
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
//	bool bIsLanding = false;
//	{
//		for (int nCnt = 0; nCnt < s_Emesh.por; nCnt++)
//		{
//			D3DXVECTOR3 posLineVec[nTri];
//
//			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
//			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
//			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;
//
//			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
//				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
//				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
//			{//縮退ポリゴンを省き
//				continue;
//			}
//
//			for (int i = 0; i < nTri; i++)
//			{//ベクトル３座標をマトリックスで変換する（乗算）
//				D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
//			}
//
//			int  LineCout = 0;
//
//			for (int i = 0; i < nTri; i++)
//			{
//				//ベクトルS2 V2												
//				D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];
//
//				//ベクトル現在のPOSと始点までの距離
//				D3DXVECTOR3 vecPos = *pPos - posLineVec[i];
//
//				//外積計算//辺１
//				float vecLine = Vec2Cross(&vecPos, &vecWall);
//
//				//三角の中に入ってるときの判定
//				if ((nCnt % 2 == 0 && vecLine > 0.0f) ||
//					(nCnt % 2 != 0 && vecLine < 0.0f))
//				{
//					LineCout++;
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			if (LineCout == nTri)
//			{
//				D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
//				D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];
//
//				D3DXVECTOR3 Normal;
//				//AとBの法線を求めるやつ
//				D3DXVec3Cross(&Normal, &V1, &V2);
//
//				//vecB をノーマライズして、長さ 1にする。
//				D3DXVec3Normalize(&Normal, &Normal);
//
//				D3DXVECTOR3 VecA = *pPos - posLineVec[0];
//				PLAYER *pPrayer = GetPlayer();
//
//				if (pVtx[pIdx[nCnt]].pos.y >= pPos->y)
//				{
//					pPos->y = posLineVec[0].y - (Normal.x*(pPos->x - posLineVec[0].x) + Normal.z*(pPos->z - posLineVec[0].z)) / Normal.y;
//				}
//			}
//		}
//	}
//	// 頂点座標をアンロック
//	s_pVtxBuff->Unlock();
//	// 頂点座標をアンロック
//	s_pIdxBuff->Unlock();
//
//	return bIsLanding;
//}
//=============================================================================
// GetPos関数
//=============================================================================
D3DXVECTOR3 * CMesh::GetPos()
{
	return NULL;
}

//=============================================================================
// SetPos関数
//=============================================================================
void CMesh::SetPos(const D3DXVECTOR3 &pos)
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