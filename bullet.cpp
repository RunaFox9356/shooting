//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include"crystal.h"
#include "player.h"
#include "hamada.h"
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

	m_VecLengt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dist = 0.0f;
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
	
	if (m_pos.y >SCREEN_HEIGHT)
	{
		CObject::Release();
	}
	if (m_pos.x >SCREEN_WIDTH)
	{
		CObject::Release();
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
				const D3DXVECTOR3 *enemyPos = pObject->GetPos();
				float enemySize = 20.0f;
				float size = 50.0f;

				if (((m_pos.y - size) <= (enemyPos->y + enemySize)) &&
					((m_pos.y + size) >= (enemyPos->y - enemySize)) &&
					((m_pos.x - size) <= (enemyPos->x + enemySize)) &&
					((m_pos.x + size) >= (enemyPos->x - enemySize)))
				{  

					CCrystal::Create(m_pos, D3DXVECTOR3(0.0f, 2.0f, 0.0f));
					// �����蔻��
					pObject->Release();

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

	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);

 	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//���Z����������
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
			pObject->SetCollar(TexVec4(1.0f, 0.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_ICE:
			pObject->SetCollar(TexVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case CPlayer::NOW_STORM:
			pObject->SetCollar(TexVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_SUN:
			pObject->SetCollar(TexVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_NON:
			pObject->SetCollar(TexVec4(1.0f, 1.0f, 1.0f, 0.8f));
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
		
		for (int i = 0; i < MAX_OBJECT; i++)
		{
			CObject*pObject;
			pObject = GetObjectData(i);

			if (pObject != nullptr)
			{
				EObjectType Type = pObject->GetType();
				if (Type == CObject::ENEMY)
				{
					D3DXVECTOR3 vecDist = m_pos - *pObject->GetPos();

					if (m_VecLengt.x <= vecDist.x)
					{
						m_VecLengt = vecDist;
					}
					if (m_VecLengt == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
					{
						m_VecLengt = vecDist;
					}
				}
			}
		}

		m_Dist = D3DXVec3Length(&m_VecLengt);
		if (m_Dist <= 300.0f)
		{
			m_pos += m_VecLengt / m_Dist * 2.0f;
		}
		else
		{
			m_pos += m_move;
		}
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