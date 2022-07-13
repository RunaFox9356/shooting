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
	m_Mesh.pos = D3DXVECTOR3(-580.0f, 590.0f, 10.0f);
	m_Mesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

													//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/rand.png",
		&m_pTextureEmesh);


	//������
	m_Mesh.xsiz = MAX_EMESH;
	m_Mesh.zsiz = MAX_EMESH;

	//�ӂ̒��_��
	m_Mesh.X = m_Mesh.xsiz + 1;//1��������
	m_Mesh.Z = m_Mesh.zsiz + 1;//1��������

								 //���_��
	m_Mesh.nVtx = m_Mesh.X* m_Mesh.Z;//���_�����g���Ă��

										//�C���f�b�N�X��
	m_Mesh.Index = (2 * m_Mesh.X * m_Mesh.zsiz + 2 * (m_Mesh.zsiz - 1));

	m_Mesh.por = m_Mesh.Index - 2;
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_Mesh.nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_Mesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < m_Mesh.nVtx; i++)
	{
		float posx = ((i % m_Mesh.X) - 1.0f);
		float posz = ((i / m_Mesh.Z) - 1.0f)*-1.0f;

		float texU = 1.0f / m_Mesh.xsiz*(i % m_Mesh.X);
		float texV = 1.0f / m_Mesh.zsiz*(i / m_Mesh.Z);


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
	for (int z = 0; z < m_Mesh.zsiz; z++)
	{
		int linetop = z * (m_Mesh.X * 2 + 2);
		for (int x = 0; x < m_Mesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * m_Mesh.X));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + m_Mesh.X);
		}
		//�k�ރ|���S���ݒ�
		if (z < m_Mesh.xsiz - 1)
		{
			pIdx[m_Mesh.X * 2 + 0 + linetop] = (WORD)(m_Mesh.xsiz + m_Mesh.X*z);
			pIdx[m_Mesh.X * 2 + 1 + linetop] = (WORD)(m_Mesh.X * 2 + m_Mesh.X * z);
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
	////���f���̐؂�ւ�
	//if (GetKeyboardTrigger(DIK_N))
	//{

	//	s_Emesh.zsiz++;
	//	s_Emesh.xsiz++;
	//	SetEmesh(s_Emesh.xsiz, s_Emesh.zsiz);
	//}

	////���f���̐؂�ւ�
	//if (GetKeyboardTrigger(DIK_M) && s_Emesh.xsiz > 1)
	//{
	//	s_Emesh.zsiz--;
	//	s_Emesh.xsiz--;
	//	SetEmesh(s_Emesh.xsiz, s_Emesh.zsiz);
	//}
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
	D3DXMatrixIdentity(&m_Mesh.mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Mesh.rot.y, m_Mesh.rot.x, m_Mesh.rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_Mesh.mtxWorld, &m_Mesh.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_Mesh.pos.x, m_Mesh.pos.y, m_Mesh.pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_Mesh.mtxWorld, &m_Mesh.mtxWorld, &mtxTrans);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Mesh.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(m_pIdxBuff);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureEmesh);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_Mesh.nVtx, 0, m_Mesh.por);

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