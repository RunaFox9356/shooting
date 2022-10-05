//=============================================================================
//
// CRYSTAL
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "crystal.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "magic.h"
#include "hamada.h"
#include "player.h"
#include "bullet.h"
#include "score.h"
#include "game.h"
#include "hit.h"

#include "tutorial.h"
int CCrystal::m_popType = 2;
LPDIRECT3DTEXTURE9	CCrystal::m_pTexture;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CCrystal::CCrystal() :C3dpolygon(1)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CCrystal::~CCrystal()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CCrystal::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_CRYSTAL);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CCrystal::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CCrystal::Update()
{
	C3dpolygon::Update();
	m_move.y -= 0.1f;
	m_move.x = -1.0f;

	m_pos += m_move;

	if (m_pos.y < -SCREEN_HEIGHT)
	{
		m_move.y = 13.0f;
		//CObject::Release();
	}
		// 当たり判定
		CObject**pObject;
		pObject = GetObjectData(0);

		for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
		{
			if (pObject[nObject] == nullptr)
			{
				continue;
			}
			EObjectType Type = pObject[nObject]->GetType();
			if (Type == CObject::PLAYER)
			{	// Playerとの当たり判定
				CPlayer* cPlayer = nullptr;
				switch (*CManager::GetMode())
				{
				case CManager::MODE_GAME:
					cPlayer = CGame::GetPlayer();
					break;
				case CManager::MODE_TUTORIAL:
					cPlayer = CTutorial::GetPlayer();
					break;
				default:
					break;
				}
				const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
				float Size = 50.0f;

				//当たり判定のサイズ
				if (((m_pos.y - m_Size.y) <= (PlayerPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (PlayerPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (PlayerPos->x + Size)) &&
					((m_pos.x + m_Size.x) >= (PlayerPos->x - Size)))
				{
					if (m_Hit <= 30)
					{
						switch (*CManager::GetMode())
						{			
						case CManager::MODE_GAME:
							CGame::GetMagicBox()->Magicplay((CTexture::TEXTURE)m_myType);
							break;
						case CManager::MODE_TUTORIAL:
							CTutorial::GetMagicBox()->Magicplay((CTexture::TEXTURE)m_myType);
							break;
						default:
							break;
						}
					
						GetScore()->Add(200);
					}
					else
					{
						GetScore()->Add(1000);
					}

					Uninit();

					return;
				}
			}
			if (Type == CObject::BULLET|| Type == CObject::RANKUPBULLET)
			{	// たまとの当たり判定
				CBullet* bullet = dynamic_cast<CBullet*>(pObject[nObject]);  // ダウンキャスト
				const D3DXVECTOR3 *BulletPos = bullet->GetPos();

				float Size = 40.0f;

				if (((m_pos.y - m_Size.y) <= (BulletPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (BulletPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (BulletPos->x + Size)) &&
					((m_pos.x + m_Size.x) >= (BulletPos->x - Size)))
				{
					m_move.y = 5.0f;
					m_Hit++;
					m_move.x = 1.5f;
					if (m_Hit <= 30)
					{//出てくるタイプの設定
						m_myType++;

						if (m_myType >= 6)
						{
							m_myType = 2;
						}

						CHit::Create(m_pos, 6);
						//色の設定
						switch (m_myType)
						{
						case NOW_FIRE:
							SetColar(PositionVec4(1.0f, 0.0f, 0.0f, 0.8f));
							break;
						case NOW_ICE:
							SetColar(PositionVec4(0.0f, 0.0f, 1.0f, 0.8f));
							break;
						case NOW_STORM:
							SetColar(PositionVec4(0.0f, 1.0f, 0.0f, 0.8f));
							break;
						case NOW_SUN:
							SetColar(PositionVec4(1.0f, 1.0f, 0.0f, 0.8f));
							break;
						default:
							SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
							break;
						}
					}
					else
					{
						SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
					}
					pObject[nObject]->Release();
					if (Type != CObject::RANKUPBULLET)
					{
						CBullet::Create(m_pos, D3DXVECTOR3(15.0f, 3.0f, 0.0f), m_myType)->SetUp(EObjectType::RANKUPBULLET);
						CBullet::Create(m_pos, D3DXVECTOR3(15.0f, -3.0f, 0.0f), m_myType)->SetUp(EObjectType::RANKUPBULLET);
					}
					return;
				}
			}
		
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CCrystal::Draw()
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
CCrystal *CCrystal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CCrystal * pObject = nullptr;
	pObject = new CCrystal;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(D3DXVECTOR3 (pos.x, pos.y,0.0f));
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(30.0f,80.0f, 0.0f));	
		
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
			pObject->SetColar(PositionVec4(1.0f, 0.0f, 0.0f, 0.8f));
			break;
		case NOW_ICE:
			pObject->SetColar(PositionVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case NOW_STORM:
			pObject->SetColar(PositionVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case NOW_SUN:
			pObject->SetColar(PositionVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		default:
			pObject->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			break;
		}
	}

	return pObject;
}
//=============================================================================
// Setmove関数
//=============================================================================
void CCrystal::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// SetType関数
//=============================================================================
void  CCrystal::SetType(const int&myType)
{
	m_myType = myType;
}
//=============================================================================
// Gettex関数
//=============================================================================
LPDIRECT3DTEXTURE9 CCrystal::GetTex()
{
	return m_pTexture;
}