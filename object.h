//=============================================================================
//
// �I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _OBJECT_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"

class CObject
{

public:
	const static int MAX_OBJECT = 25600;

	CObject();
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual	void SetPos(const D3DXVECTOR3 &pos) = 0;
	//static CObject* Create(const D3DXVECTOR3 &pos);
	static void AllUpdate();
	static void AllDraw();
	static void AllUninit();
	static void AllCreate();
protected:
	static CObject *m_pObject[MAX_OBJECT]; 
	void release();
private:
	int	m_nID;
	static int m_AllMember;
};
#endif