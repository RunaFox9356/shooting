//=============================================================================
//
// Object
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
int CCrystal::m_popType = 2;
LPDIRECT3DTEXTURE9	CCrystal::m_pTexture;

//=============================================================================
// コンストラクト関数
//=============================================================================
CCrystal::CCrystal()
{
}

//=============================================================================
// デストラクト関数
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
	m_move.y-=0.1f;
	if (m_move.y <= -5.0f)
	{
		//m_move.y = 5.0f;
	}
	m_pos += m_move;

	if (m_pos.y <-SCREEN_HEIGHT)
	{
		m_move.y = 13.0f;
		//CObject::Release();
	}
	for (int i = 0; i < MAX_OBJECT; i++)
	{	// 当たり判定
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::PLAYER)
			{	// Playerとの当たり判定
				CPlayer* cPlayer = dynamic_cast<CPlayer*>(pObject);  // ダウンキャスト
				const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
				float Size = 50.0f;
				
				if (((m_pos.y - m_Size.y) <= (PlayerPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (PlayerPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (PlayerPos->x + Size)) &&
					((m_pos.x + m_Size.x) >= (PlayerPos->x - Size)))
				{
					CManager::GetMagicBox()->Magicplay((CTexture::TEXTURE)m_myType);
				
					CObject::Release();

					return;
				}
			}
			if (Type == CObject::BULLET)
			{	// たまとの当たり判定
				CBullet* bullet = dynamic_cast<CBullet*>(pObject);  // ダウンキャスト
				const D3DXVECTOR3 *BulletPos = bullet->GetPos();
		
				float Size = 40.0f;

				if (((m_pos.y - m_Size.y) <= (BulletPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (BulletPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (BulletPos->x + Size)) &&
					((m_pos.x + m_Size.x) >= (BulletPos->x - Size)))
				{
					//m_move.y += 5.0f;
					return;
				}
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
		case 2:
  			pObject->SetCollar(TexVec4(1.0f,0.0f,0.0f,0.8f));
			break;
		case 3:
			pObject->SetCollar(TexVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case 4:
			pObject->SetCollar(TexVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case 5:
			pObject->SetCollar(TexVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		default:
			pObject->SetCollar(TexVec4(1.0f, 1.0f, 1.0f, 0.8f));
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