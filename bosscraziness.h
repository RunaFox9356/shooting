//============================
//
//  �G�l�~�[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _BOSSCRAZINESS_H_
#define _BOSSCRAZINESS_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;
class  CBossbar;

class CBossCraziness : public CEnemy
{

public:
	enum Pattern
	{
		MOVE = 0,
		POP,
		RUSH,
		MAX
	};

	CBossCraziness();
	~CBossCraziness();

	HRESULT Init(void)override;	// ������
	void Uninit(void)override;	// �j��
	void Update(void)override;	// �X�V
	void Draw()override;	// �`��
	void CBossCraziness::OnHit()override;
	static CBossCraziness *CBossCraziness::Create();
private:
	void Move();

	int m_keepCount;
	bool m_Stop;
	bool m_Go;
	float m_Speed;

	int m_SamonEnemy;
	int m_PatternCount;

	int m_Sound;
	D3DXVECTOR3 m_PopPos;
	Pattern m_PatternMode;
	CBossbar *m_Life;
	int m_MaxLife;
	int m_RushCount;
};
#endif
