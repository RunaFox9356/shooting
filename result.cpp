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

	m_addX = 0;
	m_addY = 0;
	m_object2d[0] = CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_ENDBG);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);

	m_object2d[1] = CObject2d::Create();
	m_object2d[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_object2d[1]->SetSize(CManager::Pos*0.8f);
	m_object2d[1]->SetPos(CManager::Pos);


	m_object2d[2] = CObject2d::Create();
	m_object2d[2]->SetTexture(CTexture::TEXTURE_CLEAR);
	m_object2d[2]->SetSize(D3DXVECTOR3(500.0f, 200.0f, 0.0f));
	m_object2d[2]->SetPos(CManager::Pos);
	m_object2d[2]->SetMove(D3DXVECTOR3(1.0f, -1.0f, 0.0f));

	return S_OK;
}

//========================
// リザルトの終了処理
//========================
void CResult::Uninit(void)
{
	// ポリゴンの終了処理
	CObject::ModeNotUninit();
}

//========================
// リザルトの更新処理
//========================
void CResult::Update(void)
{
	D3DXVECTOR3 DataPos = *m_object2d[2]->GetPos();
	D3DXVECTOR3 DataMove = m_object2d[2]->GetMove();
	D3DXVECTOR3 DataSize = m_object2d[2]->GetSize();

	if (DataPos.x < 0.0f + DataSize.x)
	{
		DataMove.x *= -1.0f;
	}
	if (DataPos.x > 1280.0f - DataSize.x)
	{
		DataMove.x *= -1.0f;
	}

	if (DataPos.y > 0.0f + DataSize.y)
	{
		DataMove.y *= -1.0f;
	}
	if (DataPos.y < 720.0f - DataSize.y)
	{
		DataMove.y *= -1.0f;
	}

	m_object2d[2]->SetPos(DataPos + DataMove);
	m_object2d[2]->SetMove(DataMove);
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_TITLE);
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::SetMode(CManager::MODE_TITLE);
	}

#endif // DEBUG
}

//========================
// リザルトの描画処理
//========================
void CResult::Draw(void)
{

}