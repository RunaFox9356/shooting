//=============================================================================
//
// Object
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"

int CBullet::m_AllMember;
LPDIRECT3DTEXTURE9	CBullet::m_pTexture;

//=============================================================================
// コンストラクト関数
//=============================================================================
CBullet::CBullet()
{
	m_AllMember++;
}

//=============================================================================
// デストラクト関数
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CBullet::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_KEN);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CBullet::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CBullet::Update()
{
	C3dpolygon::Update();
	m_pos += m_move;
	if (m_pos.y >SCREEN_HEIGHT)
	{
		CObject::Release();
	}
	if (m_pos.x >SCREEN_WIDTH)
	{
		CObject::Release();
	}
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::ENEMY)
			{
				const D3DXVECTOR3 *enemyPos = pObject->GetPos();
				float enemySize = 20.0f;
				float size = 50.0f;

				if (((m_pos.y - size) <= (enemyPos->y + enemySize)) &&
					((m_pos.y + size) >= (enemyPos->y - enemySize)) &&
					((m_pos.x - size) <= (enemyPos->x + enemySize)) &&
					((m_pos.x + size) >= (enemyPos->x - enemySize)))
				{  
					// 当たり判定
					pObject->Release();

				    // 解放
					CObject::Release();
					return;
				}
			}
		}
	}


}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBullet::Draw()
{

	C3dpolygon::Draw();
	//加算合成初期化

}

//=============================================================================
// create関数
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos ,D3DXVECTOR3 move)
{
	CBullet * pObject = nullptr;
	pObject = new CBullet;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(pos);
		pObject->Init();
	}

	return pObject;
}
//=============================================================================
// Setmove関数
//=============================================================================
void CBullet::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// Lood関数
//=============================================================================
void CBullet::Load()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

	//テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ken.png",
		&m_pTexture);
}

//=============================================================================
// UnLood関数
//=============================================================================
void CBullet::UnLoad()
{
	// 破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}

//=============================================================================
// Gettex関数
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::GetTex()
{
	return m_pTexture;
}