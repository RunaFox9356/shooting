//============================
//
// �X�R�A�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "object.h"

#define	MAX_SCORE	(8)

//�v���g�^�C�v�錾
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
private:

};

CScore::CScore()
{
}

CScore::~CScore()
{
}


#endif 