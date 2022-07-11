//============================
//
// スコア設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2d.h"



class CNumber : public CObject2d
{
public:
	CNumber();
	~CNumber();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set(int nScore);
	void Add(int nValue);
	int Get();
private:

};

CNumber::CNumber()
{
}

CNumber::~CNumber()
{
}

#endif