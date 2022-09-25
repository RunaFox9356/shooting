//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include "explosion.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CExplosion::CExplosion():CObject2d(1)
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

	CObject2d::Init();

	CObject2d::SetTexture(CTexture::TEXTURE_GOLD);

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
	
	CObject2d::Update();

	m_PatternAnimX++;

	if (m_PatternAnimX > m_DivisionX)
	{//�A�j���[�V����
		m_PatternAnimX = 0;
		m_PatternAnimY++;
		if (m_PatternAnimY >= m_DivisionY)
		{
			m_PatternAnimY = 0;

		}
	}

	float U = 1.0f / (m_DivisionX);
	float V = 1.0f / (m_DivisionY);

	SetTex(PositionVec4(
		U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V));


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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion * pObject = nullptr;
	pObject = new CExplosion;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(pos);
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 100.0f));
		pObject->SetAnimation(5, 4);
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
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