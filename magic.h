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

#define MAXMAGIC (3)

class CMagicBox : public CObject2d
{
public:
	CMagicBox() {}
	~CMagicBox() override {}
	HRESULT Init() override { CObject2d::Init(); return S_OK; }
	void Uninit() override { CObject2d::Uninit(); }
	void Update() override { CObject2d::Update(); }
	void Draw() override { CObject2d::Draw(); }
	void Magicplay(CTexture::TEXTURE TEX);
	void MagicRelease(void);
	static CMagicBox* Create(D3DXVECTOR3 pos);


	
private:
	class CMagic : public CObject2d
	{

	public:
		CMagic(int list);
		~CMagic() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void Draw() override;
		//static void Create(D3DXVECTOR3 pos);
		
		void SelectTex(CTexture::TEXTURE tex);

	private:
		int m_CounterAnim;
		int m_PatternAnim;
		int m_DivisionX;
		int m_DivisionY;
		int m_DivisionMAX;

		CTexture::TEXTURE m_texture;	// テクスチャの列挙型

	};
	
	CMagic *cMagic[MAXMAGIC];
public:
	CMagic& GetcMagic(int number);
};
#endif

