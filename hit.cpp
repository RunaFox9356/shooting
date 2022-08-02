//=============================================================================
//
// ����
// Author : �l�c����
//
//=============================================================================

#include "hit.h"
#include <assert.h>
#include "player.h"
#include "utility.h"
#include "manager.h"


//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CHit::CHit()
{

}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CHit::~CHit()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CHit::Init()
{
	CObject2d::Init();

	CObject2d::SetTexture(CTexture::TEXTURE_BULLET);

	
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CHit::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CHit::Update()
{
	CObject2d::Update();

	//�A�j���[�V�����ݒ�
	m_CounterAnim++;
	if ((m_CounterAnim % 5) == 0)//�����ő��x����
	{
		PlayAnimation();
	}

}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CHit::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2d::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create�֐�
//=============================================================================
CHit *CHit::Create(D3DXVECTOR3 pos,int Type)
{
	CHit * pObject = nullptr;
	pObject = new CHit;

	D3DXVECTOR3 Pos = ScreenCastWorld(
		&pos,			// �X�N���[�����W
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
// �e�N�X�`���̐ݒ�֐�
//=============================================================================
void CHit::SelectTex(CTexture::TEXTURE tex)
{
	CObject2d::SetTexture(tex);
}

//=============================================================================
// Animation�̍Đ��֐�
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

	//�\�����W���X�V
	SetTex(PositionVec4(
		U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V));
}

//=============================================================================
// Animation�̖����ݒ�֐�
//=============================================================================
void CHit::SetAnimation(const int U, const int V)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;
	m_PatternAnimX = 0;
	m_PatternAnimY = 0;

	//�\�����W���X�V
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}