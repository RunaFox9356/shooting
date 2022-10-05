//============================
//
//  エネミー設定（ねこ）ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CStraight : public CEnemy
{

public:
	CStraight();
	~CStraight();

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画
	static CStraight *CStraight::Create();


private:



};
#endif

