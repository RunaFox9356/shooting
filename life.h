//=============================================================================
//
// BG�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _LIFE_H_			// ���̃}�N����`������ĂȂ�������
#define _LIFE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"
#include "texture.h"

class CLife : public CObject2d
{
private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CLife *CLife::Create(const D3DXVECTOR3 & pos);

	CLife(const int list);
	~CLife() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
	
	void SetDamage(const int Damage);
private:
	CObject2d *m_object2d;
};

#endif

