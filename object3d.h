//=============================================================================
//
// OBJECT3D
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _OBJECT3D_H_			// このマクロ定義がされてなかったら
#define _OBJECT3D_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object.h"
#include "main.h"
#include "motion.h"

class  CMotion;

class CObject3d : public CObject
{
private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

	typedef enum
	{
		ANIME_NORMAL = 0,	// ニュートラル
		ANIME_RUN,			// 歩き
		ANIME_ATTACK,		// 攻撃
		ANIME_JUMP,			// ジャンプ
		ANIME_LANDING,		// 着地
		ANIME_MAX
	}ANIME;
public:
	CObject3d();
	~CObject3d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
	void Set(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot,  char *filename);
	D3DXVECTOR3 *GetPos()override;

	protected:
	D3DXVECTOR3		m_move;						// ムーブ
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_rot;						// 回転	
	D3DXVECTOR3		m_rotMove;					// 回転ムーブ
private:
	int  m_nTimer;
	float m_nScale;
	float m_fSize;

	LPDIRECT3DTEXTURE9	m_pTexture = NULL;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
	CMotion			*m_pMotion;					// モーション
						// 位置
	D3DXVECTOR3		m_posOld;					// 位置過去
	//D3DXVECTOR3		m_move;						// ムーブ

	D3DXVECTOR3		m_modelMin;					// サイズ最小
	D3DXVECTOR3		m_modelMax;					// サイズ最大
	D3DXMATRIX		m_mtxWorld;					// マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ

	ANIME			m_motionType;					// モーションタイプ(現在)
	ANIME			m_motionTypeOld;				// モーションタイプ(過去)
	int				m_nMaxModelType;				// モデルのタイプ数
	int				m_nMaxModelParts;				// 扱うモデルパーツ数
	int				m_nMaxMotion;					// モーション数

	int				m_type;						// タイプ
	int				m_shadow;					// 影番号
	int				m_invincible;				// 無敵時間
	float			m_consumption;				// 計算用

	bool			m_bMotionBlend;				// モーションブレンド
	bool			m_bMotion;					// モーションを使用状況

	bool			m_isUse;					// 使ってるか使ってないか
	bool			m_isLoop;					// ループするかしないか

	int				m_time;		// タイムの最大数
	int				m_nparts;	// パーツの最大数
	int				m_pow;		// ジャンプパワー
	int				m_nMotion;	// モーション番号
};
#endif
