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
	m_object2d[0] = nullptr;
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
	

	m_object2d[0] = CObject2d::Create(1);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_HPCOVER);
	
	m_object2d[0]->SetSize(D3DXVECTOR3(m_Life+5, 50.0f, 0.0f));
	m_object2d[0]->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y-20.0f, m_pos.z));

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

	CObject2d::Update();
	if (m_pos.x <= CPlayer::MAXLIFE*0.5f)
	{
		SetCollar(PositionVec4(1.0f, 1.0f, 0.0f, 1.0f));
	}
	if (m_pos.x <= CPlayer::MAXLIFE*0.15f+5.0f)
	{
		SetCollar(PositionVec4(1.0f, 0.0f, 0.0f, 1.0f));
	}


	m_move.x += (0.0f - m_move.x)* 0.5f;//（目的の値-現在の値）＊減衰係数

	m_Size.x += m_move.x;
	m_pos.x += m_move.x;
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
CLife *CLife::Create(const D3DXVECTOR3 & pos,float Life)
{
	CLife * pObject = nullptr;
	pObject = new CLife(1);

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->m_Life = Life;
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(pObject->m_Life, 20.0f, 0.0f));
		pObject->SetCollar(PositionVec4(0.0f, 1.0f, 0.0f, 1.0f));
		pObject->SetTexture(CTexture::TEXTURE_NONE);
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
	m_move = move;
}

void CLife::SetDamage(const int Damage)
{
	m_move.x -= Damage;
	//m_pos.x -= Damage;
	CPlayer* cPlayer = CGame::GetPlayer();
	cPlayer->HitLife(Damage);
}
