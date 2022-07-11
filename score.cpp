//============================
//
// �X�R�A�ݒ�
// Author:hamada ryuuga
//
//============================
#include "score.h"
#include "game.h"


static LPDIRECT3DTEXTURE9 s_pTextureScore = NULL; //�e�N�X�`���̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffScore = NULL; //���_�o�b�t�@�̐ݒ�
static D3DXVECTOR3 s_posScore; //�X�R�A�̈ʒu
static int s_nScore;

//---------------------------------------
//�Z�b�g�|�X(2d)
//---------------------------------------
void SetNorotpos2d(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW)
{
	pVtx[0].pos = D3DXVECTOR3(XUP, YUP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(XDW, YUP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(XUP, YDW, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(XDW, YDW, 0.0f);
}

//---------------------------------------
//�Z�b�g�e�N�X�`��(2d)
//---------------------------------------
void Settex2d(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}

//===================
//����������
//===================
void InitScore(void)
{

	LPDIRECT3DDEVICE9  pDevice;

	

	s_posScore = D3DXVECTOR3(900.0f, 50.0f, 0.0f);
	
	

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Score001.png",
		&s_pTextureScore);
	
	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//�������_�t�H�[�}�b�g
		&s_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{	
		//���_���W
		SetNorotpos2d(pVtx,
			s_posScore.x - 30,
			s_posScore.x + 30,
			s_posScore.y - 30,
			s_posScore.y + 30);

		s_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

		//RHW�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffScore->Unlock();
}

//===================
//�j������
//===================
void UninitScore(void)
{
		//�e�N�X�`���̔j��
	if (s_pTextureScore != NULL)
	{
		s_pTextureScore->Release();
		s_pTextureScore = NULL;
	}
	
	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffScore != NULL)
	{
		s_pVtxBuffScore->Release();
		s_pVtxBuffScore = NULL;
	}
}

//===================
//�X�V����
//===================
void UpdateScore(void)
{
	

		s_posScore = D3DXVECTOR3(900.0f, 50.0f, 0.0f);
	
	

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//���_���W
		SetNorotpos2d(pVtx,
			s_posScore.x - 30,
			s_posScore.x + 30,
			s_posScore.y - 30,
			s_posScore.y + 30);

		s_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffScore->Unlock();

}

//===================
//�`�揈��
//===================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntScore;

	pDevice = GetDevice();		//���
								//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntScore * 4,
				2);
	}
}

//===================
//�Z�b�g
//===================
void SetScore(int nScore)
{
	int nCntScore;
	int aPosTexU[MAX_SCORE]; //�e���̐������i�[

	s_nScore = nScore;

	int nScore = s_nScore;

	for (int i = 7; i >= 0; i--)
	{
		aPosTexU[i] = (nScore % 10);
		nScore /= 10;
	}
	
	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore]+0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*aPosTexU[nCntScore]+ 0.1f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffScore->Unlock();
}

//===================
//���Z
//===================
void AddScore(int nValue)
{
	int nCntScore;
	int aPosTexU[MAX_SCORE]; //�e���̐������i�[

	s_nScore += nValue;


	SetScore(s_nScore);
}

//===================
//���擾
//===================
int GetScore(void)
{
	return s_nScore;
}

