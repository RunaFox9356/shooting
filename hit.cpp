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
#include "hamada.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CHit::CHit():C3dpolygon(1)
{
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CHit::~CHit()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CHit::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_BULLET);

	
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CHit::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CHit::Update()
{
	C3dpolygon::Update();

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

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	C3dpolygon::Draw();

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
// �e�N�X�`���̐ݒ�֐�
//=============================================================================
void CHit::SelectTex(CTexture::TEXTURE tex)
{
	C3dpolygon::SetTexture(tex);
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
			Uninit();
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