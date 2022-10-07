//============================
//
// テキスト表示するべんり
// Author:hamada ryuuga
//
//============================

#include "text.h"
#include "manager.h"
#include "renderer.h"
#include "hamada.h"
#include <Shlwapi.h>

//=============================================================================
// コンストラクタ関数
//=============================================================================
CText::CText(int list) : CObject2d(list)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CText::~CText()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CText::Init()
{
	m_newlineCount = 0;
	m_wordsPopCount = 0;
	m_wordsPopCountX = 0;
	m_AddCount = 0;
	m_Text = "";
	CObject2d::Init();
	
	col = PositionVec4(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(
		0.0f, 1.0f, 0.0f, 1.0f));

	
	// フォントを使えるようにする
	DESIGNVECTOR design;

	AddFontResourceEx(
		"data/font/FZゴンタかな.otf", //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 38, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("FZゴンタかな"), &m_pFont);



	m_isRelease = false;
	m_DesTimar = 0;

	return S_OK;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CText::Uninit()
{

	DESIGNVECTOR design;

	RemoveFontResourceEx(
		TEXT("Data/font/FZゴンタかな.otf"), //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);
	for (int wordsCount = 0; wordsCount < m_TextSize; wordsCount++)
	{
		if (m_words[wordsCount] != nullptr)
		{
			m_words[wordsCount]->Uninit();
		}
	}
	delete[] m_words;

	CObject2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CText::Update()
{
	CObject2d::Update();


	if (m_isRelease)
	{
		m_DesTimar--;

		m_AddCount++;
		if (m_AddCount>=m_Addnumber)
		{
			if (m_AddLetter <= m_TextSize)
			{
				m_Text += m_ALLText[m_AddLetter];
				std::string Txt = m_Text;
				if (Txt != "")
				{//空白チェック
					if (hmd::is_sjis_lead_byte(m_ALLText[m_AddLetter])
						&& m_AddLetter < m_TextSize)
					{

						m_AddLetter++;
						m_Text += m_ALLText[m_AddLetter];
						m_AddLetter++;
						m_words[m_wordsPopCount] = CWords::Create(m_Text.c_str(),
													D3DXVECTOR3(50.0f * (m_wordsPopCountX + 1),m_pos.y + m_newlineCount*50.0f, m_pos.z), 
													D3DXVECTOR3(20.0f, 20.0f, 0.0f), 
													CFont::FONT_GON);
						m_wordsPopCount++;
						m_wordsPopCountX++;
					}
					else
					{
						if (m_Text != "\n")
						{
							m_AddLetter++;
							m_words[m_wordsPopCount] = CWords::Create(m_Text.c_str(),
														D3DXVECTOR3(50.0f * (m_wordsPopCountX + 1), m_pos.y + m_newlineCount*50.0f, m_pos.z),
														D3DXVECTOR3(20.0f, 20.0f, 0.0f),
														CFont::FONT_MEIRIO);
							m_wordsPopCount++;
							m_wordsPopCountX++;
						}
						else
						{
							m_wordsPopCountX = 0;
							m_AddLetter++;
							m_newlineCount++;
						}
					}

				}
			}
			m_Text = "";
			m_AddCount = 0;
		}
	
		CObject2d::SetColar(col);

		if (m_DesTimar <= 0)
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CText::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();


	RECT rect = { 60, 500, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	//wsprintf(str, _T(m_Text.c_str()));

	//m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


	// 新規深度値 <= Zバッファ深度値 (初期設定)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 生成関数
//=============================================================================
CText *CText::Create(Type talkType,int DeleteTime, int SpeedText,const char * Text)
{
	CText * pObject = nullptr;
	pObject = new CText(3);

	if (pObject != nullptr)
	{
		pObject->Init();

		switch (talkType)
		{
		case CText::GON:
			pObject->SetTexture(CTexture::TEXTURE_GONBOX);
			break;
		case CText::MASUO:
			pObject->SetTexture(CTexture::TEXTURE_MASUOBOX);
			break;
		case CText::MAX:
			break;
		default:
			break;
		}
		pObject->SetPos(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
		pObject->SetSize(D3DXVECTOR3(640.0f, 200.0f, 0.0f));

		pObject->Releasetimer(DeleteTime);
		pObject->TextLetter(Text, SpeedText);
	}

	return pObject;
}


//=============================================================================
// けすまでの時間設定関数
//=============================================================================
void CText::Releasetimer(int nTimar)
{
	m_DesTimar = nTimar;
	m_DesTimarMax = m_DesTimar;
	m_isRelease = true;
}

//=============================================================================
// けすまでの時間設定関数
//=============================================================================
void CText::TextLetter(const char * Text, int SpeedText)
{
	m_ALLText = Text;
	m_TextSize = m_ALLText.size();
 	m_Addnumber = SpeedText;
	m_AddLetter = 0;
	m_words = new CWords*[m_TextSize];
	for (int wordsCount = 0; wordsCount < m_TextSize; wordsCount++)
	{
		m_words[wordsCount] = nullptr;
	}

}

