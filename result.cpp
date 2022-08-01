//============================
//
// リザルト画面
// Author:hamada ryuuga
//
//============================

//------------------------
// インクルード
//------------------------
#include "result.h"
#include "input.h"
#include "manager.h"

//========================
// コンストラクター
//========================
CResult::CResult()
{
}
//========================
// デストラクト
//========================
CResult::~CResult()
{
}

//========================
// リザルトの初期化処理
//========================
HRESULT CResult::Init(void)
{
	return S_OK;
}

//========================
// リザルトの終了処理
//========================
void CResult::Uninit(void)
{
	
}

//========================
// リザルトの更新処理
//========================
void CResult::Update(void)
{

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_TITLE);
	}

}

//========================
// リザルトの描画処理
//========================
void CResult::Draw(void)
{

}