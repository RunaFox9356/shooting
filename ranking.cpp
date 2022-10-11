//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************
#include <stdio.h>
#include "ranking.h"
#include "main.h"
#include "input.h"
#include "manager.h"
#include "texture.h"
#include "object2d.h"
#include "name.h"
#include "fade.h"

#include "playhave.h"

#include "sound.h"

#include "text.h"


#include "playfab/PlayFabError.h"


bool finished = false;

CScore *CRanking::m_Ranking[MAX_RANK];
int CRanking::m_Score;
std::string  CRanking::m_PlayName;
std::string CRanking::m_Name[5];





//========================
// コンストラクタ
//========================
CRanking::CRanking()
{
}

//========================
// デストラクタ
//========================
CRanking::~CRanking()
{
}

//========================
// 初期化
//========================
inline HRESULT CRanking::Init(void)
{
	for (int i = 0; i < 3; i++)
	{
		m_Name[i] = "";
	}
	D3DXVECTOR3 pos = D3DXVECTOR3(CManager::Pos.x, 100.0f, 0.0f);
	for (int i = 0; i < MAX_RANK - 1; i++)
	{
		m_Ranking[i] = CScore::Create(pos);
		m_Ranking[i]->Set(0);
		pos.y += 100.0f;
	}

	CManager::GetSound()->Play(CSound::LABEL_BGM_RANKING);
	

	

	m_NowPlay = 0;
	m_NemePos = D3DXVECTOR3(30.0f, 100.0f, 0.0f);


	m_Object2d[0] = CObject2d::Create();
	m_Object2d[0]->SetTexture(CTexture::TEXTURE_RANKINBG);
	m_Object2d[0]->SetSize(CManager::Pos);
	m_Object2d[0]->SetPos(CManager::Pos);

	m_Object2d[1] = CObject2d::Create();
	m_Object2d[1]->SetTexture(CTexture::TEXTURE_RANKIN);
	m_Object2d[1]->SetSize(D3DXVECTOR3(100.0f, 300.0f, 0.0f));
	m_Object2d[1]->SetPos(D3DXVECTOR3(CManager::Pos.x - 120.0f, 350.0f, 0.0f));

	m_Object2d[2] = CObject2d::Create();
	m_Object2d[2]->SetTexture(CTexture::TEXTURE_RANKINTITLEOFF);
	m_Object2d[2]->SetSize(D3DXVECTOR3(200.0f, 100.0f, 0.0f));
	m_Object2d[2]->SetPos(D3DXVECTOR3(200.0f, 150.0f, 0.0f));


	finished = false;

	m_RankingSet = false;
	

	m_Ranking[5] = CScore::Create(pos);
	m_Ranking[5]->Set(m_Score);

	//CPlayhave::OnlineSetScore();
	GetScore();
	
	

	return E_NOTIMPL;
}

//========================
//　破棄
//========================
void CRanking::Uninit(void)
{
	CManager::GetSound()->Stop();
	
}

//========================
// 更新
//========================
void CRanking::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (finished)
	{
		m_Object2d[2]->SetTexture(CTexture::TEXTURE_RANKINTITLEON);


		if (!m_RankingSet)
		{
			std::string Name;
			m_RankingSet = true;
			for (int i = 0; i < 3;i++)
			{
				Name += m_Name[i];
				Name += "\n";
			}
			CText::Create(CText::GON, 300, 10, Name.c_str());
		}

		if (CInputpInput->Trigger(CInput::KEY_DECISION))
		{
			//モードの設定
			if (m_Score == 0)
			{
				CManager::GetFade()->NextMode(CManager::MODE_TITLE);
				return;
			}
			else
			{
				CManager::GetFade()->NextMode(CManager::MODE_RESULT);
				return;
			}
		}
	}
}

//========================
// 描画
//========================
void CRanking::Draw()
{
}



void CRanking::GetScore()
{


	CPlayhave::GetScore([](const ClientModels::GetLeaderboardResult& resul) {

		for (auto item : resul.Leaderboard)
		{
			if (item.Position <= 4)
			{
				switch (item.Position)
				{
				case 0:
					m_Name[item.Position] += "いちいは";
					break;
				case 1:
					m_Name[item.Position] += "にいいは";
					break;
				case 2:
					m_Name[item.Position] += "さんいは";
					break;
				case 3:

					break;

				default:
					break;
				}


				m_Name[item.Position] += item.DisplayName;//なまえをキャラに変換
														  // 表示
				m_Ranking[item.Position]->Set(item.StatValue);

			}
		}
		finished = true;
	
	
	});
}




//========================
//ランキングの値をねじ込む
//========================
void CRanking::SetScore(int nScore)
{
	m_Score = nScore;
}


