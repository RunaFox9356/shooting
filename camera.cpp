//============================
//
// カメラ設定
// Author:hamada ryuuga
//
//============================
#include "camera.h"
#include "input.h"

#include "manager.h"

//----------------------------
//コンストラクト
//----------------------------
CCamera::CCamera()
{
}

//----------------------------
//デストラクト
//----------------------------
CCamera::~CCamera()
{
}
//----------------------------
//初期化処理
//----------------------------
void CCamera::Init(void)
{
	m_aCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//視点　注視点　上方向　設定
	m_aCamera.posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_aCamera.posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_aCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_aCamera.directionR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aCamera.directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aCamera.bBool = true;

	m_aCamera.fDistance = sqrtf((m_aCamera.posR.x - m_aCamera.posV.x) *
		(m_aCamera.posR.x - m_aCamera.posV.x) +
		(m_aCamera.posR.z - m_aCamera.posV.z) *
		(m_aCamera.posR.z - m_aCamera.posV.z));

	m_aCamera.fDistance = sqrtf((m_aCamera.posR.y - m_aCamera.posV.y)*
		(m_aCamera.posR.y - m_aCamera.posV.y) +
		(m_aCamera.fDistance*m_aCamera.fDistance));

	m_aCamera.rot.x = atan2f((m_aCamera.posR.z - m_aCamera.posV.z),
		(m_aCamera.posR.y - m_aCamera.posV.y));
}

//----------------------------
//終了処理
//----------------------------
void CCamera::Uninit(void)
{
}

//----------------------------
//更新処理
//----------------------------
void CCamera::Update(void)
{
	
}

//----------------------------
//描画処理
//----------------------------
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9  pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ

	//ビューマトリックスを初期化
	D3DXMatrixIdentity(&m_aCamera.MtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_aCamera.MtxView,
		&m_aCamera.posV,
		&m_aCamera.posR,
		&m_aCamera.vecU);

	//適用
	pDevice->SetTransform(D3DTS_VIEW, &m_aCamera.MtxView);

	//プロジェクションマトリックスを初期化
	D3DXMatrixIdentity(&m_aCamera.MtxProje);

	////プロジェクションマトリックス作成
	//D3DXMatrixPerspectiveFovLH(&m_aCamera.MtxProje,
	//	D3DXToRadian(90.0f),
	//	(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//	10.0f,
	//	10000.0f);

	// プロジェクションマトリックスの作成(平行投影)
	D3DXMatrixOrthoLH(&m_aCamera.MtxProje,					// プロジェクションマトリックス
		(float)SCREEN_WIDTH,								// 幅
		(float)SCREEN_HEIGHT,								// 高さ
		10.0f,												// ニア
		1000.0f);											// ファー

	//適用
	pDevice->SetTransform(D3DTS_PROJECTION, &m_aCamera.MtxProje);
}

//----------------------------
//Get
//----------------------------
CCamera::CAMERA * CCamera::Get(void)
{
	return &m_aCamera;
}

//----------------------------
//Get
//----------------------------
D3DXVECTOR3 *CCamera::GetPos()
{
	return &m_aCamera.posV;
}

D3DXMATRIX  *CCamera::GetMtxProje()
{
	return &m_aCamera.MtxProje;
}
D3DXMATRIX *CCamera::GetMtxView()
{
	return &m_aCamera.MtxView;
}