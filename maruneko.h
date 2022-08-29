//============================
//
//  �G�l�~�[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _MARUNEKO_H_
#define _MARUNEKO_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CMaru : public CEnemy
{

public:
	CMaru();
	~CMaru();

	HRESULT Init(void)override;	// ������
	void Uninit(void)override;	// �j��
	void Update(void)override;	// �X�V
	void Draw()override;	// �`��
	static CMaru *CMaru::Create();


private:



};
#endif
