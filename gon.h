//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _GON_H_			// このマクロ定義がされてなかったら
#define _GON_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"

class  CGon : public CObject2d
{
private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	CGon();
	~CGon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CGon *CGon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void SetMove(D3DXVECTOR3 move);



private:
	int m_CounterAnim;
	int m_PatternAnim;
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
		
	static LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXVECTOR3 m_move; //polygonの位置


};
#endif

