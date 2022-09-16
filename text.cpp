//============================
//
// �e�L�X�g
// Author:hamada ryuuga
//
//============================

#include "text.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CText::CText(int list) : CObject2d(list)
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CText::~CText()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CText::Init()
{
	m_Text = "";
	CObject2d::Init();
	
	col = PositionVec4(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(
		0.0f, 1.0f, 0.0f, 1.0f));

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 38, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("FZ�S���^����"), &m_pFont);

	isRelease = false;
	m_DesTimar = 0;

	return S_OK;
}

//=============================================================================
// �j���֐�
//=============================================================================
void CText::Uninit()
{
	CObject2d::Uninit();
}


//=============================================================================
// �X�V�֐�
//=============================================================================
void CText::Update()
{
	CObject2d::Update();


	if (isRelease)
	{
		m_DesTimar--;

		m_AddCount++;
		if (m_AddCount>=m_Addnumber)
		{
			if (m_AddLetter <= m_TextSize)
			{
				m_Text+=m_ALLText[m_AddLetter];
				m_Text += m_ALLText[m_AddLetter+1];
				m_AddLetter+=2;
			}
			m_AddCount = 0;
		}
		//col.P3 -= 1.0f / m_DesTimarMax;

		//m_pos.y -= 1.0f;

		CObject2d::SetCollar(col);

		if (m_DesTimar <= 0)
		{
			Uninit();
		}
	}


}

//=============================================================================
// �`��֐�
//=============================================================================
void CText::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();


	RECT rect = { 60, 500, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T(m_Text.c_str()));

	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �V�K�[�x�l <= Z�o�b�t�@�[�x�l (�����ݒ�)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �����֐�
//=============================================================================
CText *CText::Create(Type talkType, char * Text)
{
	CText * pObject = nullptr;
	pObject = new CText(2);

	if (pObject != nullptr)
	{
		pObject->Init();
		switch (talkType)
		{
		case CText::GON:
			pObject->SetTexture(CTexture::TEXTURE_GONBOX);
			break;
		case CText::MASUO:
			pObject->SetTexture(CTexture::TEXTURE_MASUOBOX);
			break;
		case CText::MAX:
			break;
		default:
			break;
		}
		pObject->SetPos(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
		pObject->SetSize(D3DXVECTOR3(640.0f, 200.0f, 0.0f));

		pObject->Releasetimer(120);
		pObject->TextLetter(Text);
	}

	return pObject;
}


//=============================================================================
// �����܂ł̎��Ԑݒ�֐�
//=============================================================================
void CText::Releasetimer(int nTimar)
{
	m_DesTimar = nTimar;
	m_DesTimarMax = m_DesTimar;
	isRelease = true;
}

//=============================================================================
// �����܂ł̎��Ԑݒ�֐�
//=============================================================================
void CText::TextLetter(char * Text)
{
	m_ALLText = Text;
	m_TextSize = m_ALLText.size();
	m_Addnumber = m_DesTimarMax / m_TextSize;
	m_AddLetter = 0;
}
