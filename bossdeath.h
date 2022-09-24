//=============================================================================
//
// BOSSDEATH
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _BOSSDEATH_H_			// このマクロ定義がされてなかったら
#define _BOSSDEATH_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"

class CText;

class  CDeathManager : public C3dpolygon
{

public:
	CDeathManager();
	~CDeathManager() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	static CDeathManager *Create(int MAX,int Pop);
	static void SetGetGold(int Get) { m_GetGold = Get; };
	static int GetGetGold() { return m_GetGold; };
	static void AddMissGold(int Miss) { m_MissGold += Miss; };
private:
	
	int m_PopMax;
	int m_PopTime;
	int m_PopCount;
	int m_PopTimeCount;
	int m_TextCount;
	static int m_GetGold;
	static int m_MissGold;
	CText* text;
	bool GoNextMode;

};

class  CDeath : public C3dpolygon
{

public:
	CDeath();
	~CDeath() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CDeath *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
private:
	void SetAnimation(const int U, const int V);
	
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
	int m_AnimationSpeed;
	
};
#endif

