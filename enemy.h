//============================
//
// プレイヤー設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CEnemy : public CObject3d
{
public:
	enum ANIME
	{
		ANIME_NORMAL = 0,	// ニュートラル
		ANIME_RUN,			// 歩き
		ANIME_ATTACK,		// 攻撃
		ANIME_JUMP,			// ジャンプ
		ANIME_LANDING,		// 着地
		ANIME_MAX
	};

	enum TYPE
	{
		TYPE_RACCOONL = 0,	// ニュートラル
		TYPE_FOX,			// 歩き
		TYPE_FOX2,		// 攻撃
		TYPE_FOX3,			// ジャンプ
		TYPE_FOX4,		// 着地
		TYPE_MAX
	};

	enum DAMEGE
	{
		DAMEGE_NORMAL = 0,	// ニュートラル
		DAMEGE_NOU,			// ダメージくらってる
		DAMEGE_MAX
	};

	
	//modelデータの構造体//
	struct MODELDATAPLAYER
	{
		int key;		// 時間管理
		int nowKey;		// 今のキー
		int loop;		// ループするかどうか[0:ループしない / 1 : ループする]
		int num_key;  	// キー数
						/*MyKeySet KeySet[MAX_KEY];*/
	};

public:
	static const float ATTENUATION;		// 減衰係数
	static const float SPEED;			// スピード
	static const float WIDTH;			// モデルの半径
	static const int MAX_PRAYER;		// 最大数
	static const int MAX_MOVE;			// アニメーションの最大数
	static const int INVINCIBLE;		// 無敵時間
	static const int MAX_MODELPARTS = 9;
	static const int MAX_COPY;

public:
	CEnemy();
	~CEnemy();

	HRESULT Init(void)override;	// 初期化
	void Uninit(void)override;	// 破棄
	void Update(void)override;	// 更新
	void Draw()override;	// 描画
	static void  CEnemy::LoadEnemy(const char * pFdata);
	static CEnemy *CEnemy::Create(const int Type);


private:
	//void Collision(void);	// 当たり判定まとめ
	//void Move(void);		// 移動

private:

	ANIME			m_motionType;					// モーションタイプ(現在)
	ANIME			m_motionTypeOld;				// モーションタイプ(過去)
};
#endif
