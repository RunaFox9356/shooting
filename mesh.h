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
#define MAX_SIZEMESH (100.0f)
#define MAX_EMESH (20)


#define EMESHMAX (12800)

class CMesh : public CObject
{
public:
	CMesh();
	~CMesh() override;

	HRESULT Init()override;//初期化
	void Uninit()override;//破棄
	void Update()override;//更新
	void Draw()override;//描画



	static CMesh* Create();
	void SetPos(const D3DXVECTOR3 &pos);
	const D3DXVECTOR3 * CMesh::GetPos() const;

private:


	//------------------------------------
	// static変数
	//------------------------------------
	 LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	    // 頂点バッファーへのポインタ
	 LPDIRECT3DTEXTURE9 m_pTextureEmesh;        //テクスチャのポインタ
	 LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;         //インデックスバッファ

	 D3DXVECTOR3 m_pos;	// 頂点座標
	 D3DXVECTOR3 m_rot;	// 回転座標
	 D3DXMATRIX m_mtxWorld;// ワールドマトリックス
	 int m_xsiz;//面数
	 int m_zsiz;//面数
	 int m_X;//辺の頂点数
	 int m_Z;//辺の頂点数
	 int m_nVtx;//頂点数
	 int m_Index; //インデックス
	 int m_por;
	 float m_move;
};
#endif
