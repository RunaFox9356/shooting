//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _OBJECT2D_H_			// このマクロ定義がされてなかったら
#define _OBJECT2D_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"

class CObject2d : public CObject
{
private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	CObject2d();
	~CObject2d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CObject2d *CObject2d::Create();
	void SetPos(const D3DXVECTOR3 &pos) override;
private:
	int  m_nTimer;
	float m_nScale;
	float m_fSize;
	D3DXVECTOR3 m_pos; //polygonの位置

	LPDIRECT3DTEXTURE9	m_pTexture = NULL;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;


};
#endif
