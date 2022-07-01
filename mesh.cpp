//============================
//
// ���b�V���ݒ�(�܂�����)
// Author:hamada ryuuga
//
//============================


#include "mesh.h"
#include "manager.h"
#define EMESHMAX (12800)
//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureEmesh = {}; //�e�N�X�`���̃|�C���^
static LPDIRECT3DINDEXBUFFER9 s_pIdxBuff = {};  //�C���f�b�N�X�o�b�t�@
static EMESH s_Emesh;								// �|���S���̍\����



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
	s_Emesh.pos = D3DXVECTOR3(-580.0f, 590.0f, 10.0f);
	s_Emesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

													//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/rand.png",
		&s_pTextureEmesh);


	//������
	s_Emesh.xsiz = MAX_EMESH;
	s_Emesh.zsiz = MAX_EMESH;

	//�ӂ̒��_��
	s_Emesh.X = s_Emesh.xsiz + 1;//1��������
	s_Emesh.Z = s_Emesh.zsiz + 1;//1��������

								 //���_��
	s_Emesh.nVtx = s_Emesh.X* s_Emesh.Z;//���_�����g���Ă��

										//�C���f�b�N�X��
	s_Emesh.Index = (2 * s_Emesh.X * s_Emesh.zsiz + 2 * (s_Emesh.zsiz - 1));

	s_Emesh.por = s_Emesh.Index - 2;
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Emesh.nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Emesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < s_Emesh.nVtx; i++)
	{
		float posx = ((i % s_Emesh.X) - 1.0f);
		float posz = ((i / s_Emesh.Z) - 1.0f)*-1.0f;

		float texU = 1.0f / s_Emesh.xsiz*(i % s_Emesh.X);
		float texV = 1.0f / s_Emesh.zsiz*(i / s_Emesh.Z);


		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZEMESH, posz * MAX_SIZEMESH, 0.0f / D3DX_PI);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Emesh.zsiz; z++)
	{
		int linetop = z * (s_Emesh.X * 2 + 2);
		for (int x = 0; x < s_Emesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * s_Emesh.X));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + s_Emesh.X);
		}
		//�k�ރ|���S���ݒ�
		if (z < s_Emesh.xsiz - 1)
		{
			pIdx[s_Emesh.X * 2 + 0 + linetop] = (WORD)(s_Emesh.xsiz + s_Emesh.X*z);
			pIdx[s_Emesh.X * 2 + 1 + linetop] = (WORD)(s_Emesh.X * 2 + s_Emesh.X * z);
		}
	}

	// ���_���W���A�����b�N
	s_pIdxBuff->Unlock();

	return S_OK;
}

//=========================================
// �I������
//=========================================
void CMesh::Uninit(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureEmesh != NULL)
	{
		s_pTextureEmesh->Release();
		s_pTextureEmesh = NULL;
	}
	if (s_pIdxBuff != NULL)
	{
		s_pIdxBuff->Release();
		s_pIdxBuff = NULL;
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
	D3DXMatrixIdentity(&s_Emesh.mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Emesh.rot.y, s_Emesh.rot.x, s_Emesh.rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&s_Emesh.mtxWorld, &s_Emesh.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, s_Emesh.pos.x, s_Emesh.pos.y, s_Emesh.pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&s_Emesh.mtxWorld, &s_Emesh.mtxWorld, &mtxTrans);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &s_Emesh.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(s_pIdxBuff);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_pTextureEmesh);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, s_Emesh.nVtx, 0, s_Emesh.por);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//
//bool CollisionEmesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
//{
//	VERTEX_3D* pVtx = NULL;
//
//	const int nTri = 3;
//	// ���_���W�����b�N
//	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//�C���f�b�N�X�o�b�t�@�̃��b�N
//	WORD* pIdx;
//	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
//
//	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxWorld;
//
//	// ���[���h�}�g���b�N�X�̏�����
//	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
//	D3DXMatrixIdentity(&mtxWorld);
//
//	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
//	D3DXMatrixTranslation(&mtxTrans, s_Emesh.pos.x, s_Emesh.pos.y, s_Emesh.pos.z);
//	// �s��|���Z�֐�(��2�����~��3�������P�����Ɋi�[)
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
//	bool bIsLanding = false;
//	{
//		for (int nCnt = 0; nCnt < s_Emesh.por; nCnt++)
//		{
//			D3DXVECTOR3 posLineVec[nTri];
//
//			posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
//			posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
//			posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;
//
//			if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
//				(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
//				(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
//			{//�k�ރ|���S�����Ȃ�
//				continue;
//			}
//
//			for (int i = 0; i < nTri; i++)
//			{//�x�N�g���R���W���}�g���b�N�X�ŕϊ�����i��Z�j
//				D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
//			}
//
//			int  LineCout = 0;
//
//			for (int i = 0; i < nTri; i++)
//			{
//				//�x�N�g��S2 V2												
//				D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];
//
//				//�x�N�g�����݂�POS�Ǝn�_�܂ł̋���
//				D3DXVECTOR3 vecPos = *pPos - posLineVec[i];
//
//				//�O�όv�Z//�ӂP
//				float vecLine = Vec2Cross(&vecPos, &vecWall);
//
//				//�O�p�̒��ɓ����Ă�Ƃ��̔���
//				if ((nCnt % 2 == 0 && vecLine > 0.0f) ||
//					(nCnt % 2 != 0 && vecLine < 0.0f))
//				{
//					LineCout++;
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			if (LineCout == nTri)
//			{
//				D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
//				D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];
//
//				D3DXVECTOR3 Normal;
//				//A��B�̖@�������߂���
//				D3DXVec3Cross(&Normal, &V1, &V2);
//
//				//vecB ���m�[�}���C�Y���āA���� 1�ɂ���B
//				D3DXVec3Normalize(&Normal, &Normal);
//
//				D3DXVECTOR3 VecA = *pPos - posLineVec[0];
//				PLAYER *pPrayer = GetPlayer();
//
//				if (pVtx[pIdx[nCnt]].pos.y >= pPos->y)
//				{
//					pPos->y = posLineVec[0].y - (Normal.x*(pPos->x - posLineVec[0].x) + Normal.z*(pPos->z - posLineVec[0].z)) / Normal.y;
//				}
//			}
//		}
//	}
//	// ���_���W���A�����b�N
//	s_pVtxBuff->Unlock();
//	// ���_���W���A�����b�N
//	s_pIdxBuff->Unlock();
//
//	return bIsLanding;
//}
//=============================================================================
// GetPos�֐�
//=============================================================================
D3DXVECTOR3 * CMesh::GetPos()
{
	return NULL;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CMesh::SetPos(const D3DXVECTOR3 &pos)
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