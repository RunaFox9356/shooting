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
	static CObject2d *CObject2d::Create();

	CObject2d();
	~CObject2d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	virtual const D3DXVECTOR3 *GetPos() const;
	virtual void SetPos(const D3DXVECTOR3 &pos);
	virtual void SetMove(const D3DXVECTOR3 &move);

	void SetTexture(CTexture::TEXTURE texture);
	void SetTex(TexVec4 Tex);
	CTexture::TEXTURE GetTexture(); 
	void SetCollar(TexVec4 Collar);
	float GetSize() { return m_fSize; };
	void SetSize(float Size) { m_fSize = Size; };
protected:
	int  m_nTimer;
	float m_nScale;
	float m_fSize;
	D3DXVECTOR3 m_pos; //polygon�̈ʒu

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

};

#endif
