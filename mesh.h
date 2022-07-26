//============================
//
// ���b�V���ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _MESH_H_
#define _MESH_H_

#include "main.h"
#include "object.h"
#define	EMESHX	(1)
#define	EMESHY	(5)
#define MAX_SIZEMESH (100.0f)
#define MAX_EMESH (20)


#define EMESHMAX (12800)

class CMesh : public CObject
{
public:
	CMesh();
	~CMesh() override;

	HRESULT Init()override;//������
	void Uninit()override;//�j��
	void Update()override;//�X�V
	void Draw()override;//�`��



	static CMesh* Create();
	void SetPos(const D3DXVECTOR3 &pos);
	const D3DXVECTOR3 * CMesh::GetPos() const;

private:


	//------------------------------------
	// static�ϐ�
	//------------------------------------
	 LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	    // ���_�o�b�t�@�[�ւ̃|�C���^
	 LPDIRECT3DTEXTURE9 m_pTextureEmesh;        //�e�N�X�`���̃|�C���^
	 LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;         //�C���f�b�N�X�o�b�t�@

	 D3DXVECTOR3 m_pos;	// ���_���W
	 D3DXVECTOR3 m_rot;	// ��]���W
	 D3DXMATRIX m_mtxWorld;// ���[���h�}�g���b�N�X
	 int m_xsiz;//�ʐ�
	 int m_zsiz;//�ʐ�
	 int m_X;//�ӂ̒��_��
	 int m_Z;//�ӂ̒��_��
	 int m_nVtx;//���_��
	 int m_Index; //�C���f�b�N�X
	 int m_por;
	 float m_move;
};
#endif
