//============================
//
// �G�l�~�[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "words.h"

#include "manager.h"
#
#include "object.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CWords::CWords(int list) :CObject(2)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CWords::~CWords()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CWords::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//- 
	// ���_���̐ݒ�
	//-
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �t�H���g���g����悤�ɂ���
	DESIGNVECTOR design;

	AddFontResourceEx(
		"data/font/FZ�S���^����.otf", //ttf�t�@�C���ւ̃p�X
		FR_PRIVATE,
		&design
	);

	// �t�H���g�̐���
	int fontsize = 38;

	LOGFONT lf = { fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("FZ�S���^����") };

	if (!(m_hFont = CreateFontIndirect(&lf)))
	{
	
	}

	//// �f�o�b�O���\���p�t�H���g�̐���
	//D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 38, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
	//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("FZ�S���^����"), &m_pFont);

	// �f�o�C�X�R���e�L�X�g�擾
	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont);


	
	std::string words = m_words;
	// �����R�[�h�擾
	const char *c = words.c_str();
	UINT code = 0;
#if _UNICODE
	// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
	code = (UINT)*c;
#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	if (IsDBCSLeadByte(*c))
		code = (BYTE)c[0] << 8 | (BYTE)c[1];
	else
		code = c[0];
#endif

	// �t�H���g�r�b�g�}�b�v�擾
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 2, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	DeleteObject(m_hFont);
	ReleaseDC(NULL, hdc);

	// �e�N�X�`���쐬
	if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTex, NULL)))
		if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTex, NULL)))
		{
			return 0;
		}

	// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
		if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, 0)))
		{
			return 0;
		}


	// �t�H���g���̏�������
	// iOfs_x, iOfs_y : �����o���ʒu(����)
	// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
	// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	FillMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight, 0);
	for (y = iOfs_y; y<iOfs_y + iBmp_h; y++)
		for (x = iOfs_x; x<iOfs_x + GM.gmBlackBoxX; x++) {
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w*(y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
			memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4 * x, &Color, sizeof(DWORD));
		}

	m_pTex->UnlockRect(0);

	delete[] ptr;


	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CWords::Uninit(void)
{

	DESIGNVECTOR design;

	RemoveFontResourceEx(
		TEXT("Data/font/FZ�S���^����.otf"), //ttf�t�@�C���ւ̃p�X
		FR_PRIVATE,
		&design
	);

	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();

}

//------------------------------------
// �X�V
//------------------------------------
void CWords::Update(void)
{


	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

					//�}�g���b�N�X�쐬
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_rot.z);
	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);

		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_Size.x);//<-�T�C�Y�ύX
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_Size.y);//<-�T�C�Y�ύX
		pVtx[i].pos.z = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();


	//������move�������

}

//------------------------------------
// �`��
//------------------------------------
void CWords::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;        //�f�o�C�X�ւ̃|�C���^

									  //�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);

	//�|���S���̕`��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);
	//�v���~�e�B�u(�|���S��)��
	pDevice->SetTexture(0, NULL);

}

//------------------------------------
// create
//------------------------------------
CWords *CWords::Create(const char*Text)
{
	CWords * pObject = nullptr;
	pObject = new CWords;

	if (pObject != nullptr)
	{
		pObject->Setwords(Text);
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 100));
		pObject->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
		pObject->Init();
	}
	return pObject;
}



//=============================================================================
// GetPos�֐�
//=============================================================================
const D3DXVECTOR3 * CWords::GetPos() const
{
	return &m_pos;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CWords::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}
//=============================================================================
// SetPos�֐�
//=============================================================================
void CWords::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//===========================================================================
//�Z�b�g�J���[
//=============================================================================
void CWords::SetColar(D3DXCOLOR Collar)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[1].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[2].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[3].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);

	m_col = Collar;
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}