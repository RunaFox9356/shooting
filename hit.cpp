//=============================================================================
//
// たま
// Author : 浜田琉雅
//
//=============================================================================

#include "hit.h"
#include <assert.h>
#include "player.h"
#include "utility.h"
#include "manager.h"


//=============================================================================
// コンストラクト関数
//=============================================================================
CHit::CHit()
{

}

//=============================================================================
// デストラクト関数
//=============================================================================
CHit::~CHit()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CHit::Init()
{
	CObject2d::Init();

	CObject2d::SetTexture(CTexture::TEXTURE_BULLET);

	
	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CHit::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CHit::Update()
{
	CObject2d::Update();

	//アニメーション設定
	m_CounterAnim++;
	if ((m_CounterAnim % 5) == 0)//ここで速度調整
	{
		PlayAnimation();
	}

}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CHit::Draw()
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

//=============================================================================
// create関数
//=============================================================================
CHit *CHit::Create(D3DXVECTOR3 pos,int Type)
{
	CHit * pObject = nullptr;
	pObject = new CHit;

	D3DXVECTOR3 Pos = ScreenCastWorld(
		&pos,			// スクリーン座標
		D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));

	
	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(D3DXVECTOR3(Pos.x, Pos.y-50.0f, 0.0f));
 		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
  		pObject->SetAnimation(8,1);
		int nType = Type;
		switch (nType)
		{
		case CPlayer::NOW_FIRE:		
			pObject->SetTexture(CTexture::TEXTURE_FIRE);
			break;
		case CPlayer::NOW_ICE:		
			pObject->SetTexture(CTexture::TEXTURE_ICE);
			break;
		case CPlayer::NOW_STORM:		
			pObject->SetTexture(CTexture::TEXTURE_STORM);
			break;
		case CPlayer::NOW_SUN:
			pObject->SetTexture(CTexture::TEXTURE_THUNDER);
			break;
		default:
			pObject->SetTexture(CTexture::TEXTURE_LIGHT);
			break;
		}
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	}
	return pObject;
}

//=============================================================================
// テクスチャの設定関数
//=============================================================================
void CHit::SelectTex(CTexture::TEXTURE tex)
{
	CObject2d::SetTexture(tex);
}

//=============================================================================
// Animationの再生関数
//=============================================================================
void CHit::PlayAnimation()
{

	m_PatternAnimX++;
	if (m_PatternAnimX > m_DivisionX)
	{
		
		m_PatternAnimX = 0;
		m_PatternAnimY++;
		if (m_PatternAnimY >= m_DivisionY)
		{
			m_PatternAnimY = 0;
			CObject::Release();
			return;
		}
	}

	float U = 1.0f / (m_DivisionX);
	float V = 1.0f / (m_DivisionY);

	//表示座標を更新
	SetTex(PositionVec4(
		U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V));
}

//=============================================================================
// Animationの枚数設定関数
//=============================================================================
void CHit::SetAnimation(const int U, const int V)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;
	m_PatternAnimX = 0;
	m_PatternAnimY = 0;

	//表示座標を更新
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}