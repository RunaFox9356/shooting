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
#include "hamada.h"
#include "sound.h"

//=============================================================================
// コンストラクタ関数
//=============================================================================
CHit::CHit():C3dpolygon(1)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CHit::~CHit()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CHit::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_BULLET);

	
	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CHit::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CHit::Update()
{
	C3dpolygon::Update();

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

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	C3dpolygon::Draw();

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
	
	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(D3DXVECTOR3(pos.x, pos.y+50.0f, 0.0f));
 		pObject->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
  		pObject->SetAnimation(8,1);
		//CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
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
		case CPlayer::NOW_NON:
			pObject->SetTexture(CTexture::TEXTURE_HIT);
			
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
	C3dpolygon::SetTexture(tex);
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
			Uninit();
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