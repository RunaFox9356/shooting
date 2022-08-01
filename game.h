//============================
//
// ゲーム画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//このマクロが定義されてなかったら
#define _GAME_H_		//2重インクルード防止のマクロ定義

#include "object.h"


class CMagicBox;
class CParticleManager;
class CPlayer;

class CGame:public CObject
{
public:
	CGame();
	~CGame();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CMagicBox*GetMagicBox();
	static CParticleManager* GetParticleManager() { return paticleManager; }
	static CPlayer * GetPlayer() { return m_Player; };
private:

	static CMagicBox* m_MagicBox;
	static CPlayer* m_Player;
	static CParticleManager* paticleManager;	// パーティクルマネジャー


};
#endif