//============================
//
// �Q�[����ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//���̃}�N������`����ĂȂ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

class CGame:public CObject
{
public:
	CGame();
	~CGame();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos()  const override {return nullptr;};
	void SetPos(const D3DXVECTOR3 &pos) override {};
	void SetMove(const D3DXVECTOR3 &move)override {};
};
#endif