//============================
//
// スコア設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
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
	CScore*Create();
	void SetPos(const D3DXVECTOR3 &pos) {} ;
	void SetMove(const D3DXVECTOR3 &move) {};
	const D3DXVECTOR3 *GetPos() const {};

private:

	 CNumber* m_pNumber[MAX_SCORE];
	 int m_nScore;
	 D3DXVECTOR3 m_posScore; //スコアの位置
};




#endif 