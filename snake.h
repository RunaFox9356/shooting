//============================
//
//  �G�l�~�[�ݒ�i�w�r�j�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CSnake : public CEnemy
{

public:
	CSnake();
	~CSnake();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	static CSnake *CSnake::Create();
	void OnHit() override;

private:
};

#endif