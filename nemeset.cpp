//**************************************************
//
// 制作 ( 名まえ )
// Author : hamada ryuuga
//
//**************************************************
#include "nemeset.h"
#include "input.h"
#include "manager.h"
#include "object2d.h"
#include "ranking.h"
std::string  CNemeSet::m_PlayName;

//========================
// コンストラクター
//========================
CNemeSet::CNemeSet()
{
}
//========================
// デストラクト
//========================
CNemeSet::~CNemeSet()
{
}

//================
//初期化処理
//================
HRESULT CNemeSet::Init(void)
{

	m_NowPlay = 0;
	m_NemePos = D3DXVECTOR3(CManager::Pos.x-300.0f, 100.0f, 0.0f);

	m_object2d[0] = CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLEBG);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);


	m_ListName[0] = CName::Create();
	m_ListName[0]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ListName[0]->SetPos(D3DXVECTOR3(CManager::Pos.x -125.0f, 375.0f, 0.0f));
	m_ListName[0]->SetAlphabet(CName::MAX);

	m_ListName[1] = CName::Create();
	m_ListName[1]->SetSize(D3DXVECTOR3(75.0f, 75.0f, 0.0f));
	m_ListName[1]->SetPos(D3DXVECTOR3(CManager::Pos.x, 350.0f, 0.0f));

	m_ListName[2] = CName::Create();
	m_ListName[2]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ListName[2]->SetPos(D3DXVECTOR3(CManager::Pos.x + 125.0f, 375.0f, 0.0f));
	m_ListName[2]->SetAlphabet(CName::B);


	return S_OK;
}

//================
//破棄
//================
void CNemeSet::Uninit(void)
{
}

//==================
//更新処理
//==================
void CNemeSet::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		if (m_PlayNameSet[m_NowPlay] != nullptr)
		{
			m_NowPlay--;
			m_PlayNameSet[m_NowPlay]->Uninit();
			m_PlayNameSet[m_NowPlay]->Release();
			m_NemePos.x -= 60.0f;
		}
	}

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		if (m_NowPlay >= 7)
		{
			//モードの設定
			CRanking::SetPlayNeme(m_PlayName);

			CManager::SetMode(CManager::MODE_RANKING);
			return;
		}

		CNemeSet::RankingNeme();
	}	
}
//==================
//描画処理
//==================
void CNemeSet::Draw(void)
{
}

//========================
//rankingに名まえをねじ込む
//========================
void CNemeSet::RankingNeme()
{
	CName::ALPHABET Type = m_ListName[1]->GetAlphabet();

	switch (Type)
	{
	case CName::A:
		m_PlayName += "A";
		break;
	case CName::B:
		m_PlayName += "B";
		break;
	case CName::C:
		m_PlayName += "C";
		break;
	case CName::D:
		m_PlayName += "D";
		break;
	case CName::E:
		m_PlayName += "E";
		break;
	case CName::F:
		m_PlayName += "F";
		break;
	case CName::G:
		m_PlayName += "G";
		break;
	case CName::H:
		m_PlayName += "H";
		break;
	case CName::I:
		m_PlayName += "I";
		break;
	case CName::J:
		m_PlayName += "J";
		break;
	case CName::K:
		m_PlayName += "K";
		break;
	case CName::L:
		m_PlayName += "L";
		break;
	case CName::M:
		m_PlayName += "M";
		break;
	case CName::N:
		m_PlayName += "N";
		break;
	case CName::O:
		m_PlayName += "O";
		break;
	case CName::P:
		m_PlayName += "P";
		break;
	case CName::Q:
		m_PlayName += "Q";
		break;
	case CName::R:
		m_PlayName += "R";
		break;
	case CName::S:
		m_PlayName += "S";
		break;
	case CName::T:
		m_PlayName += "T";
		break;
	case CName::U:
		m_PlayName += "U";
		break;
	case CName::V:
		m_PlayName += "V";
		break;
	case CName::W:
		m_PlayName += "W";
		break;
	case CName::X:
		m_PlayName += "X";
		break;
	case CName::Y:
		m_PlayName += "Y";
		break;
	case CName::Z:
		m_PlayName += "Z";
		break;
	case CName::MAX:
		//モードの設定
		if (m_PlayName != "")
		{
			CRanking::SetPlayNeme(m_PlayName);

			CManager::SetMode(CManager::MODE_RANKING);
			return;
		}
		else
		{
			return;
		}
		break;
	default:
		return;
		break;
	}

	m_PlayNameSet[m_NowPlay] = CName::Create();
	m_PlayNameSet[m_NowPlay]->SetSize(D3DXVECTOR3(60.0f, 60.0f, 0.0f));
	m_PlayNameSet[m_NowPlay]->SetPos(m_NemePos);
	m_PlayNameSet[m_NowPlay]->SetAlphabet(Type);
	m_PlayNameSet[m_NowPlay]->SetMoveSwitch(false);

	m_NemePos.x += 120.0f;
	m_NowPlay++;
}
