//=============================================================================
//
// ����
// Author : �l�c����
//
//=============================================================================


#ifndef _KITUNE_H_			// ���̃}�N����`������ĂȂ�������
#define _KITUNE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"


class CKitune : public CObject2d
{

public:
	enum PosType
	{
		TYPE_2D = 0,	// ������[��
		TYPE_3D,		// �����Ȃ���[��
		MAX			// ���񂽂����H
	};

	CKitune();
	~CKitune() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CKitune* Create(D3DXVECTOR3 pos, int timer, bool b3D);
private:
	void SetAnimation(const int U, const int V);

	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
	int m_AnimationSpeed;

	int m_Timar;
	int m_TimaCount;
};
#endif
