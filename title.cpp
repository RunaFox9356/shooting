//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"

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
	return S_OK;
}

//破棄
void CTitle::Uninit(void)
{


	
}
//==================
//更新処理
//==================
void CTitle::Update(void)
{
#ifdef _DEBUG

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_GAME);
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