//=============================================================================
//
// オブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

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