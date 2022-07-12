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
	void SetPos(const D3DXVECTOR3 &pos) override {};
	 void SetMove(const D3DXVECTOR3 &move) override {};
	 const D3DXVECTOR3 *GetPos()const override { return nullptr; };

	void set(int Number, int Digits, D3DXVECTOR3 Pos);
	static CMultiply* list(int Number, int Digits, D3DXVECTOR3 Pos);

private:
	CNumber * test[10];
};

#endif