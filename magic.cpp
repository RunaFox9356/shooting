//=============================================================================
//
// 魔法のストックするやつ
// Author : 浜田琉雅
//
//=============================================================================

#include "magic.h"

int CMagic::MagicCount = 0;			// 最大数

//=============================================================================
// コンストラクト関数
//=============================================================================
CMagic::CMagic()
{
	m_MagicId = MagicCount;
	MagicCount++;
}

//=============================================================================
// デスストラクト関数
//=============================================================================
CMagic::~CMagic()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CMagic::Init()
{
	CObject2d::Init();

	m_DivisionX = 8;
	m_DivisionY = 1;
	m_DivisionMAX = m_DivisionY*m_DivisionX;
	m_CounterAnim = 0;
	m_PatternAnim = 0;
	//表示座標を更新
	SetTex(TexVec4(
		1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

	//CObject2d::SetTexture(CTexture::TEXTURE_FIRE);

	if (MagicCount >= 4)
	{
		MagicCount = 3;
		CObject::Release();
	}

	return S_OK;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CMagic::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CMagic::Update()
{

	CObject2d::Update();

	if (m_pos.y >SCREEN_HEIGHT)
	{
		CObject::Release();
	}

	//アニメーション設定
	m_CounterAnim++;
	if ((m_CounterAnim % 10) == 0)//ここで速度調整
	{
		m_PatternAnim = (m_PatternAnim + 1) % m_DivisionMAX;

		//表示座標を更新
		SetTex(TexVec4(
			1.0f / m_DivisionX * (m_PatternAnim % (m_DivisionX))
			, 1.0f / m_DivisionX *(m_PatternAnim % (m_DivisionX)) + 1.0f / m_DivisionX
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY))
			, 1.0f / m_DivisionY * (m_PatternAnim / (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));
	}
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (this->m_nID != *pObject->GetId())
			{
				if (Type == CObject::MAGIC)
				{
					const D3DXVECTOR3 *MagicPos = pObject->GetPos();

					float size = 20.0f;

					if (((m_pos.y - size) <= (MagicPos->y + size)) &&
						((m_pos.y + size) >= (MagicPos->y - size)) &&
						((m_pos.x - size) <= (MagicPos->x + size)) &&
						((m_pos.x + size) >= (MagicPos->x - size)))
					{
						m_pos.x += 100.0f;
						return;
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CMagic::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// 生成関数
//=============================================================================
CMagic * CMagic::Create(D3DXVECTOR3 pos)
{
	CMagic * pObject = nullptr;
	pObject = new CMagic;

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->Init();
	}

	return pObject;
}


//=============================================================================
// 生成関数
//=============================================================================
void CMagic::SelectTex(CTexture::TEXTURE tex)
{
	CObject2d::SetTexture(tex);
}

//=============================================================================
// 入れ替え
//=============================================================================
void CMagic::Magicplay()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject*pObject;
		pObject = GetObjectData(i);
		if (pObject != nullptr)
		{
			EObjectType Type = pObject->GetType();
			if (Type == CObject::MAGIC)
			{
				if (this->m_MagicId != *pObject->m_MagicId)
				{

					m_MagicId
				}
			}
		}
	}
}
//=============================================================================
// Get（MagicId）
//=============================================================================
int CMagic::GetMagicId()
{
	return m_MagicId;
}