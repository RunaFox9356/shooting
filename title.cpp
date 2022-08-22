//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"
#include "object2d.h"

//========================
// コンストラクター
//========================
CTitle::CTitle()
{
}
//========================
// デストラクト
//========================
CTitle::~CTitle()
{
}

//================
//初期化処理
//================
HRESULT CTitle::Init(void)
{

	m_addX = 0;
	m_addY = 0;
	m_object2d[0]=CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLEBG);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);

	m_object2d[1] = CObject2d::Create();
	m_object2d[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_object2d[1]->SetSize(CManager::Pos*0.8f);
	m_object2d[1]->SetPos(CManager::Pos);

	m_object2d[2] = CObject2d::Create();
	m_object2d[2]->SetTexture(CTexture::TEXTURE_TITLE);
	m_object2d[2]->SetSize(CManager::Pos);
	m_object2d[2]->SetPos(CManager::Pos);


	m_object2d[3] = CObject2d::Create();
	m_object2d[3]->SetTexture(CTexture::TEXTURE_FOXTITLE);
	m_object2d[3]->SetSize(CManager::Pos);
	m_object2d[3]->SetPos(CManager::Pos);

	return S_OK;
}

//================
//破棄
//================
void CTitle::Uninit(void)
{	
	for (int i = 0; i < 4; i++)
	{
		if (m_object2d[i] !=nullptr)
		{
			m_object2d[i]->Uninit();
			m_object2d[i]->Release();
		}
	}
}

//==================
//更新処理
//==================
void CTitle::Update(void)
{

	if (m_addY <= 10)
	{
		Sizcontroller = true;
	}
	
	if (m_addY >= 50)
	{
		Sizcontroller = false;
	}

	if (Sizcontroller)
	{
		m_addY++;
		m_addX--;
	}
	else
	{
		m_addY--;
		m_addX++;
	}
	D3DXVECTOR3 addPos = D3DXVECTOR3(1.0f + (float)m_addX, 1.0f + (float)m_addY, 0.0f);
	m_object2d[1]->SetSize(CManager::Pos *0.8f + addPos);

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_GAME);
	}
#ifdef _DEBUG


	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_NAMESET);
	}
	/*if (GetKeyboardPress(DIK_0))
	{
		SetFade(MODE_RESULT);
	}
	if (GetKeyboardPress(DIK_9))
	{
		SetFade(MODE_GAME);
	}*/

#endif // DEBUG
}
//==================
//描画処理
//==================
void CTitle::Draw(void)
{

}