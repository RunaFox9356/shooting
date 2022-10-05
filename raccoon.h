//============================
//
//  エネミー設定（たぬき）
// Author:hamada ryuuga
//
//============================
#ifndef _CRACCOON_H_
#define _CRACCOON_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CRaccoon : public CEnemy
{

public:
	CRaccoon();
	~CRaccoon();

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画
	static CRaccoon *CRaccoon::Create();

private:
	int m_counter;
	void CRaccoon::EnemyPattern4();

};
#endif
