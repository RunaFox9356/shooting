//============================
//
//  エネミー設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CSnake : public CEnemy
{

public:
	CSnake();
	~CSnake();

	HRESULT Init(void)override;	// 初期化
	void Uninit(void)override;	// 破棄
	void Update(void)override;	// 更新
	void Draw()override;	// 描画
	static CSnake *CSnake::Create();
	void OnHit() override;

private:
};

#endif