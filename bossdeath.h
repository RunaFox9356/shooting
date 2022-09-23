//=============================================================================
//
// BOSSDEATH
// Author : �l�c����
//
//=============================================================================


#ifndef _BOSSDEATH_H_			// ���̃}�N����`������ĂȂ�������
#define _BOSSDEATH_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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

