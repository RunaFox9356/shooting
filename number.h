//============================
//
// NUMBER
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
	static CNumber* Create();
	
	
	void Releasetimer(int nTimar);
private:
	PositionVec4 col;
	int m_DesTimarMax;
	int m_DesTimar;
	bool isRelease;
	
};


#endif