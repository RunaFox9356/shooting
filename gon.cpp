//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "gon.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CGon::CGon()
{
	 m_CounterAnim = 0;
	 m_PatternAnim = 0;
	 m_DivisionX = 0;
	 m_DivisionY = 0;
	 m_DivisionMAX = 0;
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CGon::~CGon()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CGon::Init()
{
	CObject2d::Init();

	m_DivisionX = 1;
	m_DivisionY = 4;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	//�\�����W���X�V
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnim / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnim / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

	CObject2d::SetTexture(CTexture::TEXTURE_GON);

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CGon::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CGon::Update()
{
	CObject2d::Update();
	m_pos += m_move;
	if (m_pos.y >SCREEN_HEIGHT)
	{
		CObject::Release();
	}

	//�A�j���[�V�����ݒ�
	m_CounterAnim++;
	if ((m_CounterAnim % 10) == 0)//�����ő��x����
	{							
		m_PatternAnim = (m_PatternAnim + 1) % m_DivisionMAX;
		
		//�\�����W���X�V
		SetTex(PositionVec4(
			  1.0f / m_DivisionX * (m_PatternAnim / (m_DivisionX))
			, 1.0f / m_DivisionX *(m_PatternAnim / (m_DivisionX)) + 1.0f / m_DivisionX
			, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY))
			, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY) + 1.0f / m_DivisionY* m_DivisionY)));
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CGon::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// create�֐�
//=============================================================================
CGon *CGon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CGon * pObject = nullptr;
	pObject = new CGon;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(pos);
		pObject->Init();
	}

	return pObject;
}

//=============================================================================
// Setmove�֐�
//=============================================================================
void CGon::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
