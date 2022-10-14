//============================
//
// Enemy設定ヘッター
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
		TYPE_RACCOONL = 0,	//たぬき
		TYPE_NEKO,			// ねこ
		TYPE_SNAKE,
		TYPE_MARU,			//
		TYPE_BOSS,			// 
		TYPE_CRAZINESS,			//
		TYPE_MAX
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


public:
	CEnemy();
	~CEnemy();

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画
	void Collision();	// 当たり判定
	TYPE GetType() { return m_EnemyType; };
	static void  LoadEnemy(const char * pFdata);
	static void  CEnemy::LoadEnemyOnline(const char * pFdata);
	static CEnemy *Create(const int Type);
	static void SetBossCraziness();
	static void SetBoss();

private:
	TYPE m_EnemyType;
	void TitleMove();
	//void Collision(void);	// 当たり判定まとめ
	void Move(void);		// 移動
	void ResetMove();
private:

};
#endif
