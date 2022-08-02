//============================
//
// �w�i�ݒ�
// Author:hamada ryuuga
//
//============================

#include "bg.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBg::CBg()
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBg::~CBg()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBg::Init()
{
	CObject2d::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CBg::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CBg::Update()
{
	CObject2d::Update();
}

//------------------------------------
// �`��
//------------------------------------
void CBg::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBg *CBg::Create()
{
	CBg * pObject = nullptr;
	pObject = new CBg;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(1280.0f, 1280.0f, 0.0f));
		//pObject->SetTexture(CTexture::);
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CBg::GetPos() const
{
	return &m_pos;
}

void CBg::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

void CBg::SetMove(const D3DXVECTOR3 & move)
{
	m_move = move;
}
