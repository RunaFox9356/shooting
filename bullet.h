//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================


#ifndef _BULLET_H_			// ���̃}�N����`������ĂȂ�������
#define _BULLET_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"

class  bullet : public CObject2d
{
private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	bullet();
	~bullet() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static bullet *bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void SetMove(D3DXVECTOR3 move);
	static LPDIRECT3DTEXTURE9 Gettex();
	static void Lood();
	static void UnLood();

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXVECTOR3 m_move; //polygon�̈ʒu
};
#endif
