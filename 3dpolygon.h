//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================


#ifndef _3DPOLYGON_H_			// ���̃}�N����`������ĂȂ�������
#define _3DPOLYGON_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "texture.h"
#include "object2d.h"

class  C3dpolygon : public CObject
{
private:
	//polygon�̊�T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	C3dpolygon();
	~C3dpolygon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;

	void SetTexture(CTexture::TEXTURE texture);
	void SetTex(TexVec4 Tex);

protected:
	float m_nScale;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos; //polygon�̈ʒu

	int  m_nTimer; // TODO: ����Ȃ����B
	float m_fSize; // TODO: ����Ȃ����B

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = nullptr;
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^
	D3DXMATRIX m_mtxWorld;					// �}�g���b�N�X
};

#endif
