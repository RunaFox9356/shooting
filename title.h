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
#include "object.h"

class CTitle :public CObject
{
public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos()  const override { return nullptr; };
	void SetPos(const D3DXVECTOR3 &pos) override {};
	void SetMove(const D3DXVECTOR3 &move)override {};
};

#endif