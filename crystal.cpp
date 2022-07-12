//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "crystal.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "magic.h"
#include "hamada.h"

int CCrystal::m_popType = 2;
LPDIRECT3DTEXTURE9	CCrystal::m_pTexture;

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CCrystal::CCrystal()
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CCrystal::~CCrystal()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CCrystal::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_CRYSTAL);

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CCrystal::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CCrystal::Update()
{
	C3dpolygon::Update();
	m_move.y-=0.1f;
	if (m_move.y <= -5.0f)
	{
		//m_move.y = 5.0f;
	}
	m_pos += m_move;

	if (m_pos.y <-SCREEN_HEIGHT)
	{
		m_move.y = 13.0f;
		//CObject::Release();
	}
	for (int i = 0; i < MAX_OBJECT; i++)
	{	// �����蔻��
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::PLAYER)
			{	// Player�Ƃ̓����蔻��
				const D3DXVECTOR3 *PlayerPos = pObject->GetPos();
				float Size = 50.0f;
				
				if (((m_pos.y - m_Size.y) <= (PlayerPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (PlayerPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (PlayerPos->x + Size)) &&
					((m_pos.x + m_Size.x) >= (PlayerPos->x - Size)))
				{
					CManager::GetMagicBox()->Magicplay((CTexture::TEXTURE)m_myType);
				
					CObject::Release();

					return;
				}
			}
			if (Type == CObject::BULLET)
			{	// ���܂Ƃ̓����蔻��
				const D3DXVECTOR3 *BulletPos = pObject->GetPos();
		
				float Size = 40.0f;

				if (((m_pos.y - m_Size.y) <= (BulletPos->y + Size)) &&
					((m_pos.y + m_Size.y) >= (BulletPos->y - Size)) &&
					((m_pos.x - m_Size.x) <= (BulletPos->x + Size)) &&
					((m_pos.x + m_Size.x) >= (BulletPos->x - Size)))
				{
					//m_move.y += 5.0f;
					return;
				}
			}
		}
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CCrystal::Draw()
{
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
}

//=============================================================================
// create�֐�
//=============================================================================
CCrystal *CCrystal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CCrystal * pObject = nullptr;
	pObject = new CCrystal;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(D3DXVECTOR3 (pos.x, pos.y,0.0f));
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(30.0f,80.0f, 0.0f));	
		
		//�o�Ă���^�C�v�̐ݒ�
		m_popType++;
		
		if (m_popType >= 6)
		{
			m_popType = 2;
		}

		pObject->SetType(m_popType);
		
		//�F�̐ݒ�
		switch (m_popType)
		{
		case 2:
  			pObject->SetCollar(TexVec4(1.0f,0.0f,0.0f,0.8f));
			break;
		case 3:
			pObject->SetCollar(TexVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case 4:
			pObject->SetCollar(TexVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case 5:
			pObject->SetCollar(TexVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		default:
			pObject->SetCollar(TexVec4(1.0f, 1.0f, 1.0f, 0.8f));
			break;
		}
		

	}

	return pObject;
}
//=============================================================================
// Setmove�֐�
//=============================================================================
void CCrystal::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// SetType�֐�
//=============================================================================
void  CCrystal::SetType(const int&myType)
{
	m_myType = myType;
}
//=============================================================================
// Gettex�֐�
//=============================================================================
LPDIRECT3DTEXTURE9 CCrystal::GetTex()
{
	return m_pTexture;
}