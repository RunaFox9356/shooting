//============================
//
// スコア設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "object.h"

#define	MAX_SCORE	(8)

class CNumber;

//プロトタイプ宣言
class CScore : public CObject
{
public:
	CScore();
	~CScore();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set(int nScore);
	void Add(int nValue);
	int Get();
	static CScore*Create();
	void SetPos(const D3DXVECTOR3 &pos) { m_posScore = pos; };
	const D3DXVECTOR3 *GetPos() const { return &m_posScore; };

private:

	 CNumber* m_pNumber[MAX_SCORE];
	 CNumber * test[MAX_SCORE];
	 int m_nScore;
	 D3DXVECTOR3 m_posScore; //スコアの位置
};




#endif 