//============================
//
// TEXT
// Author:hamada ryuuga
//
//============================

#ifndef _TEXT_H_
#define _TEXT_H_

#include "object2d.h"
#include "words.h"

class CText : public CObject2d
{
public:

	enum Type
	{
		GON = 0,
		MASUO,
		MAX
	};

	CText(int list);
	~CText();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CText* Create(Type talkType, int DeleteTime, int SpeedText, const char * Text);
	void Releasetimer(int nTimar);
private:
	PositionVec4 col;
	int m_DesTimarMax;//消える最大時間
	int m_DesTimar;//消える時間

	int m_TextSize;//文字のサイズ
	int m_Addnumber;//1つの文字が加算されるまでの時間
	int m_AddCount;//文字が加算されるまでのカウント
	int m_AddLetter;//何文字目入れるか指定
	int m_wordsPopCount;//文字を出した最大数
	int m_wordsPopCountX;//横に文字を出した数
	int m_newlineCount;//改行の数
	bool m_isRelease;

	LPD3DXFONT m_pFont = nullptr;

	std::string m_Text;
	std::string m_ALLText;
	CWords** m_words;

	void TextLetter(const char * Text, int SpeedText);
};


#endif#pragma once
