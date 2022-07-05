//============================
//
// �v���C���[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CPlayer : public CObject3d
{
public:
	typedef enum
	{
		ANIME_NORMAL = 0,	// �j���[�g����
		ANIME_RUN,			// ����
		ANIME_ATTACK,		// �U��
		ANIME_JUMP,			// �W�����v
		ANIME_LANDING,		// ���n
		ANIME_MAX
	}ANIME;

	typedef enum
	{
		STATUS_NORMAL = 0,	// �j���[�g����
		STATUS_RUN,			// ����
		STATUS_ATTACK,		// �U��
		STATUS_JUMPUP,		// �W�����v
		STATUS_JUMPDOWN,	// �W�����v
		STATUS_LANDING,		// ���n
		STATUS_MAX
	}STATUS;

	typedef enum
	{
		DAMEGE_NORMAL = 0,	// �j���[�g����
		DAMEGE_NOU,			// �_���[�W������Ă�
		DAMEGE_MAX
	}DAMEGE;

	typedef enum
	{
		COPY_NORMAL = 0,	// �j���[�g����
		COPY_SWORD,			// �\�[�h
		COPY_FIRE,			// �t�@�C�A
		COPY_LASER,			// ���[�U�[
		COPY_CUTTER,		// �J�b�^�[
		COPY_MAX
	}COPY;

	//model�f�[�^�̍\����//
	typedef struct
	{
		int key;		// ���ԊǗ�
		int nowKey;		// ���̃L�[
		int loop;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
		int num_key;  	// �L�[��
		/*MyKeySet KeySet[MAX_KEY];*/
	}MODELDATAPLAYER;

public:
	static const float ATTENUATION;		// �����W��
	static const float SPEED;			// �X�s�[�h
	static const float WIDTH;			// ���f���̔��a
	static const int MAX_PRAYER;		// �ő吔
	static const int MAX_MOVE;			// �A�j���[�V�����̍ő吔
	static const int INVINCIBLE;		// ���G����
	static const int MAX_MODELPARTS = 9;
	static const int MAX_COPY;
	
public:
	CPlayer();
	~CPlayer();

	HRESULT Init(void)override;	// ������
	void Uninit(void)override;	// �j��
	void Update(void)override;	// �X�V
	void Draw()override;	// �`��

	static CPlayer *CPlayer::Create();


private:
	//void Collision(void);	// �����蔻��܂Ƃ�
	void Move(void);		// �ړ�
	int m_Pow;
	float m_MoveSpeed;
private:
	ANIME			m_motionType;					// ���[�V�����^�C�v(����)
	ANIME			m_motionTypeOld;				// ���[�V�����^�C�v(�ߋ�)
};
#endif
