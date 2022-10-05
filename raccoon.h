//============================
//
//  �G�l�~�[�ݒ�i���ʂ��j
// Author:hamada ryuuga
//
//============================
#ifndef _CRACCOON_H_
#define _CRACCOON_H_

#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CRaccoon : public CEnemy
{

public:
	CRaccoon();
	~CRaccoon();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	static CRaccoon *CRaccoon::Create();

private:
	int m_counter;
	void CRaccoon::EnemyPattern4();

};
#endif
