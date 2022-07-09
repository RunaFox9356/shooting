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
class CMagicBox;
class CObject;
class CResult;
class CTitle;


class CManager
{
public:

	//画面(モード)の種類
	typedef enum
	{
		MODE_TITLE = 0,		//タイトル画面
		MODE_GAME,			//ゲーム画面
		MODE_RESULT,		//リザルト画面
		MODE_FADE,			//フェード画面
		MODE_RANKING,		//ランキング画面
		MODE_GAMEOVER,
		MODE_TUTORIAL,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer *GetRenderer();
	static CTexture* GetTexture();	// テクスチャの情報の取得
	static CMagicBox*GetMagicBox();
	static void SetMode(CManager::MODE mode);
private:
	static CTexture *m_pTexture;
	static CRenderer * m_cRenderer;
	CInput *m_Input;
	static CMagicBox* m_MagicBox;


	static CObject*m_Game;
	

	MODE m_mode;
};



#endif
