//=============================================================================
//
// ���@�̃X�g�b�N������
// Author : �l�c����
//
//=============================================================================

#include "magic.h"

int CMagic::MagicCount = 0;			// �ő吔

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CMagic::CMagic()
{
	m_MagicId = MagicCount;
	MagicCount++;
}

//=============================================================================
// �f�X�X�g���N�g�֐�
//=============================================================================
CMagic::~CMagic()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CMagic::Init()
{
	CObject2d::Init();

	m_DivisionX = 8;
	m_DivisionY = 1;
	m_DivisionMAX = m_DivisionY*m_DivisionX;
	m_CounterAnim = 0;
	m_PatternAnim = 0;
	//�\�����W���X�V
	SetTex(TexVec4(
		1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

	//CObject2d::SetTexture(CTexture::TEXTURE_FIRE);

	if (MagicCount >= 4)
	{
		MagicCount = 3;
		CObject::Release();
	}

	return S_OK;
}

//=============================================================================
// �j���֐�
//=============================================================================
void CMagic::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMagic::Update()
{

	CObject2d::Update();

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
		SetTex(TexVec4(
			1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
			, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));
	}
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (this->m_nID != *pObject->GetId())
			{
				if (Type == CObject::MAGIC)
				{
					const D3DXVECTOR3 *MagicPos = pObject->GetPos();

					float size = 20.0f;

					if (((m_pos.y - size) <= (MagicPos->y + size)) &&
						((m_pos.y + size) >= (MagicPos->y - size)) &&
						((m_pos.x - size) <= (MagicPos->x + size)) &&
						((m_pos.x + size) >= (MagicPos->x - size)))
					{
						m_pos.x += 100.0f;
						return;
					}
				}
			}
		}
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CMagic::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// �����֐�
//=============================================================================
CMagic * CMagic::Create(D3DXVECTOR3 pos)
{
	CMagic * pObject = nullptr;
	pObject = new CMagic;

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->Init();
	}

	return pObject;
}


//=============================================================================
// �����֐�
//=============================================================================
void CMagic::SelectTex(CTexture::TEXTURE tex)
{
	CObject2d::SetTexture(tex);
}

//=============================================================================
// ����ւ�
//=============================================================================
void CMagic::Magicplay()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::MAGIC)
			{
				if (this->m_MagicId != *pObject->m_MagicId)
				{

					m_MagicId
				}
			}
		}
	}
}
//=============================================================================
// Get�iMagicId�j
//=============================================================================
int CMagic::GetMagicId()
{
	return m_MagicId;
}