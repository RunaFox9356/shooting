//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _BG_H_			// ���̃}�N����`������ĂȂ�������
#define _BG_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"
#include "texture.h"



class CBg : public CObject2d
{
private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CBg *CBg::Create();

	CBg();
	~CBg() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
};

#endif
