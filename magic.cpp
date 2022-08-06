//=============================================================================
//
// 魔法のストックするやつ
// Author : 浜田琉雅
//
//=============================================================================

#include "magic.h"
#include "player.h"

//=============================================================================
// コンストラクト関数
//=============================================================================
CMagicBox::CMagic::CMagic(int list):CObject2d(list)
{


}

//=============================================================================
// デスストラクト関数
//=============================================================================
CMagicBox::CMagic::~CMagic()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CMagicBox::CMagic::Init()
{
	CObject2d::Init();

	m_DivisionX = 8;
	m_DivisionY = 1;
	m_DivisionMAX = m_DivisionY*m_DivisionX;
	m_CounterAnim = 0;
	m_PatternAnim = 0;

	//表示座標を更新
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));


	return S_OK;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CMagicBox::CMagic::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CMagicBox::CMagic::Update()
{

	CObject2d::Update();

	//アニメーション設定
	m_CounterAnim++;
	if ((m_CounterAnim % 10) == 0)//ここで速度調整
	{
		m_PatternAnim = (m_PatternAnim + 1) % m_DivisionMAX;

		//表示座標を更新
		SetTex(PositionVec4(
			1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
			, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));
	}
	
}

//=============================================================================
// 描画関数
//=============================================================================
void CMagicBox::CMagic::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// 生成関数
//=============================================================================
CMagicBox* CMagicBox::Create(D3DXVECTOR3 pos)
{

	CMagicBox*object = nullptr;
	object = new CMagicBox;

	object->Init();
	object->SetPos(D3DXVECTOR3(D3DXVECTOR3(pos.x+ 150.0f, pos.y+50.0f, pos.z)));
	object->SetSize(D3DXVECTOR3(250.0f, 20.0f, 0.0f));
	object->SetTexture(CTexture::TEXTURE_BOX);
	for (int i = 0; i < 3; i++)
	{
		object->cMagic[i] = nullptr;
		object->cMagic[i] = new CMagic(1);
		float posX = pos.x + 160 * i;
		if (object->cMagic[i] != nullptr)
		{
			object->cMagic[i]->Init();
			object->cMagic[i]->SetPos(D3DXVECTOR3(posX, pos.y+50.0f, pos.z));
			object->cMagic[i]->SelectTex(CTexture::TEXTURE_NONE);
			object->cMagic[i]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		}
	}
	return object;
}


//=============================================================================
// 生成関数
//=============================================================================
void CMagicBox::CMagic::SelectTex(CTexture::TEXTURE tex)
{
	CObject2d::SetTexture(tex);
}

//=============================================================================
// 入れ替え
//=============================================================================
void CMagicBox::Magicplay(CTexture::TEXTURE TEX)
{
	bool bHave = false;
  	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{
			
			bHave = true;
			cMagic[2]->SelectTex(cMagic[1]->GetTexture());
			cMagic[1]->SelectTex(cMagic[0]->GetTexture());
			cMagic[0]->SelectTex(TEX);
			CPlayer::SetMagic((CPlayer::NOWMAGIC)TEX);
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
			i = 2;
		}
		
	}
	if (!bHave)
	{
		cMagic[2]->SelectTex(cMagic[1]->GetTexture());
		cMagic[1]->SelectTex(cMagic[0]->GetTexture());
		cMagic[0]->SelectTex(TEX);
		CPlayer::SetMagic((CPlayer::NOWMAGIC)TEX);
	}
	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	cMagic[0]->SetPos(D3DXVECTOR3(m_pos.x - 150.0f, m_pos.y - 50.0f, m_pos.z));
	cMagic[0]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
}
//=============================================================================
// はきだし
//=============================================================================
void CMagicBox::MagicRelease(void)
{
	bool bHave = false;
	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{

			bHave = true;
			cMagic[0]->SelectTex(cMagic[1]->GetTexture());
			cMagic[1]->SelectTex(cMagic[2]->GetTexture());
			cMagic[2]->SelectTex(CTexture::TEXTURE_NONE);
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 1.0f));
			CPlayer::SetMagic((CPlayer::NOWMAGIC)cMagic[0]->GetTexture());
			i = 2;
		}

	}
	if (!bHave)
	{
		cMagic[0]->SelectTex(cMagic[1]->GetTexture());
		cMagic[1]->SelectTex(cMagic[2]->GetTexture());
		cMagic[2]->SelectTex(CTexture::TEXTURE_NONE);
		CPlayer::SetMagic((CPlayer::NOWMAGIC)cMagic[0]->GetTexture());

	}
	for (int i = 0; i < 3; i++)
	{
		if (CTexture::TEXTURE_NONE == cMagic[i]->GetTexture())
		{
			cMagic[i]->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	cMagic[0]->SetPos(D3DXVECTOR3(m_pos.x-150.0f, m_pos.y - 50.0f, m_pos.z));
	cMagic[0]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
}