//============================
//
// Enemy�ݒ�w�b�^�[
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
		TYPE_MARU,			//
		TYPE_BOSS,			// 
		TYPE_CRAZINESS,			//
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

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	void Collision();	// �����蔻��
	TYPE GetType() { return m_EnemyType; };
	static void  LoadEnemy(const char * pFdata);
	static void  CEnemy::LoadEnemyOnline(const char * pFdata);
	static CEnemy *Create(const int Type);
	static void SetBossCraziness();
	static void SetBoss();

private:
	TYPE m_EnemyType;
	void TitleMove();
	//void Collision(void);	// �����蔻��܂Ƃ�
	void Move(void);		// �ړ�
	void ResetMove();
private:

};
#endif
