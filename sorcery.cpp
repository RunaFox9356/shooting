//============================
//
// �喂�@�ݒ�
// Author:hamada ryuuga
//
//============================

#include "sorcery.h"
#include "hamada.h"
#include "manager.h"
#include <assert.h>

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CSorcey::CSorcey()
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CSorcey::~CSorcey()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CSorcey::Init()
{
	C3dpolygon::Init();

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CSorcey::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CSorcey::Update()
{
	C3dpolygon::Update();

	//�A�j���[�V�����ݒ�
	m_CounterAnim++;
	if ((m_CounterAnim % 5) == 0)//�����ő��x����
	{
		m_PatternAnimX++;
		if (m_PatternAnimX > m_DivisionX)
		{
			m_PatternAnimX = 0;
			m_PatternAnimY++;
			if (m_PatternAnimY >= m_DivisionY)
			{
				m_PatternAnimY = 0;
				CObject::Release();
				return;
			}
		}
	
		float U = 1.0f  / (m_DivisionX);

		float V = 1.0f  / (m_DivisionY);

		//�\�����W���X�V
		SetTex(PositionVec4(
			U * (m_PatternAnimX)
			, U *(m_PatternAnimX) + U
			, V * (m_PatternAnimY)
			, V * (m_PatternAnimY)+ V));

	}

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::ENEMY)
			{
				
				CObject3d* pObject3d = dynamic_cast<CObject3d*>(pObject);  // �_�E���L���X�g
				const D3DXVECTOR3 *enemyPos = pObject3d->GetPos();
				const D3DXVECTOR3 *pEnemySize = pObject3d->GetSize();
				if (enemyPos->x < 1280.0f - pEnemySize->x)
				{
				float enemySize = 50.0f;
				enemySize *= pEnemySize->y;
				float size = 50.0f;
				
					if (((m_pos.y - m_Size.y) <= (enemyPos->y + enemySize)) &&
						((m_pos.y + m_Size.y) >= (enemyPos->y - enemySize)) &&
						((m_pos.x - m_Size.x) <= (enemyPos->x + pEnemySize->x)) &&
						((m_pos.x + m_Size.x) >= (enemyPos->x - pEnemySize->x)))
					{

						// �����蔻��
						CObject3d* pObject3d = dynamic_cast<CObject3d*>(pObject);  // �_�E���L���X�g
						assert(pObject3d != nullptr);
						CPlayer::NOWMAGIC  NouPlayer = *CPlayer::GetMagic();
						switch (NouPlayer)
						{
						case CPlayer::NOW_FIRE:
							pObject3d->HitLife(10);
							break;
						case CPlayer::NOW_ICE:
							pObject3d->HitLife(1);
							break;
						case CPlayer::NOW_STORM:
							pObject3d->HitLife(1);
							break;
						case CPlayer::NOW_SUN:
							pObject3d->HitLife(1);
							break;
						case CPlayer::NOW_NON:
							pObject3d->HitLife(1);
							break;
						default:
							pObject3d->HitLife(5);
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
// �|���S���̕`��
//=============================================================================
void CSorcey::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create�֐�
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
		pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
		switch (type)
		{
		case CPlayer::NOW_FIRE:	
			pObject->SetAnimation(2, 10);
			pObject->SetTexture(CTexture::TEXTURE_METEO);
			pObject->SetSize(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
			break;
		case CPlayer::NOW_ICE:	
			pObject->SetAnimation(1, 8);
			pObject->SetTexture(CTexture::TEXTURE_ICEAREA);
			pObject->SetSize(D3DXVECTOR3(640.0f, 100.0f, 0.0f));
			break;
		case CPlayer::NOW_STORM:
			pObject->SetAnimation(1, 8);
			pObject->SetTexture(CTexture::TEXTURE_TEMPEST);
			pObject->SetSize(D3DXVECTOR3(640.0f, 300.0f, 0.0f));
			break;
		case CPlayer::NOW_SUN:
			pObject->SetAnimation(5, 5);
			pObject->SetTexture(CTexture::TEXTURE_RAIN);
			pObject->SetSize(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
			pObject->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
			break;
		default:
			break;
		}
	}

	return pObject;
}

//=============================================================================
// Setmove�֐�
//=============================================================================
void CSorcey::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// Animation�̖����ݒ�֐�
//=============================================================================
void CSorcey::SetAnimation(const int U, const int V)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	//�\�����W���X�V
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}