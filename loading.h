//**************************************************
//
// êßçÏ ( loading )
// Author : hamada ryuuga
//
//**************************************************

#ifndef _LOADING_H_
#define _LOADING_H_

#include"main.h"
#include "object2d.h"

class  CObject2d;
class  CWords;
class CLoading :public CObject
{


public:
	CLoading();
	~CLoading();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CObject2d *m_object2d[2];
	CWords * m_Words[10]; //NowLoading
	bool m_LoadingEnd;

	int m_timer;
	int m_timerCount = 30;
	int m_moveType;
	int m_Sin;
	
};

#endif
