//=============================================================================
//
// 最後の演出
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "bossdeath.h"
#include "manager.h"
#include "hamada.h"
#include "game.h"
#include "player.h"
#include "score.h"
#include "utility.h"
#include "text.h"
#include "fade.h"
#include "manager.h"
#include "sound.h"

int CDeathManager::m_GetGold;
int CDeathManager::m_MissGold;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CDeath::CDeath() :C3dpolygon(0)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CDeath::~CDeath()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CDeath::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_GOLD);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CDeath::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CDeath::Update()
{
	C3dpolygon::Update();

	m_pos += m_Move;

	// 当たり判定
	CObject**pObject;
	pObject = GetObjectData(0);
	for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
	{
		if (pObject[nObject] != nullptr)
		{
			EObjectType Type = pObject[nObject]->GetType();
			if (Type == CObject::PLAYER)
			{
				CPlayer* cPlayer = CGame::GetPlayer();
				const D3DXVECTOR3 *PlayerPos = cPlayer->GetPos();
				float Size = 50.0f;

				if (((m_pos.y - m_Size.y) <= (PlayerPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (PlayerPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (PlayerPos->x + Size)) &&
					((m_pos.x + m_Size.y) >= (PlayerPos->x - Size)))
				{	//当たり判定
					CManager::GetSound()->Play(CSound::LABEL_SE_GOLD);
					
					GetScore()->Add(500);
					CDeathManager::SetGetGold(CDeathManager::GetGetGold()+1);
					Uninit();
					return;
				}
			}
		}
	}

	m_PatternAnimX++;

	if (m_PatternAnimX > m_DivisionX)
	{//アニメーション
		m_PatternAnimX = 0;
		m_PatternAnimY++;
		if (m_PatternAnimY >= m_DivisionY)
		{
			m_PatternAnimY = 0;
		}
	}

	float U = 1.0f / (m_DivisionX);
	float V = 1.0f / (m_DivisionY);

	SetTex(PositionVec4(
		U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V));

	if (m_pos.y < -SCREEN_HEIGHT)
	{//画面外
		CDeathManager::AddMissGold(1);
		Uninit();
		return;
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CDeath::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	////アルファブレンディングを加算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f));

	C3dpolygon::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create関数
//=============================================================================
CDeath *CDeath::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CDeath * pObject = nullptr;
	pObject = new CDeath;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetMove(move);
		pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
		pObject->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		pObject->SetAnimation(5, 4);
		pObject->SetColar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return pObject;
}

//=============================================================================
// Animationの枚数設定関数
//=============================================================================
void CDeath::SetAnimation(const int U, const int V)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 0;
	m_PatternAnimY = 0;

	//表示座標を更新
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}

//=============================================================================
// コンストラクタ関数
//=============================================================================
CDeathManager::CDeathManager()
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CDeathManager::~CDeathManager()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CDeathManager::Init()
{
	C3dpolygon::Init();
	m_PopTimeCount = 0;
	m_PopCount = 0;
	m_GetGold = 0;
	m_MissGold = 0;
	GoNextMode = false;
	CText::Create(CText::GON, 200, 10, "ボーナスがふってくるのじゃ");
	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CDeathManager::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CDeathManager::Update()
{
	C3dpolygon::Update();

	m_PopTimeCount++;

	if (m_PopTimeCount >= m_PopTime)
	{//ボーナス召喚
		if (m_PopCount <= m_PopMax)
		{
			m_PopCount++;
			m_PopTimeCount = 0;
			float X = FloatRandam(500.0f, -500.0f);
			CDeath::Create(D3DXVECTOR3(X, 640.0f, 0.0f), D3DXVECTOR3(0.0f, -5.0f, 0.0f));
		}
	}
	if (m_MissGold >= m_PopMax)
	{//ボーナスあり
		if (m_GetGold == 0&& GoNextMode == false)
		{
			text = CText::Create(CText::GON, 360, 10, "すべてよけたのか、ならボーナスをあげるのじゃ！\n+50000ポイント");
			GetScore()->Add(50000);
			GoNextMode = true;
			m_TextCount = 0;
		}	
	}
	else if (m_GetGold + m_MissGold >= m_PopMax &&GoNextMode == false)
	{//ボーナスなし
		text = CText::Create(CText::GON, 360, 10, "たくさんゲットしたのじゃ！ないすじゃ！！");
		GoNextMode = true;
		m_TextCount = 0;
	}
	if (m_TextCount == 360 &&GoNextMode == true)
	{//画面遷移
		Uninit();
		CManager::GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}
	if (GoNextMode)
	{//画面遷移までのカウント
		m_TextCount++;
	}

}

//=============================================================================
// create関数
//=============================================================================
CDeathManager * CDeathManager::Create(int MAX, int Pop)
{
	CDeathManager * pObject = nullptr;
	pObject = new CDeathManager;
	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->m_PopTime = Pop;
		pObject->m_PopMax = MAX;
	}
	return pObject;
}
