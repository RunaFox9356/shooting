//============================
//
//  �G�l�~�[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CBoss : public CEnemy
{

public:
	CBoss();
	~CBoss();

	HRESULT Init(void)override;	// ������
	void Uninit(void)override;	// �j��
	void Update(void)override;	// �X�V
	void Draw()override;	// �`��
	static CBoss *CBoss::Create();

private:
	void Move();

	int m_keepCount;
	bool m_Stop;
	bool m_Go;
	float m_Speed;

	int m_SamonEnemy;
	D3DXVECTOR3 m_PopPos;
};
#endif