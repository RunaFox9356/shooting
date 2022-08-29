//============================
//
// �v���C���[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;

class CEnemy : public CObject3d
{
public:
	enum ANIME
	{
		ANIME_NORMAL = 0,	// �j���[�g����
		ANIME_RUN,			// ����
		ANIME_ATTACK,		// �U��
		ANIME_JUMP,			// �W�����v
		ANIME_LANDING,		// ���n
		ANIME_MAX
	};

	enum TYPE
	{
		TYPE_RACCOONL = 0,	//���ʂ�
		TYPE_NEKO,			// �˂�
		TYPE_SNAKE,
		TYPE_MARU,			// �W�����v
		TYPE_BOSS,			// �U��
		TYPE_FOX4,			// ���n
		TYPE_MAX
	};

	

	
	//model�f�[�^�̍\����//
	struct MODELDATAPLAYER
	{
		int key;		// ���ԊǗ�
		int nowKey;		// ���̃L�[
		int loop;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
		int num_key;  	// �L�[��
						/*MyKeySet KeySet[MAX_KEY];*/
	};

public:


public:
	CEnemy();
	~CEnemy();

	HRESULT Init(void)override;	// ������
	void Uninit(void)override;	// �j��
	void Update(void)override;	// �X�V
	void Draw()override;	// �`��
	void Collision();	// �����蔻��
	static void  LoadEnemy(const char * pFdata);
	static CEnemy *Create(const int Type);

	static void SetBoss();
private:
	//void Collision(void);	// �����蔻��܂Ƃ�
	//void Move(void);		// �ړ�

private:

};
#endif
