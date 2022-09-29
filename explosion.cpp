//============================
//
// �����ݒ�
// Author:hamada ryuuga
//
//============================

#include "explosion.h"
#include "utility.h"
//------------------------------------
// �R���X�g���N�^
//------------------------------------
CExplosion::CExplosion():CObject2d(0)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CExplosion::~CExplosion()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CExplosion::Init()
{
	m_Timar = 0;
	m_TimaCount = 0;
	CObject2d::Init();

	CObject2d::SetTexture(CTexture::TEXTURE_EXPLOSION);

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CExplosion::Uninit()
{

	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CExplosion::Update()
{
	m_TimaCount++;
	CObject2d::Update();
	if (m_TimaCount >= m_Timar)
	{
		m_PatternAnimX++;

		if (m_PatternAnimX > m_DivisionX)
		{//�A�j���[�V����
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

		SetTex(PositionVec4(
			U * (m_PatternAnimX)
			, U *(m_PatternAnimX)+U
			, V * (m_PatternAnimY)
			, V * (m_PatternAnimY)+V));
		SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

//------------------------------------
// �`��
//------------------------------------
void CExplosion::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CExplosion *CExplosion::Create(D3DXVECTOR3 pos,int timer,bool b3D)
{
	CExplosion * pObject = nullptr;
	pObject = new CExplosion;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 Poppos = pos;
		if (b3D)
		{
			Poppos = ScreenCastWorld(&Poppos,			// �X�N���[�����W
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));								// �X�N���[���T�C�Y
		}
		pObject->Init();
		pObject->SetPos(Poppos);
		pObject->SetSize(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
		pObject->SetAnimation(7, 1);
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		pObject->m_Timar = timer;
	}
	return pObject;
}

//=============================================================================
// Animation�̖����ݒ�֐�
//=============================================================================
void CExplosion::SetAnimation(const int U, const int V)
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