//=============================================================================
//
// ���@�w
// Author : �l�c����
//
//=============================================================================


#ifndef _MAGICCIRCLE_H_			// ���̃}�N����`������ĂȂ�������
#define _MAGICCIRCLE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"

#define MAXMAGICCIRCLE (3)

class  CMagicCircleManager : public C3dpolygon
{
public:
	CMagicCircleManager() {}
	~CMagicCircleManager() override {}
	HRESULT Init() override { return S_OK; }
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}
	void SetMove(const D3DXVECTOR3 &move)override { move; };
	static CMagicCircleManager* Create(D3DXVECTOR3 pos);


	class  CMagicCircle : public C3dpolygon
	{
		enum NOWMAGIC
		{
			NOW_FIRE = 2,		// ��
			NOW_ICE,			// �X
			NOW_STORM,			// ��
			NOW_SUN,			// ��
			NOW_NON,
			NOW_MAX
		};
	public:
		CMagicCircle();
		~CMagicCircle() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void Draw() override;
		static CMagicCircle *CMagicCircle::Create(D3DXVECTOR3 pos);
		void SetMove(const D3DXVECTOR3 &move)override;
		void SetType(const int&myType);
		void SetDefaultSize(const D3DXVECTOR3&Size) { m_DefaultSize = Size; };
		void SetDecreasingRate(const float DecreasingRate) { m_DecreasingRate = DecreasingRate; };
	private:
		static int m_AllMember;
		static int m_popType;
		int m_myType;
		int m_Hit;
		D3DXVECTOR3 m_move;
		D3DXVECTOR3 Hitpos;
		D3DXVECTOR3 m_DefaultSize;
		bool m_isEndAnimation;
		float m_DecreasingRate;
	};

private:
	CMagicCircle *MagicCircle[MAXMAGICCIRCLE];
};
#endif

