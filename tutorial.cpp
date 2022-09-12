//============================
//
// リザルト画面
// Author:hamada ryuuga
//
//============================




//------------------------
// インクルード
//------------------------
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "player.h"
#include "motion.h"
#include "bg.h"
#include "magic.h"
#include "particle_manager.h"
#include "score.h"
#include "life.h"

CMagicBox* CTutorial::m_MagicBox;	
CParticleManager* CTutorial::m_PaticleManager;
CPlayer * CTutorial::m_Player;

//========================
// コンストラクター
//========================
CTutorial::CTutorial()
{
}

//========================
// デストラクト
//========================
CTutorial::~CTutorial()
{
}

//========================
// 初期化処理
//========================
HRESULT CTutorial::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 0.0f;
	m_Magic = 2;

	m_Bg[0] = CBg::Create();
	m_Bg[0]->SetTexture(CTexture::TEXTURE_TUTORIAL);
	m_Bg[0]->SetSize(CManager::Pos);

	m_Bg[0]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_Player = nullptr;
	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);


	m_PaticleManager = new CParticleManager;
	// パーティクル
	if (FAILED(m_PaticleManager->Init()))
	{
		return E_FAIL;
	}

	CScore* pCScore = CScore::Create(D3DXVECTOR3(900.0f, 100.0f, 0.0f));
	pCScore->Set(0);

	CLife*pCLife = CLife::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f));

	m_MagicBox = CMagicBox::Create(D3DXVECTOR3(150.0f, 620.0f, 0.0f));

	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_THUNDER);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_ICE);
	m_MagicBox->CMagicBox::Magicplay(CTexture::TEXTURE_FIRE);

	return S_OK;

}

//========================
// 終了処理
//========================
void CTutorial::Uninit(void)
{
	CManager::GetSound()->Stop();
	
	if (m_Bg[0] != nullptr)
	{
		m_Bg[0]->Uninit();
	}
	

	if (m_MagicBox != nullptr)
	{
		m_MagicBox->Uninit();
		m_MagicBox = nullptr;
	}

	if (m_PaticleManager != nullptr)
	{
		m_PaticleManager->Uninit();
		delete m_PaticleManager;
		m_PaticleManager = nullptr;

	}


	CModelManager::ReleaseAll();
}

//========================
// 更新処理
//========================
void CTutorial::Update(void)
{
	
	m_PaticleManager->Update();

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		//モードの設定
		CManager::GetFade()->NextMode(CManager::MODE_TITLE);
	}

	if (CInputpInput->Trigger(CInput::KEY_RELOAD))
	{
		if (m_PaticleManager->GetEmitter().size() == 0)
		{
			m_MagicBox->CMagicBox::Magicplay((CTexture::TEXTURE)m_Magic);
			m_Magic++; 
			if (m_Magic >= 6)
			{
				m_Magic = 2;
			}
			
		}

	}
#ifdef _DEBUG

	

#endif // DEBUG
}

//========================
// 描画処理
//========================
void CTutorial::Draw(void)
{

}