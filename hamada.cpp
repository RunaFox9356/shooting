//=============================================================================
//
// �֗��֐�
// Author : �l�c����
//
//=============================================================================

#include "hamada.h"

//=============================================================================
//��]�ƈړ��𔽉f�s��
//=============================================================================
D3DXMATRIX *hmd::giftmtx(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// TODO: �֐�������
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(pOut);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.x, rot.y, rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);
	return pOut;
}


//=============================================================================
//�C�[�W���O
//=============================================================================
float hmd::easeInSine(float X)
{
	return 1 - cos((X * D3DX_PI) / 2);
}

float hmd::easeInQuad(float X)
{
	return X * X;
}

//=============================================================================
//1�o�C�g�������V�t�gJIS���ǂ������肷��֐�
//=============================================================================
bool hmd::is_sjis_lead_byte(int c)
{
	return (((c & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}