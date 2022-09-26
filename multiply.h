//============================
//
// MULTIPLY　H//これは開発初期につくった失敗作
// Author:hamada ryuuga
//
//============================

#ifndef _MULTIPLY_H_
#define _MULTIPLY_H_

#include "object2d.h"


#
class CNumber;
class CMultiplyManager
{
public:

};

//#define MAXRATE (10)
//#define RATE (MAXRATE-1)

class CMultiply : public CObject2d
{
private:
	static const int KETA = 3;

public:
	CMultiply();
	 ~CMultiply();

	 HRESULT Init() override
	 {
		 for (int i = 0; i < KETA; i++)
		 {
			 Fastratio[i] = nullptr;
		 }
		 return S_OK;
	 };
	 void Uninit()override;
	 void Update() override;
	 void Draw() override {};

	void set(int Number, D3DXVECTOR3 Pos, bool extinction);
	static void FastSet(int Number, D3DXVECTOR3 Pos);

	static CMultiply* Create(int Number, D3DXVECTOR3 Pos ,bool extinction);
	static void  SetRate(int Rete) ;
	static int*  GetRate() { return &m_Rate; };

private:


	static int m_Rate;		//倍率
	static int m_RateWait;
	static bool m_Decrease;
	CNumber * ratio[KETA];
	static CNumber * Fastratio[KETA];
};

#endif