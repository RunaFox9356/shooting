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
		//polygon�̊g��T�C�Y
		static const D3DXVECTOR3 m_Vtx[4];

	public:
		C3dpolygon();
		~C3dpolygon() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void Draw() override;
		void SetTexture(CTexture::TEXTURE texture);
		D3DXVECTOR3 *GetPos()override;

		void SetPos(const D3DXVECTOR3 &pos) override;
		void SetTex(TexVec4 Tex);
	protected:
		int  m_nTimer;
		float m_nScale;
		float m_fSize;
		D3DXVECTOR3 m_pos; //polygon�̈ʒu
		D3DXMATRIX		m_mtxWorld;					// �}�g���b�N�X
	private:
		CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

		LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
};
#endif

