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
	typedef enum
	{
		ANIME_NORMAL = 0,	// ニュートラル
		ANIME_RUN,			// 歩き
		ANIME_ATTACK,		// 攻撃
		ANIME_JUMP,			// ジャンプ
		ANIME_LANDING,		// 着地
		ANIME_MAX
	}ANIME;

	typedef enum
	{
		STATUS_NORMAL = 0,	// ニュートラル
		STATUS_RUN,			// 歩き
		STATUS_ATTACK,		// 攻撃
		STATUS_JUMPUP,		// ジャンプ
		STATUS_JUMPDOWN,	// ジャンプ
		STATUS_LANDING,		// 着地
		STATUS_MAX
	}STATUS;

	typedef enum
	{
		DAMEGE_NORMAL = 0,	// ニュートラル
		DAMEGE_NOU,			// ダメージくらってる
		DAMEGE_MAX
	}DAMEGE;

	typedef enum
	{
		COPY_NORMAL = 0,	// ニュートラル
		COPY_SWORD,			// ソード
		COPY_FIRE,			// ファイア
		COPY_LASER,			// レーザー
		COPY_CUTTER,		// カッター
		COPY_MAX
	}COPY;

	//modelデータの構造体//
	typedef struct
	{
		int key;		// 時間管理
		int nowKey;		// 今のキー
		int loop;		// ループするかどうか[0:ループしない / 1 : ループする]
		int num_key;  	// キー数
						/*MyKeySet KeySet[MAX_KEY];*/
	}MODELDATAPLAYER;

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

	static CEnemy *CEnemy::Create();

	//void Set(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// セット引数座標と読み込むファイル名
	//void SetPos(const D3DXVECTOR3 &pos) override;
	/*void SetCopy(char *pFileName, PartsFile *partsFile, Parts *parts, MyMotion *Motion, int *nMaxParts);*/

private:
	//void Collision(void);	// 当たり判定まとめ
	//void Move(void);		// 移動

private:

	ANIME			m_motionType;					// モーションタイプ(現在)
	ANIME			m_motionTypeOld;				// モーションタイプ(過去)
};
#endif
