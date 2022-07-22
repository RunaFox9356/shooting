//=============================================================================
//
// オブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"

class CScore;


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
		BG,
		SORCERY,
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


	static void AllUpdate();
	static void AllDraw();
	static void AllUninit();
	static void AllCreate();

	static void TypeDraw(EObjectType Type);

	int * GetId();
	CObject * GetObjectData(int nCount);
	void SetUp(EObjectType Type);

	void Release();
	EObjectType GetType();
	CScore*GetScore();

protected:
	static CObject *m_pObject[MAX_OBJECT]; 
	int	m_nID;
private:
	//int	m_nID;
	static int m_AllMember;
	EObjectType m_Type;


};
#endif