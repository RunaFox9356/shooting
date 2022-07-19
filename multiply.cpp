//============================
//
// �{��
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"


int CMultiply::m_Rate = 0;
int CMultiply::m_RateWait = 0;
CNumber * CMultiply::Fastratio[10] = {};
//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos, bool extinction)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = log10f(nModScore);

	for (int i = 0; i < 10; i++)
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
		ratio[nCntScore]->SetSize(30);
		ratio[nCntScore]->SetTex(PositionVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
		if (extinction)
		{
			ratio[nCntScore]->Releasetimer(360);
		}
	}
 	
}

CMultiply* CMultiply::FastSet(int Number, D3DXVECTOR3 Pos)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = log10f(nModScore);
	for (int i = 10; i >= 0; i--)
	{
		if (Fastratio[i] == nullptr)
		{
			Fastratio[i] = CNumber::Create();
		}
		aPosTexU[i] = 0;
		Fastratio[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
	}
	for (int i = nDigits; i >= 0; i--)
	{

		aPosTexU[i] = (nModScore % 10);
   		nModScore /= 10;
	}
	D3DXVECTOR3 ratiopos = Pos;

							// �X�N���[���T�C�Y
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (int nCntScore = 0; nCntScore <= nDigits; nCntScore++)
	{
		
		Fastratio[nCntScore]->SetPos(ratiopos);
		ratiopos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		Fastratio[nCntScore]->SetSize(30);
	
		Fastratio[nCntScore]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		
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
		m_Rate = Rete;
		CMultiply::FastSet(m_Rate, D3DXVECTOR3(100.0f, 200.0f, 0.0f));
	}
	m_RateWait = 6000;
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
	for (int i = 0; i < 10; i++)
	{
		if (ratio[i] != nullptr)
		{
			//ratio[i]->Uninit();
			//delete ratio[i];
			//ratio[i] = nullptr;
		}
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMultiply::Update()
{
 	m_RateWait--; 

	if (m_RateWait <= 0)
	{
		m_RateWait = 20;
		if (m_Rate >= 1)
		{
			m_Rate--;
			CMultiply::FastSet(m_Rate, D3DXVECTOR3(100.0f, 200.0f, 0.0f));
		}
	}
}
