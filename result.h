//============================
//
// ���U���g��ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _RESULT_H_		//���̃}�N������`����ĂȂ�������
#define _RESULT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

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


};

#endif