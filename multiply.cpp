//============================
//
// �{��
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"

//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos)
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
		ratio[nCntScore]->SetTex(TexVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
		ratio[nCntScore]->Releasetimer(360);
	}
}

//=============================================================================
// ������\������֐�
//=============================================================================
CMultiply* CMultiply::list(int Number, D3DXVECTOR3 Pos)
{
	CMultiply * pObject = nullptr;
	pObject = new CMultiply;

	if (pObject != nullptr)
	{
		pObject->set(Number, Pos);
	}

	return pObject;
}

CMultiply::CMultiply()
{
}

CMultiply::~CMultiply()
{
}

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
