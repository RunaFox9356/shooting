//============================
//
// NUMBER
// Author:hamada ryuuga
//
//============================

#ifndef _MULTIPLY_H_
#define _MULTIPLY_H_

#include "object2d.h"

class CNumber;

class CMultiply : public CObject
{
public:
	CMultiply();
	 ~CMultiply();
	 HRESULT Init() override { return S_OK; };
	 void Uninit()override;
	 void Update() override {};
	 void Draw() override {};


	void set(int Number, D3DXVECTOR3 Pos);
	static CMultiply* list(int Number, D3DXVECTOR3 Pos);

private:
	CNumber * test[10];
};

#endif