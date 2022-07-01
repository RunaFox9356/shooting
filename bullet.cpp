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

	C3dpolygon::SetTexture(CTexture::TEXTURE_KEN);

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
	m_pos += m_move;
	if (m_pos.y >SCREEN_HEIGHT)
	{
		CObject::release();
	}
	if (m_pos.x >SCREEN_WIDTH)
	{
		CObject::release();
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
				//CAMERA *pCamera = GetCamera()->Get();

				//Hitpos = WorldCastScreen(&m_pos,								// �X�N���[�����W
				//	D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),			// �X�N���[���T�C�Y
				//	GetCamera()->GetMtxView(),								// �r���[�}�g���b�N�X
				//	GetCamera()->GetMtxProje());								// �v���W�F�N�V�����}�g���b�N�X

			/*	D3DVECTOR *Object = pObject->GetPos();
				float Sizetest = 100.0f;
				if (Hitpos.x +Sizetest >= Object->x - Sizetest
					&& Hitpos.x - Sizetest <= Object->x + Sizetest
					&& Hitpos.y + Sizetest >= Object->y - Sizetest
					&& Hitpos.y - Sizetest <= Object->y + Sizetest)
				{
					CObject::release();
				}*/
			}
		}
	}


}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBullet::Draw()
{
	C3dpolygon::Draw();
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
	}

	return pObject;
}
//=============================================================================
// Setmove�֐�
//=============================================================================
void CBullet::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// Lood�֐�
//=============================================================================
void CBullet::Lood()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ken.png",
		&m_pTexture);
}

//=============================================================================
// UnLood�֐�
//=============================================================================
void CBullet::UnLood()
{
	// �j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}

//=============================================================================
// Gettex�֐�
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::Gettex()
{
	return m_pTexture;
}