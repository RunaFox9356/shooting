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
	enum EObjectType
	{
		ENEMY = 0,
		PLAYER,
		BULLET,
		GON,
		MAGIC,
		CRYSTAL,
		MAX,
		NONE
	};

	const static int MAX_OBJECT = 2560;

	CObject();
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual	void SetPos(const D3DXVECTOR3 &pos) = 0;
	virtual void SetMove(const D3DXVECTOR3 &move) = 0;
	virtual const D3DXVECTOR3 *GetPos() const = 0;

	static void AllUpdate();
	static void AllDraw();
	static void AllUninit();
	static void AllCreate();

	int * GetId();
	CObject * GetObjectData(int nCount);
	void SetUp(EObjectType Type, D3DXVECTOR3 pos, D3DXVECTOR3 move);
	
	void Release();
	EObjectType GetType();

protected:
	static CObject *m_pObject[MAX_OBJECT]; 
	int	m_nID;
private:
	//int	m_nID;
	static int m_AllMember;
	EObjectType m_Type;
};
#endif