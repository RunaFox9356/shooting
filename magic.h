//=============================================================================
//
// ���@�̃X�g�b�N������
// Author : �l�c����
//
//=============================================================================


#ifndef _MAGIC_H_			// ���̃}�N����`������ĂȂ�������
#define _MAGIC_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"

#define MAXMAGIC (3)

class CMagicBox : public CObject2d
{
public:
	CMagicBox() {}
	~CMagicBox() override {}
	HRESULT Init() override {return S_OK; }
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}
	void Magicplay(CTexture::TEXTURE TEX);
	void MagicRelease(void);
	static CMagicBox* Create(D3DXVECTOR3 pos);

private:
	class CMagic : public CObject2d
	{

	public:
		CMagic();
		~CMagic() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void Draw() override;
		//static void Create(D3DXVECTOR3 pos);
		
		void SelectTex(CTexture::TEXTURE tex);

	private:
		int m_CounterAnim;
		int m_PatternAnim;
		int m_DivisionX;
		int m_DivisionY;
		int m_DivisionMAX;

		CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

	};
	
	CMagic *cMagic[MAXMAGIC];
};
#endif
