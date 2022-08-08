//=============================================================================
//
// ����
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "crystal.h"
#include "player.h"
#include "hamada.h"
#include "enemy.h"
#include "hit.h"
#include <assert.h>


int CBullet::m_AllMember;
LPDIRECT3DTEXTURE9	CBullet::m_pTexture;

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CBullet::CBullet()
{
	m_AllMember++;
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CBullet::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_BULLET);

	m_VecLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Length = 0.0f;
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CBullet::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CBullet::Update()
{
	C3dpolygon::Update();

	Move();

	if (m_pos.y > SCREEN_HEIGHT)
	{
		CObject::Release();
	}
	if (m_pos.x > SCREEN_WIDTH)
	{
		CObject::Release();
	}
	CObject**pObject;
	pObject = GetObjectData(0);

	for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
	{
		if (pObject[nObject] != nullptr)
		{
			EObjectType Type = pObject[nObject]->GetType();
			if (Type == CObject::ENEMY)
			{
				CObject3d* pObject3d = dynamic_cast<CObject3d*>(pObject[nObject]);  // �_�C�i�~�b�N�L���X�g
				assert(pObject3d != nullptr);
				//�T�C�Y
				const D3DXVECTOR3 *enemyPos = pObject3d->GetPos();
				const D3DXVECTOR3 *pEnemySize = pObject3d->GetSize();

				float enemySize = 30.0f;
				enemySize *= pEnemySize->y;

				//�����蔻��
				if (((m_pos.y - m_Size.y) <= (enemyPos->y + enemySize)) &&
					((m_pos.y + m_Size.y) >= (enemyPos->y - enemySize)) &&
					((m_pos.x - m_Size.x) <= (enemyPos->x + pEnemySize->x)) &&
					((m_pos.x + m_Size.x) >= (enemyPos->x - pEnemySize->x)))
				{
					CPlayer::NOWMAGIC  NouPlayer = *CPlayer::GetMagic();
					CHit::Create(*enemyPos, NouPlayer);
					switch (NouPlayer)
					{
					case CPlayer::NOW_FIRE:
						pObject3d->HitLife(30);
						break;
					case CPlayer::NOW_ICE:
						pObject3d->HitLife(5);
						break;
					case CPlayer::NOW_STORM:
						pObject3d->HitLife(5);
						break;
					case CPlayer::NOW_SUN:
						pObject3d->HitLife(5);
						break;
					case CPlayer::NOW_NON:
						pObject3d->HitLife(5);
						break;
					default:
						pObject3d->HitLife(5);
						break;
					}

					// ���
					CObject::Release();
					return;
				}
			}
		}
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBullet::Draw()
{		//�f�o�C�X�̎擾
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
CBullet *CBullet::Create(D3DXVECTOR3 pos ,D3DXVECTOR3 move)
{
	CBullet * pObject = nullptr;
	pObject = new CBullet;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(pos);
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

		CPlayer::NOWMAGIC  NouPlayer = *CPlayer::GetMagic();
		pObject->SetType((int)NouPlayer);
		//�F�̐ݒ�
		switch (NouPlayer)
		{
		case CPlayer::NOW_FIRE:
			pObject->SetCollar(PositionVec4(1.0f, 0.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_ICE:
			pObject->SetCollar(PositionVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case CPlayer::NOW_STORM:
			pObject->SetCollar(PositionVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_SUN:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_NON:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
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
void CBullet::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// Gettex�֐�
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::GetTex()
{
	return m_pTexture;
}

//=============================================================================
// �����n���֐�
//=============================================================================
void CBullet::Move()
{
	switch ((CPlayer::NOWMAGIC)m_Type)
	{
	case CPlayer::NOW_FIRE:
		m_pos += m_move;
		break;
	case CPlayer::NOW_ICE:
	{
		bool homing = false;

		
			CObject**pObject = nullptr;
			pObject = GetObjectData(0);
			for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
			{
				if (pObject[nObject] != nullptr)
				{
					EObjectType Type = pObject[nObject]->GetType();
					if (Type == CObject::ENEMY)
					{
						/*D3DXVECTOR3 vec = *pObject->GetPos() - m_pos;
						float length = D3DXVec3Length(&vec);

						if (m_Length >= length)
						{
							m_Length = length;
							m_VecLength = vec;
						}*/
						CEnemy* Enemy = dynamic_cast<CEnemy*>(pObject[nObject]);  // �_�E���L���X�g

						D3DXVECTOR3 vecDiff = *Enemy->GetPos() - m_pos;
						float fLength = D3DXVec3Length(&vecDiff);
						m_pos = m_pos + ((vecDiff / fLength) * 10.0f);
						homing = true;
						break;
					}
				}
			}
		

		if (!homing)
		{
			m_pos += m_move;
		}
	}

		/*if (m_Length <= 300.0f)
		{
			m_pos += m_VecLength / m_Length * 2.0f;
		}
		else
		{
			m_pos += m_VecLength / m_Length * 2.0f;
		}*/
		
		break;
	case CPlayer::NOW_STORM:
		m_pos += m_move;
		break;
	case CPlayer::NOW_SUN:
		m_pos += m_move;
		break;
	case CPlayer::NOW_NON:
		m_pos += m_move;
		break;
	default:
		break;
	}



}

void CBullet::SetType(int Type)
{
	m_Type = Type;
}