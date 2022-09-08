//============================
//
// TUTORIAL画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _TUTORIAL_H_		//このマクロが定義されてなかったら
#define _TUTORIAL_H_		//2重インクルード防止のマクロ定義

#include "main.h"
#include "object.h"
#include "object2d.h"


class CPlayer;
class CEnemy;
class CBg;
class CMagicBox;
class CParticleManager;
class CTutorial :public CObject
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CParticleManager* GetParticleManager() { return paticleManager; }
	static CMagicBox*GetMagicBox() { return m_MagicBox; };
	static CPlayer * GetPlayer() { return m_Player; };

	static CParticleManager* paticleManager;	// パーティクルマネジャー
	static CMagicBox* m_MagicBox;
	static CPlayer * m_Player;

private:
	CObject2d *m_object2d[4];

	
	CEnemy * m_Enemy[10];
	CBg *m_Bg[4];
	int m_addX;
	int m_addY;
	bool Sizcontroller;


};

#endif
