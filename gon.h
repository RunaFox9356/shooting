//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================


#ifndef _GON_H_			// ���̃}�N����`������ĂȂ�������
#define _GON_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"

class  CGon : public CObject2d
{
private:

public:
	CGon();
	~CGon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CGon *CGon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void SetMove(D3DXVECTOR3 move);



private:
	int m_CounterAnim;
	int m_PatternAnim;

	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	D3DXVECTOR3 m_move; //polygon�̈ʒu


};
#endif

