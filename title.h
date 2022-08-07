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

class CTitle :public CObject
{
public:


public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	

	CObject2d *m_object2d[4];
	int m_addX;
	int m_addY;
	bool Sizcontroller;
};

#endif