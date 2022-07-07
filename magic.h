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

class  CMagic : public CObject2d
{
private:

public:
	CMagic();
	~CMagic() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CMagic *CMagic::Create(D3DXVECTOR3 pos);
	void SelectTex(CTexture::TEXTURE tex);
	int GetMagicId();
	static int MagicCount;
	void Magicplay();
private:
	int m_CounterAnim;
	int m_PatternAnim;
	int m_MagicId;
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^
};
#endif

