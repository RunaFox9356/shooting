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
class CMultiplyManager
{
public:

};


class CMultiply : public CObject
{
public:
	CMultiply();
	 ~CMultiply();
	 HRESULT Init() override {
		 for (int i = 0; i < 10; i++)
		 {
			 Fastratio[i] = nullptr;
		 }
		 return S_OK; };
	 void Uninit()override;
	 void Update() override ;
	 void Draw() override {};


	void set(int Number, D3DXVECTOR3 Pos, bool extinction);
	static CMultiply* FastSet(int Number, D3DXVECTOR3 Pos);

	static CMultiply* list(int Number, D3DXVECTOR3 Pos ,bool extinction);

	static void  SetRate(int Rete) ;
	static int*  GetRate() { return &m_Rate; };

private:


	static int m_Rate;		//”{—¦
	static int m_RateWait;

	CNumber * ratio[10];
	static CNumber * Fastratio[10];
};

#endif