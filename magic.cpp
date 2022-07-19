//=============================================================================
//
// ���@�̃X�g�b�N������
// Author : �l�c����
//
//=============================================================================

#include "magic.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CMagicBox::CMagic::CMagic()
{


}

//=============================================================================
// �f�X�X�g���N�g�֐�
//=============================================================================
CMagicBox::CMagic::~CMagic()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CMagicBox::CMagic::Init()
{
	CObject2d::Init();

	m_DivisionX = 8;
	m_DivisionY = 1;
	m_DivisionMAX = m_DivisionY*m_DivisionX;
	m_CounterAnim = 0;
	m_PatternAnim = 0;

	//�\�����W���X�V
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));


	return S_OK;
}

//=============================================================================
// �j���֐�
//=============================================================================
void CMagicBox::CMagic::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMagicBox::CMagic::Update()
{

	CObject2d::Update();

	//�A�j���[�V�����ݒ�
	m_CounterAnim++;
	if ((m_CounterAnim % 10) == 0)//�����ő��x����
	{
		m_PatternAnim = (m_PatternAnim + 1) % m_DivisionMAX;

		//�\�����W���X�V
		SetTex(PositionVec4(
			1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
			, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));
	}
	
}

//=============================================================================
// �`��֐�
//=============================================================================
void CMagicBox::CMagic::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// �����֐�
//=============================================================================
CMagicBox* CMagicBox::Create(D3DXVECTOR3 pos)
{

	CMagicBox*object = nullptr;
	object = new CMagicBox;

	for (int i = 0; i < 3; i++)
	{
		object->cMagic[i] = nullptr;
		object->cMagic[i] = new CMagic;
		float posX = pos.x + 100 * i;
		if (object->cMagic[i] != nullptr)
		{
			object->cMagic[i]->SetPos(D3DXVECTOR3(posX, pos.y, pos.z));
			object->cMagic[i]->Init();
			object->cMagic[i]->SelectTex(CTexture::TEXTURE_NONE);
			object->cMagic[i]->SetSize(80);
		}
	}
	return object;
}


//=============================================================================
// �����֐�
//=============================================================================
void CMagicBox::CMagic::SelectTex(CTexture::TEXTURE tex)
{
	CObject2d::SetTexture(tex);
	
}

//=============================================================================
// ����ւ�
//=============================================================================
void CMagicBox::Magicplay(CTexture::TEXTURE TEX)
{
	bool bHave = false;
  	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{
			
			bHave = true;
			cMagic[2]->SelectTex(cMagic[1]->GetTexture());
			cMagic[1]->SelectTex(cMagic[0]->GetTexture());
			cMagic[0]->SelectTex(TEX);
			CPlayer::SetMagic((CPlayer::NOWMAGIC)TEX);
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
			i = 2;
		}
		
	}
	if (!bHave)
	{
		cMagic[2]->SelectTex(cMagic[1]->GetTexture());
		cMagic[1]->SelectTex(cMagic[0]->GetTexture());
		cMagic[0]->SelectTex(TEX);
		CPlayer::SetMagic((CPlayer::NOWMAGIC)TEX);
	}
	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}
//=============================================================================
// �͂�����
//=============================================================================
void CMagicBox::MagicRelease(void)
{
	bool bHave = false;
	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{

			bHave = true;
			cMagic[0]->SelectTex(cMagic[1]->GetTexture());
			cMagic[1]->SelectTex(cMagic[2]->GetTexture());
			cMagic[2]->SelectTex(CTexture::TEXTURE_NONE);
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
			CPlayer::SetMagic((CPlayer::NOWMAGIC)cMagic[0]->GetTexture());
			i = 2;
		}

	}
	if (!bHave)
	{
		cMagic[0]->SelectTex(cMagic[1]->GetTexture());
		cMagic[1]->SelectTex(cMagic[2]->GetTexture());
		cMagic[2]->SelectTex(CTexture::TEXTURE_NONE);
		CPlayer::SetMagic((CPlayer::NOWMAGIC)cMagic[0]->GetTexture());

	}
	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}