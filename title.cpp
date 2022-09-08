//**************************************************
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "ranking.h"

//========================
// �R���X�g���N�^�[
//========================
CTitle::CTitle()
{
}
//========================
// �f�X�g���N�g
//========================
CTitle::~CTitle()
{
}

//================
//����������
//================
HRESULT CTitle::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CManager::Pos;
	m_alpha = 1.2f;

	
	m_addX = 0;
	m_addY = 0;
	ModeSelect = false;
	NextMode = MODE::MODE_GAME;

	m_Player = nullptr;
	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	EnemyPos.z -= 30.0f;

	//���ʂ�
	m_Enemy[0] = CEnemy::Create(0);
	m_Enemy[0]->SetUp(ENEMY);
	m_Enemy[0]->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	m_Enemy[0]->SetPos(EnemyPos);
	m_Enemy[0]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[0]->SetLife(10);

	EnemyPos.x += 50.0f;
	m_Enemy[4] = CEnemy::Create(0);
	m_Enemy[4]->SetUp(ENEMY);
	m_Enemy[4]->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	m_Enemy[4]->SetPos(EnemyPos);
	m_Enemy[4]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[4]->SetLife(10);

	EnemyPos.x += 50.0f;
	m_Enemy[5] = CEnemy::Create(0);
	m_Enemy[5]->SetUp(ENEMY);
	m_Enemy[5]->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	m_Enemy[5]->SetPos(EnemyPos);
	m_Enemy[5]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[5]->SetLife(10);

	EnemyPos.z -= 30.0f;

	//���O������Ȃ��킢�˂�����
	m_Enemy[1] = CEnemy::Create(1);
	m_Enemy[1]->SetUp(ENEMY);
	m_Enemy[1]->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	m_Enemy[1]->SetPos(EnemyPos);
	m_Enemy[1]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[1]->SetLife(10);

	EnemyPos.z -= 30.0f;

	//���������ɃL���C�w�r
	m_Enemy[2] = CEnemy::Create(2);
	m_Enemy[2]->SetUp(ENEMY);
	m_Enemy[2]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy[2]->SetPos(D3DXVECTOR3(CManager::Pos.x - 70.0f, CManager::Pos.y, 0.0f));
	m_Enemy[2]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[2]->SetLife(10);


	m_Enemy[3] = CEnemy::Create(2);
	m_Enemy[3]->SetUp(ENEMY);
	m_Enemy[3]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy[3]->SetPos(D3DXVECTOR3(-CManager::Pos.x + 70.0f, CManager::Pos.y, 0.0f));
	m_Enemy[3]->SetRot(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	m_Enemy[3]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[3]->SetLife(10);


	//���̔w�i
	m_Bg[0] = CBg::Create();
	m_Bg[0]->SetTexture(CTexture::TEXTURE_STARRY);
	m_Bg[0]->SetSize(CManager::Pos);
	m_Bg[0]->SetPos(BGPos);
	m_Bg[0]->SetBgType(CBg::MOVE);
	m_Bg[0]->SetMove(D3DXVECTOR3(0.0001f, 0.0f, 0.0f));
	m_Bg[0]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	
	//GonFox��TITLE����
	m_Bg[1] = CBg::Create();
	m_Bg[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_Bg[1]->SetSize(CManager::Pos*0.8f);
	m_Bg[1]->SetPos(BGPos);
	m_Bg[1]->SetBgType(CBg::STOP);
	m_Bg[1]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.7f));

	
	//GonFox��TITLE����
	m_object2d[0] = CObject2d::Create(1);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLE);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);
	m_object2d[0]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	
	//�Q�[���X�^�[�g�̕���
	m_object2d[1] = CObject2d::Create(1);
	m_object2d[1]->SetTexture(CTexture::TEXTURE_FOXTITLE);
	m_object2d[1]->SetSize(CManager::Pos);
	m_object2d[1]->SetPos(CManager::Pos);
	m_object2d[1]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));


	//���[�h�I�����̔w�i����������
	m_object2d[2] = CObject2d::Create(2);
	m_object2d[2]->SetTexture(CTexture::TEXTURE_NONE);
	m_object2d[2]->SetSize(CManager::Pos);
	m_object2d[2]->SetPos(CManager::Pos);
	m_object2d[2]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	
	//�Q�[���̕���
	m_object2d[3] = CObject2d::Create(2);
	m_object2d[3]->SetTexture(CTexture::TEXTURE_TITLEGAME);
	m_object2d[3]->SetSize(CManager::Pos);
	m_object2d[3]->SetPos(CManager::Pos);
	m_object2d[3]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));


	float y = 100.0f;

	//�`���[�g���A���̕���
	m_object2d[4] = CObject2d::Create(2);
	m_object2d[4]->SetTexture(CTexture::TEXTURE_TITLETUTORIAL);
	m_object2d[4]->SetSize(CManager::Pos);
	m_object2d[4]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y+y, 0.0f));
	m_object2d[4]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	//�����L���O�̕���
	m_object2d[5] = CObject2d::Create(2);
	m_object2d[5]->SetTexture(CTexture::TEXTURE_TITLERANKIN);
	m_object2d[5]->SetSize(CManager::Pos);
	m_object2d[5]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[5]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	//�����̕���
	m_object2d[6] = CObject2d::Create(2);
	m_object2d[6]->SetTexture(CTexture::TEXTURE_TITLEEND);
	m_object2d[6]->SetSize(CManager::Pos);
	m_object2d[6]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[6]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	CManager::GetSound()->Play(CSound::LABEL_BGM_TITLE);

	CRanking::SetScore(0);

	return S_OK;
}

//================
//�j��
//================
void CTitle::Uninit(void)
{
	CManager::GetSound()->Stop();
	for (int i = 0; i < 4; i++)
	{
		if (m_Bg[i] !=nullptr)
		{
			m_Bg[i]->Uninit();
			m_Bg[i] = nullptr;
		}
	}
	if (m_Player != nullptr)
	{
		m_Player->Uninit();
		m_Player = nullptr;
	}
	CModelManager::ReleaseAll();
}

//==================
//�X�V����
//==================
void CTitle::Update(void)
{
	//���˂�����������������
	if (m_addY <= 10)
	{
		Sizcontroller = true;
	}
	
	if (m_addY >= 50)
	{
		Sizcontroller = false;
	}


	if (Sizcontroller)
	{
		m_addY++;
		m_addX--;
		m_alpha -= 1.0f / 40;

	}
	else
	{
		m_addY--;
		m_addX++;
		m_alpha += 1.0f / 40;
	}

	//���˂�����������������
	D3DXVECTOR3 addPos = D3DXVECTOR3(1.0f + (float)m_addX, 1.0f + (float)m_addY, 0.0f);
	m_Bg[1]->SetSize(CManager::Pos *0.8f + addPos);

	//�_�ł�����
	m_object2d[1]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, m_alpha));

	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
	
		if (ModeSelect)
		{		
			switch (NextMode)
			{
			case MODE::MODE_GAME:
				//���[�h�̐ݒ�
				CManager::GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_TUTORIAL:
				//���[�h�̐ݒ�
				CManager::GetFade()->NextMode(CManager::MODE_TUTORIAL);
				break;
			case MODE::MODE_RANKING:
				//���[�h�̐ݒ�
				CManager::GetFade()->NextMode(CManager::MODE_RANKING);
				break;
			case MODE::MODE_END:
				//�Q�[���̏I��
				exit(0);
				break;
			default:
				break;
			}		
		}
		else
		{
			m_object2d[2]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.5f));

			for (int i = 3; i < 7; i++)
			{
				m_object2d[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			}
			m_object2d[NextMode + 2]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
			ModeSelect = true;
		}

	}
	if (ModeSelect)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			//���[�h�I��
			m_object2d[NextMode + 2]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode - 1);


			if (NextMode <= MODE::MODE_MIN)
			{
				NextMode = MODE::MODE_END;
			}

			

			m_object2d[NextMode + 2]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			//���[�h�I��
			m_object2d[NextMode + 2]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode + 1);

			if (NextMode >= MODE::MODE_MAX)
			{
				NextMode = MODE::MODE_GAME;
			}

			m_object2d[NextMode + 2]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::GetFade()->NextMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//���[�h�̐ݒ�
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
	}

#endif // DEBUG
}
//==================
//�`�揈��
//==================
void CTitle::Draw(void)
{

}