//=============================================================================
//
// 魔法のストックするやつ
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _MAGIC_H_			// このマクロ定義がされてなかったら
#define _MAGIC_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"

class  CMagic : public CObject2d
{
private:

public:
	CMagic();
	~CMagic() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CMagic *CMagic::Create(D3DXVECTOR3 pos);
	void SelectTex(CTexture::TEXTURE tex);
	int GetMagicId();
	static int MagicCount;
	void Magicplay();
private:
	int m_CounterAnim;
	int m_PatternAnim;
	int m_MagicId;
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	CTexture::TEXTURE m_texture;	// テクスチャの列挙型
};
#endif

