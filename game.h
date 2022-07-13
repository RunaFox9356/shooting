//============================
//
// ゲーム画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//このマクロが定義されてなかったら
#define _GAME_H_		//2重インクルード防止のマクロ定義

#include "object.h"

class CGame:public CObject
{
public:
	CGame();
	~CGame();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};
#endif