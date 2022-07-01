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
#define MAX_SIZEMESH (70.0f)
#define MAX_EMESH (20)
//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{

	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 rot;	// ��]���W
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	int xsiz;//�ʐ�
	int zsiz;//�ʐ�
	int X;//�ӂ̒��_��
	int Z;//�ӂ̒��_��
	int nVtx;//���_��
	int Index; //�C���f�b�N�X
	int por;
} EMESH;


class CMesh : public CObject
{
public:
	CMesh();
	~CMesh() override;

	HRESULT Init()override;//������
	void Uninit()override;//�j��
	void Update()override;//�X�V
	void Draw()override;//�`��
	//bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
	//EMESH *Get();
	static CMesh* Create();
	void SetPos(const D3DXVECTOR3 &pos); 
	D3DXVECTOR3 * CMesh::GetPos();
	
};
#endif
