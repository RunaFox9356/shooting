//=============================================================================
//
// BOSSDEATH
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _BOSSDEATH_H_			// このマクロ定義がされてなかったら
#define _BOSSDEATH_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"

class  CDeath : public C3dpolygon
{

public:
	CDeath();
	~CDeath() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CDeath *CDeath::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
private:

};
#endif

