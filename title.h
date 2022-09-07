//**************************************************
//
// êßçÏ ( É^ÉCÉgÉã )
// Author : hamada ryuuga
//
//**************************************************
#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"
#include "object2d.h"


class CBg;
class CPlayer;
class CEnemy;
class C3dpolygon;
class CTitle :public CObject
{
public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	
private:
	CPlayer * m_Player;
	CEnemy * m_Enemy[10];
	CBg *m_object3d[4];
	C3dpolygon *m_3dpolygon[4];
	CObject2d *m_object2d[4];
	int m_addX;
	int m_addY;
	bool Sizcontroller;
};

#endif