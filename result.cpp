//============================
//
// リザルト画面
// Author:hamada ryuuga
//
//============================




//------------------------
// インクルード
//------------------------
#include "result.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "player.h"
#include "motion.h"
#include "bg.h"

//========================
// コンストラクター
//========================
CResult::CResult()
{
}
//========================
// デストラクト
//========================
CResult::~CResult()
{
}

//========================
// リザルトの初期化処理
//========================
HRESULT CResult::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 Rot(0.0f, 1.57f, 0.0f);

	D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);

	m_Bg[0] = CBg::Create();
	m_Bg[0]->SetTexture(CTexture::TEXTURE_ENDBG);
	m_Bg[0]->SetSize(CManager::Pos);
	m_Bg[0]->SetPos(BGPos);

	m_Bg[1] = CBg::Create();
	m_Bg[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_Bg[1]->SetSize(CManager::Pos*0.8f);
	m_Bg[1]->SetPos(BGPos);


	m_object2d[0] = CObject2d::Create(2);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_CLEAR);
	m_object2d[0]->SetSize(D3DXVECTOR3(500.0f, 200.0f, 0.0f));
	m_object2d[0]->SetPos(CManager::Pos);
	m_object2d[0]->SetMove(D3DXVECTOR3(1.0f, -1.0f, 0.0f));
	CManager::GetSound()->Play(CSound::LABEL_BGM_RESET);

	m_Player = nullptr;
	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);


	m_Enemy[0] = CEnemy::Create(2);
	m_Enemy[0]->SetUp(ENEMY);
	m_Enemy[0]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy[0]->SetPos(D3DXVECTOR3(-CManager::Pos.x + 70.0f, CManager::Pos.y -350.0f, 0.0f));
	m_Enemy[0]->SetRot(Rot);
	m_Enemy[0]->SetSize(Size);
	m_Enemy[0]->SetLife(10);


	m_Enemy[1] = CEnemy::Create(2);
	m_Enemy[1]->SetUp(ENEMY);
	m_Enemy[1]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy[1]->SetPos(D3DXVECTOR3(-CManager::Pos.x - 70.0f, CManager::Pos.y, 0.0f));
	m_Enemy[1]->SetRot(Rot);
	m_Enemy[1]->SetSize(Size);
	m_Enemy[1]->SetLife(10);


	m_Enemy[2] = CEnemy::Create(2);
	m_Enemy[2]->SetUp(ENEMY);
	m_Enemy[2]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy[2]->SetPos(D3DXVECTOR3(CManager::Pos.x - 70.0f, CManager::Pos.y, 0.0f));
	m_Enemy[2]->SetSize(Size);
	m_Enemy[2]->SetLife(10);


	m_Enemy[3] = CEnemy::Create(2);
	m_Enemy[3]->SetUp(ENEMY);
	m_Enemy[3]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Enemy[3]->SetPos(D3DXVECTOR3(CManager::Pos.x + 70.0f, CManager::Pos.y - 350.0f, 0.0f));
	m_Enemy[3]->SetSize(Size);
	m_Enemy[3]->SetLife(10);

	return S_OK;

}

//========================
// リザルトの終了処理
//========================
void CResult::Uninit(void)
{
	CManager::GetSound()->Stop();
	//for (int i = 0; i < 4; i++)
	//{
	//	if (m_Bg[i] != nullptr)
	//	{
	//		m_Bg[i]->Uninit();
	//		
	//	}
	//}
	CModelManager::ReleaseAll();
}

//========================
// リザルトの更新処理
//========================
void CResult::Update(void)
{
	D3DXVECTOR3 DataPos = *m_object2d[0]->GetPos();
	D3DXVECTOR3 DataMove = m_object2d[0]->GetMove();
	D3DXVECTOR3 DataSize = m_object2d[0]->GetSize();

	if (DataPos.x < 0.0f + DataSize.x)
	{
		DataMove.x *= -1.0f;
	}
	if (DataPos.x > 1280.0f - DataSize.x)
	{
		DataMove.x *= -1.0f;
	}

	if (DataPos.y > 0.0f + DataSize.y)
	{
		DataMove.y *= -1.0f;
	}
	if (DataPos.y < 720.0f - DataSize.y)
	{
		DataMove.y *= -1.0f;
	}

	m_object2d[0]->SetPos(DataPos + DataMove);
	m_object2d[0]->SetMove(DataMove);
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_TITLE);
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_TITLE);
	}

#endif // DEBUG
}

//========================
// リザルトの描画処理
//========================
void CResult::Draw(void)
{

}