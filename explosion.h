//=============================================================================
//
// ���@�̃X�g�b�N������
// Author : �l�c����
//
//=============================================================================


#ifndef _EXPLOSION_H_			// ���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"


class CExplosion : public CObject2d
{

public:
	CExplosion();
	~CExplosion() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CExplosion* Create(D3DXVECTOR3 pos);
private:
	void SetAnimation(const int U, const int V);

	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
	int m_AnimationSpeed;
};
#endif