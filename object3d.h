//=============================================================================
//
// OBJECT3D
// Author : �l�c����
//
//=============================================================================


#ifndef _OBJECT3D_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object.h"
#include "main.h"
#include "motion.h"

class  CMotion;

class CObject3d : public CObject
{
private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

	typedef enum
	{
		ANIME_NORMAL = 0,	// �j���[�g����
		ANIME_RUN,			// ����
		ANIME_ATTACK,		// �U��
		ANIME_JUMP,			// �W�����v
		ANIME_LANDING,		// ���n
		ANIME_MAX
	}ANIME;
public:
	CObject3d();
	~CObject3d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
	void Set(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot,  char *filename);
	D3DXVECTOR3 *GetPos()override;

	protected:
	D3DXVECTOR3		m_move;						// ���[�u
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_rot;						// ��]	
	D3DXVECTOR3		m_rotMove;					// ��]���[�u
private:
	int  m_nTimer;
	float m_nScale;
	float m_fSize;

	LPDIRECT3DTEXTURE9	m_pTexture = NULL;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
	CMotion			*m_pMotion;					// ���[�V����
						// �ʒu
	D3DXVECTOR3		m_posOld;					// �ʒu�ߋ�
	//D3DXVECTOR3		m_move;						// ���[�u

	D3DXVECTOR3		m_modelMin;					// �T�C�Y�ŏ�
	D3DXVECTOR3		m_modelMax;					// �T�C�Y�ő�
	D3DXMATRIX		m_mtxWorld;					// �}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J

	ANIME			m_motionType;					// ���[�V�����^�C�v(����)
	ANIME			m_motionTypeOld;				// ���[�V�����^�C�v(�ߋ�)
	int				m_nMaxModelType;				// ���f���̃^�C�v��
	int				m_nMaxModelParts;				// �������f���p�[�c��
	int				m_nMaxMotion;					// ���[�V������

	int				m_type;						// �^�C�v
	int				m_shadow;					// �e�ԍ�
	int				m_invincible;				// ���G����
	float			m_consumption;				// �v�Z�p

	bool			m_bMotionBlend;				// ���[�V�����u�����h
	bool			m_bMotion;					// ���[�V�������g�p��

	bool			m_isUse;					// �g���Ă邩�g���ĂȂ���
	bool			m_isLoop;					// ���[�v���邩���Ȃ���

	int				m_time;		// �^�C���̍ő吔
	int				m_nparts;	// �p�[�c�̍ő吔
	int				m_pow;		// �W�����v�p���[
	int				m_nMotion;	// ���[�V�����ԍ�
};
#endif
