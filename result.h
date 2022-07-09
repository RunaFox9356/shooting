//============================
//
// リザルト画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _RESULT_H_		//このマクロが定義されてなかったら
#define _RESULT_H_		//2重インクルード防止のマクロ定義

#include "main.h"
#include "object.h"

class CResult :public CObject
{
public:
	CResult();
	~CResult();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos()  const override { return nullptr; };
	void SetPos(const D3DXVECTOR3 &pos) override {};
	void SetMove(const D3DXVECTOR3 &move)override {};

};

#endif