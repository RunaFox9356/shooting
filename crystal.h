//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================


#ifndef _CRYSTAL_H_			// ���̃}�N����`������ĂȂ�������
#define _CRYSTAL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"

class  CCrystal : public C3dpolygon
{
public:
	CCrystal();
	~CCrystal() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CCrystal *CCrystal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void SetMove(const D3DXVECTOR3 &move)override;
	void SetType(const int&myType);
	static LPDIRECT3DTEXTURE9 GetTex();

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;
	static int m_AllMember;
	static int m_popType;
	int m_myType;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 Hitpos;
	int m_Hit;
};
#endif

