
//=============================================================================
//
// 魔法のストックするやつ
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _HIT_H_			// このマクロ定義がされてなかったら
#define _HIT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"

class CHit : public CObject2d
{

public:
	CHit();
	~CHit() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CHit* Create(D3DXVECTOR3 pos);

	void SelectTex(CTexture::TEXTURE tex);
	void SetAnimation(const int U, const int V);

	void PlayAnimation(const int &m_CounterAnim);
private:
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	CTexture::TEXTURE m_texture;	// テクスチャの列挙型

};

#endif