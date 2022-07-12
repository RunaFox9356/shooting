//=============================================================================
//
// �֗��֐�
// Author : �l�c����
//
//=============================================================================

#include "hamada.h"

namespace hmd
{
	D3DXMATRIX *giftmtx(D3DXMATRIX *pOut,D3DXVECTOR3 pos, D3DXVECTOR3 rot);
}


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