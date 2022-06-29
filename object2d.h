//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _OBJECT2D_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object.h"
#include "texture.h"

struct TexVec4
{
	float     P0, P1, P2, P3;
	constexpr TexVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr TexVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }

};

class CObject2d : public CObject
{
private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:

	
	 CObject2d();
	 ~CObject2d() override;
	 HRESULT Init() override;
	 void Uninit() override;
	 void Update() override;
	 void Draw() override;
	 void SetTexture(CTexture::TEXTURE texture);
	static CObject2d *CObject2d::Create();
	D3DXVECTOR3 *GetPos()override;
	 
	 void SetPos(const D3DXVECTOR3 &pos) override;
	 void SetTex(TexVec4 Tex);
protected:
	int  m_nTimer;
	float m_nScale;
	float m_fSize;
	D3DXVECTOR3 m_pos; //polygon�̈ʒu
private:
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
};
#endif
