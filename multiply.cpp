//============================
//
// �{��
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"


int CMultiply::m_Rate;
int CMultiply::m_RateWait;
bool CMultiply::m_Decrease;
CNumber * CMultiply::Fastratio[MAXRATE] = {};

//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = (int)log10f((float)nModScore);

	for (int i = 0; i < RATE; i++)
	{
		ratio[i] = nullptr;
	}

	for (int i = nDigits; i >= 0; i--)
	{
		
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	D3DXVECTOR3 ratiopos = Pos;

	ratiopos = ScreenCastWorld(&ratiopos,			// �X�N���[�����W
		D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));									// �X�N���[���T�C�Y
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (int nCntScore = 0; nCntScore <= nDigits; nCntScore++)
	{
		ratio[nCntScore] = CNumber::Create();
		ratio[nCntScore]->SetPos(ratiopos);
		ratiopos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		ratio[nCntScore]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	

		ratio[nCntScore]->SetTex(PositionVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
		if (extinction)
		{
			ratio[nCntScore]->Releasetimer(90);
		}
	}
 	
}

//=============================================================================
//�X�R�A�̐ݒu
//=============================================================================
CMultiply* CMultiply::FastSet(int Number, D3DXVECTOR3 Pos)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	if (Number != 0)
	{	// �����������v�Z
		nDigits = (int)log10f((float)nModScore);
	}
	else
	{
		nDigits = 8;
	}

	//�{���̌�����
	if (m_Decrease)
	{
		m_RateWait = 6000;
	}
	else
	{
		m_RateWait = 6000;	
	}

	for (int i = RATE; i >= 0; i--)
	{
		if (Fastratio[i] == nullptr)
		{//�����̃f�[�^���Ȃ����������
			Fastratio[i] = CNumber::Create();
			Fastratio[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));	
		}

		aPosTexU[i] = 0;
		
	}

	//��̌����������
	for (int i = nDigits; i >= 0; i--)
	{
		aPosTexU[i] = (nModScore % 10);
   		nModScore /= 10;
	}


	D3DXVECTOR3 ratiopos = Pos;

	// �����̈ʒu���v�Z
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (int nCntScore = nDigits; nCntScore >= 0; nCntScore--)
	{

		// �����̈ʒu�Z�b�g
		Fastratio[nCntScore]->SetPos(ratiopos);
		// �����̈ʒu�̍����o��
		ratiopos -= D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		// �����̃T�C�Y������
		Fastratio[nCntScore]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		
		//���l���O���������Ȃ�O������
		/*if (aPosTexU[nCntScore] == 0 && m_Decrease == true)
		{
			if (nCntScore != nDigits)
			{
				Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
			}

		}
		else
		{
			
		}*/
		
		Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		
		// �����̃e�N�X�`���̈ʒu�𒲐�
		Fastratio[nCntScore]->SetTex(PositionVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));

	}
	return nullptr;
}

//=============================================================================
// ������\������֐�
//=============================================================================
CMultiply* CMultiply::list(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	CMultiply * pObject = nullptr;
	pObject = new CMultiply;

	if (pObject != nullptr)
	{
		pObject->set(Number, Pos, extinction);
	}

	return pObject;
}


//=============================================================================
// �X�R�A��\������֐�
//=============================================================================
void CMultiply::SetRate(int Rete)
{
	if (m_Rate <= 256)
	{
		m_Decrease = false;
		m_Rate = Rete;
		CMultiply::FastSet(m_Rate, D3DXVECTOR3(150.0f, 200.0f, 0.0f));
	}
}

CMultiply::CMultiply()
{
}

CMultiply::~CMultiply()
{
}

//=============================================================================
// �j���֐�
//=============================================================================
void CMultiply::Uninit()
{
	for (int nCntScore = 0; nCntScore <= RATE; nCntScore++)
	{
		if (Fastratio[nCntScore] == nullptr)
		{
			return;
		}

		Fastratio[nCntScore]->Uninit();
		Fastratio[nCntScore] = nullptr;
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMultiply::Update()
{
	if (m_Rate > 0)
	{
		m_RateWait--;
	
		if (m_RateWait <= 0)
		{

			m_Decrease = false;
			m_Rate--;
			if (m_Rate <= 0)
			{
				m_Rate = 0;
			}
			
			CMultiply::FastSet(m_Rate, D3DXVECTOR3(150.0f, 200.0f, 0.0f));
		}
	}

}
