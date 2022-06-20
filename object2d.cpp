//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "object2d.h"
#include "manager.h"
#include "input.h"


 const D3DXVECTOR3 CObject2d::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
};
//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CObject2d::CObject2d()
{

}
//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CObject2d::~CObject2d()
{

}
//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CObject2d::Init()
{
	float fSize = 50.0f;
	m_nScale = 10.0f;

	LPDIRECT3DDEVICE9 pDevice = CManeager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�e�N�X�`��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ken.png",
		&m_pTexture);


	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 50.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CObject2d::Uninit()
{
	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CObject2d::Update()
{
	m_nTimer++;
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

	 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

	//�}�g���b�N�X�쐬
	D3DXMatrixIdentity(&mtx);

	//��]�s���쐬
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 2.0f) / 360.0f) * m_nTimer);

	//�T�C�Y�ύX
	float fSize;
	m_fSize += 0.01f;
	fSize = sinf(m_fSize);

	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);
		pVtx[i].pos = m_pos + addPos[i] * (85.0f *fSize);//<-�T�C�Y�ύX
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CObject2d::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;        //�f�o�C�X�ւ̃|�C���^

	 //�f�o�C�X�̎擾
	pDevice = CManeager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);						//�v���~�e�B�u(�|���S��)��
}

//=============================================================================
// create�֐�
//=============================================================================
CObject2d *CObject2d::Create()
{
	CObject2d * pObject = nullptr;
	pObject = new CObject2d;

	if (pObject != nullptr)
	{
		pObject->Init();
	
	}

	return pObject;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CObject2d::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

