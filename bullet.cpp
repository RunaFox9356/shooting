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
{

	C3dpolygon::Draw();
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
// Lood�֐�
//=============================================================================
void CBullet::Load()
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
void CBullet::UnLoad()
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
LPDIRECT3DTEXTURE9 CBullet::GetTex()
{
	return m_pTexture;
}