//============================
//
// ライフ設定
// Author:hamada ryuuga
//
//============================

#include "life.h"
#include "hamada.h"
#include "manager.h"
#include "player.h"
#include "game.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CLife::CLife(int list) :CObject2d(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CLife::~CLife()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CLife::Init()
{
	CObject2d::Init();
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CLife::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CLife::Update()
{
	VERTEX_2D *pVtx; //頂点へのポインタ

	 //頂点バッファをロックし頂点情報へのポインタを取得
	GetVtx()->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// 計算用マトリックス

					//マトリックス作成
	D3DXMatrixIdentity(&mtx);

	//頂点座標
	for (int i = 0; i < 2; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);
		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_fSize.x);//<-サイズ変更
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_fSize.y);//<-サイズ変更
		pVtx[i].pos.z = 0.0f;
	}

	//頂点バッファをアンロック
	GetVtx()->Unlock();
}

//------------------------------------
// 描画
//------------------------------------
void CLife::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2d::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CLife *CLife::Create(const D3DXVECTOR3 & pos)
{
	CLife * pObject = nullptr;
	pObject = new CLife(0);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(300.0f, 50.0f, 0.0f));
		pObject->SetPos(pos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * CLife::GetPos() const
{
	return &m_pos;
}

void CLife::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

void CLife::SetMove(const D3DXVECTOR3 & move)
{
	//	m_move = move;
}

void CLife::SetDamage(const int Damage)
{
	m_fSize.x -= Damage;
	CPlayer* cPlayer = CGame::GetPlayer();

}
