//=============================================================================
//
// Object
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "gon.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// コンストラクト関数
//=============================================================================
CGon::CGon()
{
	 m_CounterAnim = 0;
	 m_PatternAnim = 0;
	 m_DivisionX = 0;
	 m_DivisionY = 0;
	 m_DivisionMAX = 0;
}

//=============================================================================
// デストラクト関数
//=============================================================================
CGon::~CGon()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CGon::Init()
{
	CObject2d::Init();

	m_DivisionX = 1;
	m_DivisionY = 4;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	//表示座標を更新
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnim / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnim / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

	CObject2d::SetTexture(CTexture::TEXTURE_GON);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CGon::Uninit()
{
	CObject2d::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CGon::Update()
{
	CObject2d::Update();
	m_pos += m_move;
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
		SetTex(PositionVec4(
			  1.0f / m_DivisionX * (m_PatternAnim / (m_DivisionX))
			, 1.0f / m_DivisionX *(m_PatternAnim / (m_DivisionX)) + 1.0f / m_DivisionX
			, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY))
			, 1.0f / m_DivisionY * (m_PatternAnim % (m_DivisionY) + 1.0f / m_DivisionY* m_DivisionY)));
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CGon::Draw()
{
	CObject2d::Draw();
}

//=============================================================================
// create関数
//=============================================================================
CGon *CGon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CGon * pObject = nullptr;
	pObject = new CGon;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(pos);
		pObject->Init();
	}

	return pObject;
}

//=============================================================================
// Setmove関数
//=============================================================================
void CGon::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
