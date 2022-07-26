//=============================================================================
//
// 2Dオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _BG_H_			// このマクロ定義がされてなかったら
#define _BG_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"
#include "texture.h"



class CBg : public CObject2d
{
private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CBg *CBg::Create();

	CBg();
	~CBg() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
};

#endif
