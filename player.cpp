//============================
//
// �v���C���[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "Player.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "motion.h"

//------------------------------------
// static�ϐ�
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// �ړ���
const float CPlayer::WIDTH = 10.0f;			// ���f���̔��a
const int CPlayer::MAX_PRAYER = 16;			// �ő吔
const int CPlayer::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CPlayer::INVINCIBLE = 300;		// ���G����
const int CPlayer::MAX_COPY = 4;			// �ő�R�s�[��

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CPlayer::CPlayer() :
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_modelMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_modelMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	//m_mtxWorld(),
	m_status(STATUS_NORMAL),
	m_damege(DAMEGE_NORMAL),
	m_copy(COPY_NORMAL),
	/*m_parts(),*/
	//m_partsFile(),
	//m_motion(),
	m_motionType(ANIME_NORMAL),
	m_motionTypeOld(ANIME_NORMAL),
	m_nMaxModelType(0),
	m_nMaxModelParts(0),
	m_nMaxMotion(0),
	m_type(0),
	m_shadow(0),
	m_invincible(0),
	m_consumption(0.0f),
	m_bMotionBlend(false),
	m_bMotion(false),
	m_isUse(false),
	m_isLoop(false),
	//m_aFirename(),
	m_time(0),
	m_nparts(0),
	m_pow(0),
	m_nMotion(0)
{
	//memset(&s_Player, NULL, sizeof(s_Player));
	/*memset(&m_motion, 0, sizeof(m_motion));*/

}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------
// ������
//------------------------------------
HRESULT CPlayer::Init(void)
{
	CAMERA *pCamera = GetCamera()->Get();

	//�J�����̃f�[�^�擾
	
	m_rotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI * 0.5f + pCamera->rot.y, 0.0f);

	m_modelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	m_modelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	m_motionTypeOld = m_motionType;

	Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CPlayer::Uninit(void)
{
	m_pMotion->Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CPlayer::Update(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	m_motionTypeOld = m_motionType;

	if (!m_bMotion)
	{// �g�p���Ă郂�[�V�������Ȃ��ꍇ
		m_motionType = ANIME_NORMAL;
		m_isLoop = false;
	}

	Move();	//�����Z�b�g

	Collision();//��

	//�A�j���[�V�����⑫���̐ݒ�
	if (!m_isLoop)
	{
		m_motionType = ANIME_NORMAL;
	}
	
	if (m_motionTypeOld != m_motionType)
	{// ���[�V�����^�C�v���ύX���ꂽ��
		m_pMotion->CntReset((int)(m_motionTypeOld));
		m_bMotionBlend = true;
	}

	if (m_bMotionBlend)
	{// ���[�V�����u�����h���g�p���Ă�
		m_bMotionBlend = m_pMotion->MotionBlend((int)(m_motionType));
	}
	else if (!m_bMotionBlend)
	{// ���[�V�����u�����h���g�p���ĂȂ��ꍇ
		m_bMotion = m_pMotion->PlayMotion((int)(m_motionType));
	}
}

//------------------------------------
// �`��
//------------------------------------
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 marDef;
	D3DXMATERIAL *pMat = {};
	D3DXVECTOR3 scale(1.8f, 1.8f, 1.8f);

	if (m_isUse)//�g���Ă��o��
	{
		// ���[���h�}�g���b�N�X�̏�����
		// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
		D3DXMatrixIdentity(&m_mtxWorld);

		// �g�k�𔽉f
		// �s��g�k�֐�
		D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

		// �����𔽉f
		// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// �p�[�c�̕`��ݒ�
		m_pMotion->SetParts(m_mtxWorld,				// ���[���h�}�g���b�N�X
			mtxRot,									// �v�Z�p�}�g���b�N�X
			mtxTrans,								// �v�Z�p�}�g���b�N�X
			&marDef,								// �}�e���A���ۑ��ϐ�
			pMat);									// �}�e���A���f�[�^

		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		pDevice->SetMaterial(&marDef);
	}
}

//------------------------------------
// �ݒ�
//------------------------------------
void CPlayer::Set(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// �v���C���[���̏�����
	m_pos = pos;											// �ʒu�̏�����
	m_posOld = m_pos;								// �ߋ��ʒu�̏�����
	m_posOld = m_pos;								// �ߋ��ʒu�̏�����
	m_rot = rot;											// �����̏�����
	m_modelMin = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	// ���_���W�̍ŏ��l
	m_modelMax = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);	// ���_���W�̍ő�l
	m_mtxWorld = {};										// ���[���h�}�g���b�N�X
	//m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړI�̌���
	m_motionType = ANIME_NORMAL;							// �j���[�g�������[�V����
	m_motionTypeOld = m_motionType;				// �j���[�g�������[�V����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
	m_bMotionBlend = false;								// ���[�V�����u�����h�̎g�p��
	m_isUse = true;										// �g�p��

	// ���[�V�������
	m_pMotion = new CMotion("Data/system/Gon/Fox.txt");
	assert(m_pMotion != nullptr);
}

//------------------------------------
// �ړ�����
//------------------------------------
void CPlayer::Move(void)
{
	// �ړ��W���̐錾
	int nDash = 1;
	
	CAMERA *pCamera = GetCamera()->Get();

	//�Q�[���̎��̈ړ����@
	m_consumption = 0.0f;

	
	m_posOld = m_pos;//�ߋ��̈ړ��ʂ�ۑ�

	if (m_invincible <= 0)
	{//���G���Ԃ��[���ɂȂ�����_���[�W���炤�悤�ɂ���
		m_damege = DAMEGE_NORMAL;
	}

	//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	m_pos += m_move;	// �ړ������Z

						// ���K��
	if (m_consumption > D3DX_PI)
	{
		m_consumption += D3DX_PI * 2;
	}
	if (m_consumption < -D3DX_PI)
	{
		m_consumption += -D3DX_PI * 2;
	}

	//���Z�ݒ�i�����j
	m_rot.y += m_consumption * ATTENUATION;	//�ړI�̒l-���݂̒l�j�������W��

	//���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//------------------------------------
// �����蔻��
//------------------------------------
void CPlayer::Collision(void)
{
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
	}
}

////------------------------------------
////�R�s�[�����Ƃ����[�V���������[�h���鏈��
////------------------------------------
//void CPlayer::SetCopy(char * pFileName, PartsFile * partsFile, Parts * parts, MyMotion * Motion, int * nMaxParts)
//{
//	// �ϐ��錾
//	char aString[128] = {};			// �������r�p�̕ϐ�
//	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�
//	int	nCntKeySet = 0;				// KeySet�J�E���g
//	int	nCntKey = 0;				// Key�J�E���g
//
//	//-------------------------------
//	//�R�s�[������
//	//-------------------------------
//	if (m_nMaxModelParts >= 7)
//	{
//		m_nMaxModelParts = 7;
//	}
//
//	// �t�@�C���|�C���^�̐錾
//	FILE* pFile = fopen(pFileName, "r");
//
//	if (pFile != NULL)
//	{
//		fscanf(pFile, "%s", &aString);
//
//		while (strncmp(&aString[0], "SCRIPT", 6) != 0)
//		{// �����񂪈�v�����ꍇ
//			aString[0] = {};
//			// ������̓ǂݍ���
//			fscanf(pFile, "%s", &aString[0]);
//		}
//		while (strncmp(&aString[0], "END_SCRIPT", 10) != 0)
//		{
//			fscanf(pFile, "%s", &aString[0]);
//
//			if (strncmp(&aString[0], "#", 1) == 0)
//			{// ���ǂݍ���
//				fgets(&aString[0], sizeof(aString), pFile);
//			}
//
//			if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
//			{// �t�@�C�����̓ǂݍ���
//				fscanf(pFile, "%s", &g_aEqual[0]);
//				fscanf(pFile, "%s", &partsFile->aName[0]);
//			}
//
//			if (strcmp(&aString[0], "CHARACTERSET") == 0)
//			{// �L�����N�^�[�̓ǂݍ���
//				while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
//				{
//					fscanf(pFile, "%s", &aString[0]);
//
//					if (strncmp(&aString[0], "#", 1) == 0)
//					{// ���ǂݍ���
//						fgets(&aString[0], sizeof(aString), pFile);
//					}
//					if (strcmp(&aString[0], "PARTSSET") == 0)
//					{// �p�[�c�̓ǂݍ���
//						while (strcmp(&aString[0], "END_PARTSSET") != 0)
//						{
//							fscanf(pFile, "%s", &aString[0]);
//
//							if (strncmp(&aString[0], "#", 1) == 0)
//							{// ���ǂݍ���
//								fgets(&aString[0], sizeof(aString), pFile);
//							}
//
//							if (strcmp(&aString[0], "INDEX") == 0)
//							{// �^�C�v�̓ǂݍ���
//								fscanf(pFile, "%s", &g_aEqual[0]);
//								fscanf(pFile, "%d", &parts->nType);
//							}
//							if (strcmp(&aString[0], "PARENT") == 0)
//							{// �e�̓ǂݍ���
//								fscanf(pFile, "%s", &g_aEqual[0]);
//								fscanf(pFile, "%d", &parts->nIdxModelParent);
//							}
//							if (strcmp(&aString[0], "POS") == 0)
//							{// �ʒu�̓ǂݍ���
//								fscanf(pFile, "%s", &g_aEqual[0]);
//								fscanf(pFile, "%f", &parts->pos.x);
//								fscanf(pFile, "%f", &parts->pos.y);
//								fscanf(pFile, "%f", &parts->pos.z);
//							}
//							if (strcmp(&aString[0], "ROT") == 0)
//							{// �����̓ǂݍ���
//								fscanf(pFile, "%s", &g_aEqual[0]);
//								fscanf(pFile, "%f", &parts->rot.x);
//								fscanf(pFile, "%f", &parts->rot.y);
//								fscanf(pFile, "%f", &parts->rot.z);
//							}
//						}
//					}
//				}
//			}
//			if (strcmp(&aString[0], "MOTIONSET") == 0)
//			{// ���[�V�����̓ǂݍ���
//				while (strcmp(&aString[0], "END_MOTIONSET") != 0)
//				{
//					fscanf(pFile, "%s", &aString[0]);
//
//					if (strncmp(&aString[0], "#", 1) == 0)
//					{// ���ǂݍ���
//						fgets(&aString[0], sizeof(aString), pFile);
//					}
//
//					if (strcmp(&aString[0], "LOOP") == 0)
//					{// ���[�v�L���̓ǂݍ���
//						fscanf(pFile, "%s", &g_aEqual[0]);
//						fscanf(pFile, "%d", (int*)(&Motion->bLoop));
//					}
//					if (strcmp(&aString[0], "NUM_KEY") == 0)
//					{// �L�[���̓ǂݍ���
//						fscanf(pFile, "%s", &g_aEqual[0]);
//						fscanf(pFile, "%d", &Motion->nNumKey);
//					}
//					if (strcmp(&aString[0], "KEYSET") == 0)
//					{// �L�[�Z�b�g�̓ǂݍ���
//						while (strcmp(&aString[0], "END_KEYSET") != 0)
//						{
//							fscanf(pFile, "%s", &aString[0]);
//
//							if (strncmp(&aString[0], "#", 1) == 0)
//							{// ���ǂݍ���
//								fgets(&aString[0], sizeof(aString), pFile);
//							}
//
//							if (strcmp(&aString[0], "FRAME") == 0)
//							{// �t���[�����̓ǂݍ���
//								fscanf(pFile, "%s", &g_aEqual[0]);
//								fscanf(pFile, "%d", &Motion->keySet[nCntKeySet].nFrame);
//							}
//							if (strcmp(&aString[0], "KEY") == 0)
//							{// �L�[�̓ǂݍ���
//								while (strcmp(&aString[0], "END_KEY") != 0)
//								{
//									fscanf(pFile, "%s", &aString[0]);
//
//									if (strncmp(&aString[0], "#", 1) == 0)
//									{// ���ǂݍ���
//										fgets(&aString[0], sizeof(aString), pFile);
//									}
//
//									if (strcmp(&aString[0], "POS") == 0)
//									{// �ʒu�̓ǂݍ���
//										fscanf(pFile, "%s", &g_aEqual[0]);
//										fscanf(pFile, "%f", &Motion->keySet[nCntKeySet].key[nCntKey].pos.x);
//										fscanf(pFile, "%f", &Motion->keySet[nCntKeySet].key[nCntKey].pos.y);
//										fscanf(pFile, "%f", &Motion->keySet[nCntKeySet].key[nCntKey].pos.z);
//									}
//									if (strcmp(&aString[0], "ROT") == 0)
//									{// �����̓ǂݍ���
//										fscanf(pFile, "%s", &g_aEqual[0]);
//										fscanf(pFile, "%f", &Motion->keySet[nCntKeySet].key[nCntKey].rot.x);
//										fscanf(pFile, "%f", &Motion->keySet[nCntKeySet].key[nCntKey].rot.y);
//										fscanf(pFile, "%f", &Motion->keySet[nCntKeySet].key[nCntKey].rot.z);
//									}
//								}
//
//								// �L�[�J�E���g�̃C���N�������g
//								nCntKey++;
//							}
//						}
//
//						// �L�[�J�E���g�̏�����
//						nCntKey = 0;
//
//						// �L�[�Z�b�g�J�E���g�̃C���N�������g
//						nCntKeySet++;
//					}
//				}
//				// �L�[�Z�b�g�J�E���g�̏�����
//				nCntKeySet = 0;
//
//				// �p�[�c���̃C���N�������g
//				Motion++;
//			}
//
//		}
//
//		//�t�@�C�������
//		fclose(pFile);
//	}
//	else
//	{//�t�@�C�����J���Ȃ��ꍇ
//		printf("\n * * * �t�@�C�����J���܂��� * * * \n");
//	}
//
//	// �ʒu�ƌ����̏����l��ۑ�
//	m_parts[m_nMaxModelParts].posOrigin = m_parts[m_nMaxModelParts].pos;
//	m_parts[m_nMaxModelParts].rotOrigin = m_parts[m_nMaxModelParts].rot;
//
//	// X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX(&m_partsFile[m_parts[m_nMaxModelParts].nType].aName[0],
//		D3DXMESH_SYSTEMMEM,
//		CManeager::GetRenderer()->GetDevice(),
//		NULL,
//		&m_parts[m_nMaxModelParts].pBuffer,
//		NULL,
//		&m_parts[m_nMaxModelParts].nNumMat,
//		&m_parts[m_nMaxModelParts].pMesh);
//
//	m_nMaxModelParts++;
//}

//------------------------------------
// create
//------------------------------------
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;

}

//------------------------------------
// POS�����Z�b�g
//------------------------------------
void CPlayer::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}