//=============================================================================
//
// BG�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _BOSSDAR_H_			// ���̃}�N����`������ĂȂ�������
#define _BOSSDAR_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"
#include "texture.h"

class CBossbar : public CObject2d
{
private:
	static const int BOSSHP = 3000;
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CBossbar *Create(const D3DXVECTOR3 & pos, float Life);

	CBossbar(const int list);
	~CBossbar() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;

	void SetDamage(const int Damage);


private:
	float m_Life;
	CObject2d *m_object2d[1];

};

#endif
