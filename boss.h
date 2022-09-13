//============================
//
//  エネミー設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CBoss : public CEnemy
{

public:
	CBoss();
	~CBoss();

	HRESULT Init(void)override;	// 初期化
	void Uninit(void)override;	// 破棄
	void Update(void)override;	// 更新
	void Draw()override;	// 描画
	static CBoss *CBoss::Create();

private:
	void Move();

	int m_keepCount;
	bool m_Stop;
	bool m_Go;
	float m_Speed;

	int m_SamonEnemy;
	D3DXVECTOR3 m_PopPos;
};
#endif