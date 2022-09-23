//=============================================================================
//
// CRYSTAL
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "bossdeath.h"
#include "manager.h"
#include "hamada.h"
#include "game.h"


//=============================================================================
// コンストラクト関数
//=============================================================================
CDeath::CDeath() :C3dpolygon(1)
{
}

//=============================================================================
// デストラクト関数
//=============================================================================
CDeath::~CDeath()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CDeath::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_ENDBG);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CDeath::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CDeath::Update()
{
	C3dpolygon::Update();

}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CDeath::Draw()
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
CDeath *CDeath::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CDeath * pObject = nullptr;
	pObject = new CDeath;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(180.0f, 180.0f, 0.0f));
	}

	return pObject;
}
