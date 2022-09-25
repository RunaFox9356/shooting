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
class  CBossbar;

class CBoss : public CEnemy
{

public:
	enum Pattern
	{
		MOVE = 0,
		POP,
		RUSH,
		MAX
	};

	CBoss();
	~CBoss();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	void CBoss::OnHit()override;
	static CBoss *CBoss::Create();
private:
	void Move();

	int m_keepCount;
	bool m_Stop;
	bool m_Go;
	float m_Speed;

	int m_SamonEnemy;
	int m_PatternCount;
	D3DXVECTOR3 m_PopPos;
	Pattern m_PatternMode;
	CBossbar *m_Life;
	int m_MaxLife;
	int m_Sound;
};
#endif