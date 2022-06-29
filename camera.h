//============================
//
// カメラ設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "renderer.h"

//構造体
typedef struct
{
	D3DXVECTOR3 posV;	//位置
	D3DXVECTOR3 posR;	//注視点
	D3DXVECTOR3 vecU;	//ベクトル
	D3DXVECTOR3 directionV; //回転の向き位置
	D3DXVECTOR3 directionR;//回転の向き注視点
	D3DXVECTOR3 rot;//位置回転
	float fDistance;//距離
	float fDistanceY;
	bool bBool;
	D3DVIEWPORT9 viewport;
	D3DXVECTOR3 posVDest, posRDest;
	D3DXMATRIX MtxProje; //プロジェクションマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	D3DXMATRIX MtxView; //ビューマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
}CAMERA;



class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);//初期化
	void Uninit(void);//破棄
	void Update(void);//更新
	void Set(void);//画面設定
	CAMERA *Get(void); //ゲット
	D3DXMATRIX *GetMtxProje();
	D3DXMATRIX *GetMtxView();
private:
	 float m_Speed = 1.0f;

	 float m_rotSpeed = 0.05f;
	 float m_rotSpeed2 = D3DX_PI / 2;

	//スタティック変数
	 CAMERA m_aCamera;
	 float m_rot;
};
#endif

