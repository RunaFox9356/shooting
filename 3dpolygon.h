//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _3DPOLYGON_H_			// このマクロ定義がされてなかったら
#define _3DPOLYGON_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "texture.h"
#include "object2d.h"

class  C3dpolygon : public CObject
{

	private:
		//polygonの拡大サイズ
		static const D3DXVECTOR3 m_Vtx[4];

	public:
		C3dpolygon();
		~C3dpolygon() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void Draw() override;
		void SetTexture(CTexture::TEXTURE texture);
		D3DXVECTOR3 *GetPos()override;

		void SetPos(const D3DXVECTOR3 &pos) override;
		void SetTex(TexVec4 Tex);
	protected:
		int  m_nTimer;
		float m_nScale;
		float m_fSize;
		D3DXVECTOR3 m_pos; //polygonの位置
		D3DXMATRIX		m_mtxWorld;					// マトリックス
	private:
		CTexture::TEXTURE m_texture;	// テクスチャの列挙型

		LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
};
#endif

