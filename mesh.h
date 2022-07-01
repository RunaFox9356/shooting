//============================
//
// メッシュ設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _MESH_H_
#define _MESH_H_

#include "main.h"
#include "object.h"
#define	EMESHX	(1)
#define	EMESHY	(5)
#define MAX_SIZEMESH (70.0f)
#define MAX_EMESH (20)
//------------------------------------
// ポリゴンの構造体を定義
//------------------------------------
typedef struct
{

	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 rot;	// 回転座標
	D3DXMATRIX mtxWorld;// ワールドマトリックス
	int xsiz;//面数
	int zsiz;//面数
	int X;//辺の頂点数
	int Z;//辺の頂点数
	int nVtx;//頂点数
	int Index; //インデックス
	int por;
} EMESH;


class CMesh : public CObject
{
public:
	CMesh();
	~CMesh() override;

	HRESULT Init()override;//初期化
	void Uninit()override;//破棄
	void Update()override;//更新
	void Draw()override;//描画
	//bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
	//EMESH *Get();
	static CMesh* Create();
	void SetPos(const D3DXVECTOR3 &pos); 
	D3DXVECTOR3 * CMesh::GetPos();
	
};
#endif
