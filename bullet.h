//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _BULLET_H_			// このマクロ定義がされてなかったら
#define _BULLET_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"

class  CBullet : public C3dpolygon
{
private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	CBullet();
	~CBullet() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void SetMove(const D3DXVECTOR3 &move)override;
	static LPDIRECT3DTEXTURE9 Gettex();
	static void Lood();
	static void UnLood();

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;
	static int m_AllMember;
	D3DXVECTOR3 m_move; //polygonの位置
	D3DXVECTOR3 Hitpos;
};
#endif
