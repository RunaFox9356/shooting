//============================
//
//  �G�l�~�[�ݒ�i�˂��j�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CStraight : public CEnemy
{

public:
	CStraight();
	~CStraight();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	static CStraight *CStraight::Create();


private:



};
#endif

