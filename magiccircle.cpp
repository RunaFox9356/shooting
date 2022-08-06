//=============================================================================
//
// CRYSTAL
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "magiccircle.h"
#include "manager.h"
#include "utility.h"
#include "camera.h"
#include "hamada.h"
#include "hit.h"
#include "player.h"
#include "game.h"
#include "particle_manager.h"
int CMagicCircleManager::CMagicCircle::m_popType = 2;

//=============================================================================
// コンストラクト関数
//=============================================================================
CMagicCircleManager::CMagicCircle::CMagicCircle() :C3dpolygon(0)
{
}

//=============================================================================
// デストラクト関数
//=============================================================================
CMagicCircleManager::CMagicCircle::~CMagicCircle()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CMagicCircleManager::CMagicCircle::Init()
{
	C3dpolygon::Init();
	m_isEndAnimation = true;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CMagicCircleManager::CMagicCircle::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CMagicCircleManager::CMagicCircle::Update()
{
	C3dpolygon::Update();

	if (m_Size.x <= m_DefaultSize.x)
	{
		m_Size += m_DefaultSize / m_DecreasingRate;
		m_nTimer++;
		SetSize(m_Size);
	}
	CPlayer* cPlayer = CGame::GetPlayer();  // ダウンキャスト
	const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
	m_pos = *PlayerPos;

	CParticleManager* particleManager = CGame::GetParticleManager();
	if (particleManager->GetEmitter().size() == 0)
	{
		m_isEndAnimation = false;
	}
	if (!m_isEndAnimation)
	{
		m_Size -= m_DefaultSize / (m_DecreasingRate*0.5f);

		if (m_Size.x <= 0.0f)
		{
			Release();
		}
	}

}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CMagicCircleManager::CMagicCircle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);

	C3dpolygon::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create関数
//=============================================================================
CMagicCircleManager::CMagicCircle *CMagicCircleManager::CMagicCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CMagicCircle * pObject = nullptr;
	pObject = new CMagicCircle;

	if (pObject != nullptr)
	{
		pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
		pObject->Init();

		//出てくるタイプの設定
		m_popType++;

		if (m_popType >= 6)
		{
			m_popType = 2;
		}

		pObject->SetType(m_popType);

		//色の設定
		switch (m_popType)
		{
		case NOW_FIRE:
			pObject->SetCollar(PositionVec4(1.0f, 0.0f, 0.0f, 0.8f));
			break;
		case NOW_ICE:
			pObject->SetCollar(PositionVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case NOW_STORM:
			pObject->SetCollar(PositionVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case NOW_SUN:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		default:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			break;
		}
	}

	return pObject;
}
//=============================================================================
// Setmove関数
//=============================================================================
void CMagicCircleManager::CMagicCircle::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// SetType関数
//=============================================================================
void CMagicCircleManager::CMagicCircle::SetType(const int&myType)
{
	m_myType = myType;
}

//=============================================================================
// create関数
//=============================================================================
CMagicCircleManager * CMagicCircleManager::Create(D3DXVECTOR3 pos)
{

	CMagicCircleManager*object = nullptr;
	object = new CMagicCircleManager;

	for (int i = 0; i < 3; i++)
	{
		object->MagicCircle[i] = nullptr;
		object->MagicCircle[i] = CMagicCircle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		
		if (object->MagicCircle[i] != nullptr)
		{
			object->MagicCircle[i]->Init();
			object->MagicCircle[i]->SetPos(pos);
			object->MagicCircle[i]->SetDecreasingRate(30.0f + (20.0f*i));
			object->MagicCircle[i]->SetTexture((CTexture::TEXTURE)((int)CTexture::TEXTURE_MAGICCIRCLE1+ rand() % 4 + 0));
			object->MagicCircle[i]->SetSize(D3DXVECTOR3(1.0f + (10.0f*i), 1.0f + (10.0f*i), 0.0f));
			object->MagicCircle[i]->SetDefaultSize(D3DXVECTOR3(100.0f+(70.0f*i), 100.0f + (70.0f * i), 0.0f));
			object->MagicCircle[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));

		}
	}

	return object;
}
