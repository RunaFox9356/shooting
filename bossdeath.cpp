//=============================================================================
//
// CRYSTAL
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "bossdeath.h"
#include "manager.h"
#include "hamada.h"
#include "game.h"


//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CDeath::CDeath() :C3dpolygon(1)
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CDeath::~CDeath()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CDeath::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_ENDBG);

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CDeath::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CDeath::Update()
{
	C3dpolygon::Update();

}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CDeath::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);

	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create�֐�
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
