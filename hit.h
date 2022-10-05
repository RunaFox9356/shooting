
//=============================================================================
//
// Hit����
// Author : �l�c����
//
//=============================================================================


#ifndef _HIT_H_			// ���̃}�N����`������ĂȂ�������
#define _HIT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"

class CHit : public C3dpolygon
{

public:
	CHit();
	~CHit() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetMove(const D3DXVECTOR3 &move)override { m_move = move; };

	static CHit* Create(D3DXVECTOR3 pos, int Type);

	void SelectTex(CTexture::TEXTURE tex);
	void SetAnimation(const int U, const int V);

	void PlayAnimation();
private:
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
	D3DXVECTOR3 m_move;
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

};

#endif