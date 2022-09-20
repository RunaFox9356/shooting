//=============================================================================
//
// BGオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _DANGEROUS_H_			// このマクロ定義がされてなかったら
#define _DANGEROUS_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"
#include "texture.h"


class CDangerous : public CObject2d
{
public:
	static const int Max = 10;
	static CDangerous *Create(const D3DXVECTOR3 & pos);

	CDangerous(const int list);
	~CDangerous() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int  m_nTimer;
	D3DXVECTOR3 m_rot;
};

class CDangerousManager : public CObject2d
{
public:
	static const int Max = 10;
	static const int  BossPop = 480;
	static CDangerousManager *Create(const D3DXVECTOR3 & pos, const int PopTime, const int m_DesTime);
	static void BossPopStaging();

private:
	CDangerousManager(const int list);
	~CDangerousManager() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int  m_nTimer;
	CDangerous *m_object2d[Max];
	D3DXVECTOR3 m_BackMove;
	int m_PopTime;
	int m_PopTimeCount;
	int m_DesTime;
	bool m_PopOn;

};


#endif
