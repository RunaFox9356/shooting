//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _MANEAGER_H_			// このマクロ定義がされてなかったら
#define _MANEAGER_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"

class CRenderer;
class CInput;
class CTexture;

class CManeager
{
public:
	CManeager();
	~CManeager();
	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer *GetRenderer();
	static CTexture* GetTexture();	// テクスチャの情報の取得
private:
	static CTexture *m_pTexture;
	static CRenderer * m_cRenderer;
	CInput *m_Input;
};



#endif
