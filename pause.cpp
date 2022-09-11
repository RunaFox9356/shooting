//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "pause.h"
#include "input.h"
#include "manager.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "ranking.h"
#include "manager.h"
//========================
// コンストラクター
//========================
CPause::CPause()
{
}
//========================
// デストラクト
//========================
CPause::~CPause()
{
}

//================
//初期化処理
//================
HRESULT CPause::Init(void)
{
	m_NextMode = MODE_GAME;
	m_OnPause = false;
	//モード選択時の背景黒くするやつ
	m_Bg = CObject2d::Create(2);
	m_Bg->SetTexture(CTexture::TEXTURE_NONE);
	m_Bg->SetSize(CManager::Pos);
	m_Bg->SetPos(CManager::Pos);
	m_Bg->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	//ゲームの文字
	m_object2d[0] = CObject2d::Create(2);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_PAUSEGAME);
	m_object2d[0]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_object2d[0]->SetPos(CManager::Pos);
	m_object2d[0]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));


	float y = 100.0f;

	//チュートリアルの文字
	m_object2d[1] = CObject2d::Create(2);
	m_object2d[1]->SetTexture(CTexture::TEXTURE_PAUSERETURN);
	m_object2d[1]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[1]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	//ランキングの文字
	m_object2d[2] = CObject2d::Create(2);
	m_object2d[2]->SetTexture(CTexture::TEXTURE_PAUSETITLE);
	m_object2d[2]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_object2d[2]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[2]->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================
//破棄
//================
void CPause::Uninit(void)
{
	
}

//==================
//更新処理
//==================
void CPause::Update(void)
{
	
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_PAUSE))
	{
		if (m_OnPause)
		{
			Set();
			m_Bg->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.0f));
			for (int i = 0; i < 3; i++)
			{
				m_object2d[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
			}
		
		}
		else
		{
			m_NextMode = 0;
			Set();
			m_Bg->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.8f));
			for (int i = 0; i < 3; i++)
			{
				m_object2d[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			}
			m_object2d[m_NextMode]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		if (m_OnPause)
		{
			switch (m_NextMode)
			{
			case MODE::MODE_GAME:
				//モードの設定
				CManager::GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_RETURN:
				//モードの設定
				break;
			case MODE::MODE_TITLE:
				//モードの設定
				CManager::GetFade()->NextMode(CManager::MODE_TITLE);
				break;
			default:
				break;
			}
			m_OnPause = false;
		}

		if (m_OnPause)
		{
			m_Bg->SetCollar(PositionVec4(0.0f, 0.0f, 0.0f, 0.5f));
			for (int i = 0; i < 3; i++)
			{
				m_object2d[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			}
			m_object2d[m_NextMode]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_Bg->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
			for (int i = 0; i < 3; i++)
			{

				m_object2d[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
			}

		}

	}
	if (m_OnPause)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			//モード選択
			m_object2d[m_NextMode]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));

			m_NextMode = (MODE)(m_NextMode - 1);


			if (m_NextMode < MODE::MODE_GAME)
			{
				m_NextMode = MODE::MODE_TITLE;
			}



			m_object2d[m_NextMode]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			//モード選択
			m_object2d[m_NextMode]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));

			m_NextMode = (MODE)(m_NextMode + 1);

			if (m_NextMode >= MODE::MODE_END)
			{
				m_NextMode = MODE::MODE_GAME;
			}

			m_object2d[m_NextMode]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#ifdef _DEBUG


#endif // DEBUG
}
//==================
//描画処理
//==================
void CPause::Draw(void)
{

}