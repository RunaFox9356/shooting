//=============================================================================
//
// 3dpolygon
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _3DPOLYGON_H_			// このマクロ定義がされてなかったら
#define _3DPOLYGON_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "texture.h"
#include "object2d.h"

#define SIZEX (45.0f)
#define SIZEY (90.0f)
#define TIMER (m_nTimer + 90)

class  C3dpolygon : public CObject
{
private:
	//polygonの基準サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	C3dpolygon();
	~C3dpolygon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;

	void SetTexture(CTexture::TEXTURE texture);
	void SetTex(TexVec4 Tex);
	
	void SetSize(const D3DXVECTOR3 &size);
	void SetCollar(TexVec4 Collar);
protected:
	float m_nScale;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos; //polygonの位置
	D3DXVECTOR3 m_Size;
	D3DXMATRIX m_mtxWorld;					// マトリックス
private:
	int  m_nTimer; // TODO: これなおす
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = nullptr;
	CTexture::TEXTURE m_texture;	// テクスチャの列挙型

};

#endif
