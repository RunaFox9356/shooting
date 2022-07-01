//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "3dpolygon.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"


const D3DXVECTOR3 C3dpolygon::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
};

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
C3dpolygon::C3dpolygon()
{
	
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
C3dpolygon::~C3dpolygon()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT C3dpolygon::Init()
{

	float fSize = 50.0f;
	m_nScale = 10.0f;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	m_texture = CTexture::TEXTURE_NONE;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�e�N�X�`��
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\ken.png",
	//	&m_pTexture);


	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- 50.0f, + 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ 50.0f, + 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- 50.0f, - 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ 50.0f, - 50.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

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
void C3dpolygon::Uninit()
{
	
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void C3dpolygon::Update()
{
	m_nTimer++;
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

					//�}�g���b�N�X�쐬
	D3DXMatrixIdentity(&mtx);

	//��]�s���쐬
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 2.0f) / 360.0f) * m_nTimer);

	//�T�C�Y�ύX


	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);
		pVtx[i].pos =  +addPos[i] * (45.0f);//<-�T�C�Y�ύX]
		pVtx[i].pos.z = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void C3dpolygon::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;        //�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
									  //�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();
	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);						//�v���~�e�B�u(�|���S��)��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetTexture(0, NULL);


}


//=============================================================================
// GetPos�֐�
//=============================================================================
D3DXVECTOR3 * C3dpolygon::GetPos()
{
	return &m_pos;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void C3dpolygon::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}


//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void C3dpolygon::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//---------------------------------------
//�Z�b�g�e�N�X�`��(2d)
//---------------------------------------
void C3dpolygon::SetTex(TexVec4 Tex)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

