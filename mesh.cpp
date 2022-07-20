//============================
//
// ���b�V���ݒ�(�܂�����)
// Author:hamada ryuuga
//
//============================


#include "mesh.h"
#include "manager.h"


CMesh::CMesh()
{

}
CMesh::~CMesh()
{

}

//=========================================
// ����������
//=========================================
HRESULT CMesh:: Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ����������
	m_pos = D3DXVECTOR3(-580.0f, 590.0f, 10.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

													//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/rand.png",
		&m_pTextureEmesh);


	//������
	m_xsiz = MAX_EMESH;
	m_zsiz = MAX_EMESH;

	//�ӂ̒��_��
	m_X = m_xsiz + 1;//1��������
	m_Z = m_zsiz + 1;//1��������

								 //���_��
	m_nVtx = m_X* m_Z;//���_�����g���Ă��

										//�C���f�b�N�X��
	m_Index = (2 * m_X * m_zsiz + 2 * (m_zsiz - 1));

	m_por = m_Index - 2;
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < m_nVtx; i++)
	{
		float posx = ((i % m_X) - 1.0f);
		float posz = ((i / m_Z) - 1.0f)*-1.0f;

		float texU = 1.0f / m_xsiz*(i % m_X);
		float texV = 1.0f / m_zsiz*(i / m_Z);


		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZEMESH, posz * MAX_SIZEMESH, 0.0f / D3DX_PI);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < m_zsiz; z++)
	{
		int linetop = z * (m_X * 2 + 2);
		for (int x = 0; x < m_X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * m_X));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + m_X);
		}
		//�k�ރ|���S���ݒ�
		if (z < m_xsiz - 1)
		{
			pIdx[m_X * 2 + 0 + linetop] = (WORD)(m_xsiz + m_X*z);
			pIdx[m_X * 2 + 1 + linetop] = (WORD)(m_X * 2 + m_X * z);
		}
	}

	// ���_���W���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=========================================
// �I������
//=========================================
void CMesh::Uninit(void)
{
	// ���_�o�b�t�@�[�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTextureEmesh != NULL)
	{
		m_pTextureEmesh->Release();
		m_pTextureEmesh = NULL;
	}
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=========================================
// �X�V����
//=========================================
void CMesh:: Update(void)
{

}

//=========================================
// �`�揈��
//=========================================
void CMesh::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	
	//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(m_pIdxBuff);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureEmesh);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtx, 0, m_por);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}



//=============================================================================
// GetPos�֐�
//=============================================================================
const D3DXVECTOR3 *CMesh::GetPos() const
{
	return nullptr;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CMesh::SetPos(const D3DXVECTOR3 &pos)
{
	//m_pos = pos;
}
//=============================================================================
// SetPos�֐�
//=============================================================================
void CMesh::SetMove(const D3DXVECTOR3 &move)
{
	//m_pos = pos;
}
//=============================================================================
// Create�֐�
//=============================================================================
CMesh* CMesh::Create()
{
	CMesh * pObject = nullptr;
	pObject = new CMesh;

	if (pObject != nullptr)
	{
		pObject->Init();

	}
	return pObject;
}