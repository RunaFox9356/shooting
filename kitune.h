//=============================================================================
//
// 爆発
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _KITUNE_H_			// このマクロ定義がされてなかったら
#define _KITUNE_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"


class CKitune : public CObject2d
{

public:
	enum PosType
	{
		TYPE_2D = 0,	// 動くやーつ
		TYPE_3D,		// 動かないやーつ
		MAX			// あんただれや？
	};

	CKitune();
	~CKitune() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CKitune* Create(D3DXVECTOR3 pos, int timer, bool b3D);
private:
	void SetAnimation(const int U, const int V);

	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
	int m_AnimationSpeed;

	int m_Timar;
	int m_TimaCount;
};
#endif
