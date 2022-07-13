//============================
//
// �J�����ݒ�
// Author:hamada ryuuga
//
//============================
#include "camera.h"
#include "input.h"

#include "manager.h"

//----------------------------
//�R���X�g���N�g
//----------------------------
CCamera::CCamera()
{
}

//----------------------------
//�f�X�g���N�g
//----------------------------
CCamera::~CCamera()
{
}
//----------------------------
//����������
//----------------------------
void CCamera::Init(void)
{
	m_aCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���_�@�����_�@������@�ݒ�
	m_aCamera.posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_aCamera.posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_aCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_aCamera.directionR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aCamera.directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aCamera.bBool = true;

	m_aCamera.fDistance = sqrtf((m_aCamera.posR.x - m_aCamera.posV.x) *
		(m_aCamera.posR.x - m_aCamera.posV.x) +
		(m_aCamera.posR.z - m_aCamera.posV.z) *
		(m_aCamera.posR.z - m_aCamera.posV.z));

	m_aCamera.fDistance = sqrtf((m_aCamera.posR.y - m_aCamera.posV.y)*
		(m_aCamera.posR.y - m_aCamera.posV.y) +
		(m_aCamera.fDistance*m_aCamera.fDistance));

	m_aCamera.rot.x = atan2f((m_aCamera.posR.z - m_aCamera.posV.z),
		(m_aCamera.posR.y - m_aCamera.posV.y));
}

//----------------------------
//�I������
//----------------------------
void CCamera::Uninit(void)
{
}

//----------------------------
//�X�V����
//----------------------------
void CCamera::Update(void)
{
	
}

//----------------------------
//�`�揈��
//----------------------------
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9  pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	//�r���[�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_aCamera.MtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_aCamera.MtxView,
		&m_aCamera.posV,
		&m_aCamera.posR,
		&m_aCamera.vecU);

	//�K�p
	pDevice->SetTransform(D3DTS_VIEW, &m_aCamera.MtxView);

	//�v���W�F�N�V�����}�g���b�N�X��������
	D3DXMatrixIdentity(&m_aCamera.MtxProje);

	////�v���W�F�N�V�����}�g���b�N�X�쐬
	//D3DXMatrixPerspectiveFovLH(&m_aCamera.MtxProje,
	//	D3DXToRadian(90.0f),
	//	(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//	10.0f,
	//	10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
	D3DXMatrixOrthoLH(&m_aCamera.MtxProje,					// �v���W�F�N�V�����}�g���b�N�X
		(float)SCREEN_WIDTH,								// ��
		(float)SCREEN_HEIGHT,								// ����
		10.0f,												// �j�A
		1000.0f);											// �t�@�[

	//�K�p
	pDevice->SetTransform(D3DTS_PROJECTION, &m_aCamera.MtxProje);
}

//----------------------------
//Get
//----------------------------
CCamera::CAMERA * CCamera::Get(void)
{
	return &m_aCamera;
}

//----------------------------
//Get
//----------------------------
D3DXVECTOR3 *CCamera::GetPos()
{
	return &m_aCamera.posV;
}

D3DXMATRIX  *CCamera::GetMtxProje()
{
	return &m_aCamera.MtxProje;
}
D3DXMATRIX *CCamera::GetMtxView()
{
	return &m_aCamera.MtxView;
}