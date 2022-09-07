//**************************************************
//
// 制作 ( タイトル )
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

//========================
// コンストラクター
//========================
CTitle::CTitle()
{
}
//========================
// デストラクト
//========================
CTitle::~CTitle()
{
}

//================
//初期化処理
//================
HRESULT CTitle::Init(void)
{
	D3DXVECTOR3 BGPos = CManager::Pos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CManager::Pos;


	BGPos.z = 30.0f;
	m_addX = 0;
	m_addY = 0;

	

	m_Player = nullptr;
	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	EnemyPos.z -= 30.0f;

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

	m_Enemy[1] = CEnemy::Create(1);
	m_Enemy[1]->SetUp(ENEMY);
	m_Enemy[1]->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	m_Enemy[1]->SetPos(EnemyPos);
	m_Enemy[1]->SetSize(D3DXVECTOR3(3.8f, 3.8f, 3.8f));
	m_Enemy[1]->SetLife(10);

	EnemyPos.z -= 30.0f;



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

	m_object3d[0] = CBg::Create();
	m_object3d[0]->SetTexture(CTexture::TEXTURE_TITLEBG);
	m_object3d[0]->SetSize(CManager::Pos);
	m_object3d[0]->SetPos(BGPos);
	m_object3d[0]->SetBgType(CBg::STOP);
	m_object3d[0]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_object3d[1] = CBg::Create();
	m_object3d[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_object3d[1]->SetSize(CManager::Pos*0.8f);
	m_object3d[1]->SetPos(BGPos);
	m_object3d[1]->SetBgType(CBg::STOP);
	m_object3d[1]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.7f));

	m_object2d[0] = CObject2d::Create(2);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLE);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);
	m_object2d[0]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_object2d[1] = CObject2d::Create(2);
	m_object2d[1]->SetTexture(CTexture::TEXTURE_FOXTITLE);
	m_object2d[1]->SetSize(CManager::Pos);
	m_object2d[1]->SetPos(CManager::Pos);
	m_object2d[1]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	CManager::GetSound()->Play(CSound::LABEL_BGM_TITLE);


	return S_OK;
}

//================
//破棄
//================
void CTitle::Uninit(void)
{
	CManager::GetSound()->Stop();
	for (int i = 0; i < 4; i++)
	{
		if (m_object3d[i] !=nullptr)
		{
			m_object3d[i]->Uninit();
			m_object3d[i] = nullptr;
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
//更新処理
//==================
void CTitle::Update(void)
{
	
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
	}
	else
	{
		m_addY--;
		m_addX++;
	}
	D3DXVECTOR3 addPos = D3DXVECTOR3(1.0f + (float)m_addX, 1.0f + (float)m_addY, 0.0f);
	m_object3d[1]->SetSize(CManager::Pos *0.8f + addPos);

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_GAME);
	}
#ifdef _DEBUG


	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
	}


#endif // DEBUG
}
//==================
//描画処理
//==================
void CTitle::Draw(void)
{

}