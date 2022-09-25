//============================
//
// �����Ăރw�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _BELL_H_
#define _BELL_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CBell : public CObject3d
{
public:

	static const int BOUNDPOWER;

	//model�f�[�^�̍\����//
	struct MODELDATAPLAYER
	{
		int key;		// ���ԊǗ�
		int nowKey;		// ���̃L�[
		int loop;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
		int num_key;  	// �L�[��
	};

public:

public:
	CBell();
	~CBell();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	static CBell *CBell::Create();


private:
	//void Collision(void);	// �����蔻��܂Ƃ�
	//void Move(void);		// �ړ�

private:
	bool            m_dist;
	int				m_bound;
	ANIME			m_motionType;					// ���[�V�����^�C�v(����)
	ANIME			m_motionTypeOld;				// ���[�V�����^�C�v(�ߋ�)
};
#endif
