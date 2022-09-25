//============================
//
// あいてむヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _BELL_H_
#define _BELL_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CBell : public CObject3d
{
public:

	static const int BOUNDPOWER;

	//modelデータの構造体//
	struct MODELDATAPLAYER
	{
		int key;		// 時間管理
		int nowKey;		// 今のキー
		int loop;		// ループするかどうか[0:ループしない / 1 : ループする]
		int num_key;  	// キー数
	};

public:

public:
	CBell();
	~CBell();

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画
	static CBell *CBell::Create();


private:
	//void Collision(void);	// 当たり判定まとめ
	//void Move(void);		// 移動

private:
	bool            m_dist;
	int				m_bound;
	ANIME			m_motionType;					// モーションタイプ(現在)
	ANIME			m_motionTypeOld;				// モーションタイプ(過去)
};
#endif
