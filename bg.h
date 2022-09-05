//=============================================================================
//
// BGオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _BG_H_			// このマクロ定義がされてなかったら
#define _BG_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CBg : public C3dpolygon
{
private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CBg *CBg::Create();

	CBg(const int list);
	~CBg() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
	static void SetKillMove(const D3DXVECTOR3 & move);
	static D3DXVECTOR3 GetKillMove();
private:

	D3DXVECTOR3 m_Speed;
	D3DXVECTOR3 m_MoveSpeed;
	static D3DXVECTOR3 m_KillSpeed;
	D3DXVECTOR3 m_AddSpeed;
};

#endif
