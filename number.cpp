//============================
//
// NUMBER
// Author:hamada ryuuga
//
//============================

#include "number.h"

CNumber::CNumber()
{
}

CNumber::~CNumber()
{
}

HRESULT CNumber::Init()
{
	CObject2d::Init();
	CObject2d::SetTexture(CTexture::TEXTURE_SCORE);
	
	SetTex(TexVec4(
		0.0f, 0.1f, 0.0f, 1.0f));

	return S_OK;
}


void CNumber::Uninit()
{
	CObject2d::Uninit();
}

void CNumber::Update()
{
	CObject2d::Update();
}

void CNumber::Draw()
{
	CObject2d::Draw();
}

CNumber *CNumber::Create()
{
	CNumber * pObject = nullptr;
	pObject = new CNumber;

	if (pObject != nullptr)
	{
		pObject->Init();
	
	}

	return pObject;
}

