//=============================================================================
//
// BGオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _LIFE_H_			// このマクロ定義がされてなかったら
#define _LIFE_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"
#include "texture.h"

class CLife : public CObject2d
{
private:
	//polygonの拡大サイズ
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

