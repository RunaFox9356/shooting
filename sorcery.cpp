//============================
//
// 大魔法設定
// Author:hamada ryuuga
//
//============================

#include "sorcery.h"
#include "hamada.h"
#include "manager.h"
#include "particle_manager.h"
#include <assert.h>
#include "utility.h"
#include "hit.h"
#include "game.h"
#include "sound.h"
#include "tutorial.h"

//=============================================================================
// コンストラクト関数
//=============================================================================
CSorcey::CSorcey() :C3dpolygon(1)
{
}

//=============================================================================
// デストラクト関数
//=============================================================================
CSorcey::~CSorcey()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CSorcey::Init() 
{
	C3dpolygon::Init();
	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CSorcey::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CSorcey::Update()
{
	//ムーブ
	Move();

	//アニメーション設定
	m_CounterAnim++;
	if ((m_CounterAnim % m_AnimationSpeed) == 0)//ここで速度調整
	{
		PlayAnimation();
	}

	//当たり判定
	Collision();

	C3dpolygon::Update();
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CSorcey::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	C3dpolygon::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create関数
//=============================================================================
CSorcey *CSorcey::Create(D3DXVECTOR3 pos , CPlayer::NOWMAGIC type)
{
	CSorcey * pObject = nullptr;
	pObject = new CSorcey;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetMove(D3DXVECTOR3(15.0f, 0.0f, 0.0f));
		pObject->SetPos(D3DXVECTOR3(pos.x+640.0f, pos.y, 0.0f));
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		pObject->m_NouPlayer = type;
		pObject->SetTexture(CTexture::TEXTURE_NONE);
		switch (type)
		{
		case CPlayer::NOW_FIRE:	
			pObject->SetAnimation(2, 10);
			//pObject->SetTexture(CTexture::TEXTURE_METEO);
			pObject->SetSize(D3DXVECTOR3(640.0f, 300.0f,0.0f));
			pObject->SetSpeed(3);
			CManager::GetSound()->Play(CSound::LABEL_SE_FLARE);
			break;
		case CPlayer::NOW_ICE:	
			pObject->SetAnimation(1, 8);
			pObject->SetTexture(CTexture::TEXTURE_ICEAREA);
			pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
			pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
			CManager::GetSound()->Play(CSound::LABEL_SE_ICE);
			pObject->SetSpeed(10);
			break;
		case CPlayer::NOW_STORM:
			pObject->SetAnimation(1, 8);
			//pObject->SetTexture(CTexture::TEXTURE_TEMPEST);
			pObject->SetSize(D3DXVECTOR3(640.0f, 300.0f, 0.0f));
			CManager::GetSound()->Play(CSound::LABEL_SE_STORM);
			pObject->SetSpeed(5);
			break;
		case CPlayer::NOW_SUN:
			pObject->SetAnimation(5, 5);
			//pObject->SetTexture(CTexture::TEXTURE_RAIN);
			pObject->SetSize(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
			pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
			CManager::GetSound()->Play(CSound::LABEL_SE_SUN);
			pObject->SetSpeed(4);
			break;
		default:
			pObject->SetSpeed(1);
			break;
		}
	}

	return pObject;
}

//=============================================================================
// Setmove関数
//=============================================================================
void CSorcey::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// AnimationのSpeed決める関数
//=============================================================================
void CSorcey::SetSpeed(const int &Speed)
{
	m_AnimationSpeed = Speed;
}

//=============================================================================
// Animationの再生関数
//=============================================================================
void CSorcey::PlayAnimation()
{
	CParticleManager* particleManager = nullptr;
	if (*CManager::GetMode() == CManager::MODE_GAME)
	{
		particleManager = CGame::GetParticleManager();
	}
	else if (*CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		particleManager = CTutorial::GetParticleManager();
	}
	m_PatternAnimX++;

	if (m_PatternAnimX > m_DivisionX)
	{
		if (m_NouPlayer == CPlayer::NOW_ICE&&m_PatternAnimY == 0)
		{
			CSorcey::Create(D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z), CPlayer::NOW_ICE)->SetUp(EObjectType::SORCERY);
		}

		m_PatternAnimX = 0;
		m_PatternAnimY++;
		if (m_PatternAnimY >= m_DivisionY)
		{
			m_PatternAnimY = 0;
			if (particleManager->GetEmitter().size() != 0 && m_NouPlayer != CPlayer::NOW_ICE)
			{
				particleManager->Release(0);
			}
			Uninit();
			return;
		}
	}

	float U = 1.0f / (m_DivisionX);
	float V = 1.0f / (m_DivisionY);

	//表示座標を更新
	SetTex(PositionVec4(
		U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V));
}

//=============================================================================
// Move関数
//=============================================================================
void CSorcey::Move()
{
	D3DXVECTOR3 Imguipos, PlayerPos;

	CParticleManager* particleManager = nullptr;

	CPlayer *Data = nullptr;

	if (*CManager::GetMode() == CManager::MODE_GAME)
	{
		particleManager = CGame::GetParticleManager();
		Data = CGame::GetPlayer();
	}
	else if (*CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		 particleManager = CTutorial::GetParticleManager();
		 Data = CTutorial::GetPlayer();
	}



	if (particleManager->GetEmitter().size() != 0)
	{
		Imguipos = particleManager->GetEmitter()[0]->GetPos();
		PlayerPos = *Data->GetPos();

		D3DXVECTOR3 Pos = ScreenCastWorld(
			&PlayerPos,			// スクリーン座標
			D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));

		PlayerPos.x += 640.0f;
		PlayerPos.z = 100;
		switch (m_NouPlayer)
		{
		case CPlayer::NOW_FIRE:
			m_pos = PlayerPos;
			Imguipos = Pos;
			break;
		case CPlayer::NOW_ICE:
			break;
		case CPlayer::NOW_STORM:
			Imguipos.x += 15.0f;
			PlayerPos.x -= 640.0f;
			break;
		case CPlayer::NOW_SUN:
			PlayerPos.x -= 640.0f;
			break;
		case CPlayer::NOW_NON:
			break;
		default:
			break;
		}

		particleManager->GetEmitter()[0]->SetPos(Imguipos);
	}

	if (m_pos.x > (float)SCREEN_WIDTH)
	{
		Uninit();
		particleManager->Release(0);
		return;
	}
}

//=============================================================================
// Collision関数
//=============================================================================
void CSorcey::Collision()
{

	CObject**pObject;
	pObject = GetObjectData(0);
	for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
	{
		if (pObject[nObject] != nullptr)
		{
			EObjectType Type = pObject[nObject]->GetType();
			if (Type == CObject::ENEMY)
			{
				CObject3d* pObject3d = dynamic_cast<CObject3d*>(pObject[nObject]);  // ダウンキャスト
				assert(pObject3d != nullptr);
				const D3DXVECTOR3 *enemyPos = pObject3d->GetPos();
				const D3DXVECTOR3 *pEnemySize = pObject3d->GetSize();
				if (enemyPos->x < 590.0f - pEnemySize->x)
				{
					float enemySize = 50.0f;
					float enemySizeX = 15.0f;
					enemySize *= pEnemySize->y;
					enemySizeX *= pEnemySize->x;
					if (((m_pos.y - m_Size.y) <= (enemyPos->y + enemySize)) &&
						((m_pos.y + m_Size.y) >= (enemyPos->y - enemySize)) &&
						((m_pos.x - m_Size.x) <= (enemyPos->x + enemySizeX)) &&
						((m_pos.x + m_Size.x) >= (enemyPos->x - enemySizeX)))
					{

						CHit::Create(*enemyPos, m_NouPlayer);
						switch (m_NouPlayer)
						{
						case CPlayer::NOW_FIRE:
							pObject3d->HitLife(5);
							break;
						case CPlayer::NOW_ICE:
							pObject3d->HitLife(5);
							break;
						case CPlayer::NOW_STORM:
							pObject3d->HitLife(15);
							break;
						case CPlayer::NOW_SUN:
							pObject3d->HitLife(3);
							break;
						default:
							break;
						}
						return;
					}
				}
			}
		}
	}

}

//=============================================================================
// Animationの枚数設定関数
//=============================================================================
void CSorcey::SetAnimation(const int U, const int V)
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