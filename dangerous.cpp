//============================
//
// ライフ設定
// Author:hamada ryuuga
//
//============================

#include "dangerous.h"
#include "hamada.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "enemy.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CDangerousManager::CDangerousManager(int list) :CObject2d(list)
{
	for (int i = 0; i < Max; i++)
	{
		m_object2d[i] = nullptr;
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//------------------------------------
// デストラクタ
//------------------------------------
CDangerousManager::~CDangerousManager()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CDangerousManager::Init()
{
	CObject2d::Init();

	m_PopTimeCount = 0;
	m_PopOn = false;
	
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CDangerousManager::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CDangerousManager::Update()
{
	CObject2d::Update();
	m_PopTimeCount++;

	if (m_PopTimeCount >= m_PopTime)
	{
		if (!m_PopOn)
		{
			D3DXVECTOR3 Pos(0.0f, m_pos.y, 0.0f);
			D3DXVECTOR3 Rot(0.0f, 0.0f, 0.0f);
			for (int i = 0; i < Max; i++)
			{
				m_object2d[i] = CDangerous::Create(Pos);
				m_object2d[i]->SetTexture(CTexture::TEXTURE_DANGEROUS);
				m_object2d[i]->SetRot(Rot);
				Pos += D3DXVECTOR3(260.0f, 0.0f, 0.0f);
			}
			m_PopOn = true;
		}

		m_move.x += (0.0f - m_move.x)* 0.5f;//（目的の値-現在の値）＊減衰係数

		for (int i = 0; i < Max; i++)
		{
			m_object2d[i]->SetMove(m_move);
			
			float a = sinf((float)m_PopTimeCount*0.08f);
			m_object2d[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, a));	
		}
	}
	if (m_PopTimeCount >= m_PopTime+300)
	{
		SetMove(-m_BackMove);
	}
}

//------------------------------------
// 描画
//------------------------------------
void CDangerousManager::Draw()
{
}

//------------------------------------
// create
//------------------------------------
CDangerousManager *CDangerousManager::Create(const D3DXVECTOR3 & pos, const int PopTime)
{
	CDangerousManager * pObject = nullptr;
	pObject = new CDangerousManager(1);

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->Init();
		pObject->m_PopTime = PopTime;
		pObject->SetMove(D3DXVECTOR3(520.0f, 0.0f, 0.0f));
		pObject->m_BackMove = D3DXVECTOR3(520.0f, 0.0f, 0.0f);
	}

	return pObject;
}
//------------------------------------
// create
//------------------------------------
void CDangerousManager::BossPopStaging()
{
	CDangerousManager::Create(D3DXVECTOR3(0.0f, 125.0f, 0.0f),0);

	CDangerousManager::Create(D3DXVECTOR3(0.0f, 370.0f, 0.0f),0);

	CDangerousManager::Create(D3DXVECTOR3(0.0f, 620.0f, 0.0f),0);

	CObject::SetBossPop(true);
	CEnemy::SetBoss();
	
}
//------------------------------------
// コンストラクタ
//------------------------------------
CDangerous::CDangerous(int list) :CObject2d(list)
{
	m_rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//------------------------------------
// デストラクタ
//------------------------------------
CDangerous::~CDangerous()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CDangerous::Init()
{
	CObject2d::Init();

	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CDangerous::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CDangerous::Update()
{
	CObject2d::Update();

	m_move.x += (0.0f - m_move.x)* 0.5f;//（目的の値-現在の値）＊減衰係数

	m_Size.x += m_move.x;
	m_pos.x -= m_move.x;
}

//------------------------------------
// 描画
//------------------------------------
void CDangerous::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);

	CObject2d::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CDangerous *CDangerous::Create(const D3DXVECTOR3 & pos)
{
	CDangerous * pObject = nullptr;
	pObject = new CDangerous(2);

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(0.0f,125.0f, 0.0f));
		pObject->SetTexture(CTexture::TEXTURE_DANGEROUS);
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return pObject;
}



