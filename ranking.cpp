//**************************************************
//
// ���� ( �����L���O )
// Author  : hamada ryuuga
//
//**************************************************
#include <stdio.h>
#include "ranking.h"
#include "main.h"
#include "input.h"
#include "manager.h"
#include "texture.h"
#include "object2d.h"
#include "name.h"
#include "fade.h"

#include "playfab/PlayFabError.h"
#include "playfab/PlayFabClientDataModels.h"
#include "playfab/PlayFabClientApi.h"
#include "playfab/PlayFabSettings.h"
#include "playfab/PlayFabApiSettings.h"
#include <windows.h>
#include <functional>
#include <iphlpapi.h>
#include <string>

#pragma comment(lib, "iphlpapi.lib")


using namespace PlayFab;
using namespace ClientModels;

bool finished = false;

CScore *CRanking::m_Ranking[MAX_RANK];
int CRanking::m_score;
std::string  CRanking::m_PlayName;

void OnLoginGet(const LoginResult& result, void* customData)
{
	printf("Congratulations, you made your first successful API call!\n");
	finished = true;
	CRanking::GerScore();
	Sleep(1000);
}

void OnLoginSet(const LoginResult& result, void* customData)
{
	printf("Congratulations, you made your first successful API call!\n");
	finished = true;
	CRanking::GoScore();
	CRanking::SetName();
}

void OnLoginFail(const PlayFabError& error, void* customData)
{
	printf("Something went wrong with your first API call.\n");
	printf("Here's some debug information:\n");
	printf(error.GenerateErrorReport().c_str());
	printf("\n");
	finished = true;
}

//========================
// �R���X�g���N�^
//========================
CRanking::CRanking()
{
}

//========================
// �f�X�g���N�^
//========================
CRanking::~CRanking()
{
}

//========================
// ������
//========================
inline HRESULT CRanking::Init(void)
{
	CRanking::OnlineSetScore();

	m_NowPlay = 0;
	m_NemePos = D3DXVECTOR3(30.0f, 100.0f, 0.0f);


	m_object2d[0] = CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_RANKINBG);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);

	m_object2d[1] = CObject2d::Create();
	m_object2d[1]->SetTexture(CTexture::TEXTURE_RANKIN);
	m_object2d[1]->SetSize(D3DXVECTOR3(100.0f, 300.0f, 0.0f));
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::Pos.x - 120.0f, 350.0f, 0.0f));

	finished = false;

	
	D3DXVECTOR3 pos = D3DXVECTOR3(CManager::Pos.x, 100.0f, 0.0f);
	for (int i = 0; i < MAX_RANK-1; i++)
	{
		m_Ranking[i] = CScore::Create(pos);
		m_Ranking[i]->Set(0);
		pos.y += 100.0f;
	}

	m_Ranking[5] = CScore::Create(pos);
	m_Ranking[5]->Set(m_score);

	PlayFabSettings::staticSettings->titleId = ("323A0");

	LoginWithCustomIDRequest request;
	request.CreateAccount = true;
	request.CustomId = GetMACAddr();

	PlayFabClientAPI::LoginWithCustomID(request, OnLoginGet, OnLoginFail);

	while (PlayFabClientAPI::Update() != 0)
		Sleep(1);

	return E_NOTIMPL;
}

//========================
//�@�j��
//========================
void CRanking::Uninit(void)
{
	/*for (int i = 0; i < 4; i++)
	{
		if (m_object2d[i] != nullptr)
		{
			m_object2d[i]->Uninit();
			m_object2d[i]->Release();
		}
	}
	for (int i = 0; i < 5; i++)
	{
		m_Ranking[i]->Uninit();
		m_Ranking[i]->Release();
	}*/
}

//========================
// �X�V
//========================
void CRanking::Update(void)
{

	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
	//���[�h�̐ݒ�
		CManager::GetFade()->NextMode(CManager::MODE_TITLE);
			return;
	
	}
}

//========================
// �`��
//========================
void CRanking::Draw()
{
}

//========================
// SET
//========================
void CRanking::GoScore()
{
	UpdatePlayerStatisticsRequest req;
	StatisticUpdate statistic;
	statistic.StatisticName = "ScoreFox";//�Q�[���}�l�[�W���[�Ń����L���O���̂��

	statistic.Value = m_score;//���������ɂ��邽�߂ɂ�-�P������

	req.Statistics.push_back(statistic);

	PlayFabClientAPI::UpdatePlayerStatistics(req,
		[](const ClientModels::UpdatePlayerStatisticsResult& resul, void*customData)
	{//������
		int a = 0;

	}, [](const PlayFabError& error, void*customData)
	{//���s��
	});
}

//========================
// OnlineSetScore
//========================
void CRanking::OnlineSetScore()
{
	finished = false;

	PlayFabSettings::staticSettings->titleId = ("323A0");

	LoginWithCustomIDRequest request;
	request.CreateAccount = true;
	request.CustomId = m_PlayName;//GetMACAddr();

	PlayFabClientAPI::LoginWithCustomID(request, OnLoginSet, OnLoginFail);

	while (PlayFabClientAPI::Update() != 0)
		Sleep(1);
}

//========================
// GerScore
//========================
void CRanking::GerScore()
{
	GetLeaderboardRequest req;

	req.StatisticName = "ScoreFox";//�Q�[���}�l�[�W���[�Ń����L���O���̂��

	PlayFabClientAPI::GetLeaderboard(req,
		[](const ClientModels::GetLeaderboardResult& resul, void*customData)
	{
		for (auto item : resul.Leaderboard)
		{
			if (item.Position <= 4)
			{
				const char * Name = item.DisplayName.c_str();//�Ȃ܂����L�����ɕϊ�
				// �\��
				m_Ranking[item.Position]->Set(item.StatValue);	
			}
		}
	});
}

//========================
// ranking�̖��܂���Set
//========================
void CRanking::SetName()
{
	UpdateUserTitleDisplayNameRequest req;

	req.DisplayName = m_PlayName;
	PlayFabClientAPI::UpdateUserTitleDisplayName(req, [](const UpdateUserTitleDisplayNameResult result, void* customData)
	{
		//����

	}, [](const PlayFabError& error, void* customData)
	{
		//���s
	});
}

//========================
// �C�ӂ̃l�b�g���[�N�A�_�v�^��MAC�A�h���X���擾
//========================
std::string CRanking::GetMACAddr()
{
	PIP_ADAPTER_INFO adapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);

	adapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	if (adapterInfo == NULL)
	{
		return "";
	}

	if (GetAdaptersInfo(adapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(adapterInfo);
		adapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufLen);
		if (adapterInfo == NULL) {
			return "";
		}
	}

	char pOutMacAddr[64];
	std::string macAddr;
	if (GetAdaptersInfo(adapterInfo, &dwBufLen) == NO_ERROR)
	{
		PIP_ADAPTER_INFO pAdapterInfo = adapterInfo;
		macAddr =
			sprintf(pOutMacAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
				pAdapterInfo->Address[0], pAdapterInfo->Address[1],
				pAdapterInfo->Address[2], pAdapterInfo->Address[3],
				pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

		pAdapterInfo = pAdapterInfo->Next;
	}
	else
	{
		// mac�A�h���X��������Ȃ��ꍇ�͌Œ蕶����
		sprintf(pOutMacAddr, "user");
	}
	free(adapterInfo);
	return std::string(pOutMacAddr);
}

//========================
//�����L���O�̒l���˂�����
//========================
void CRanking::SetScore(int nScore)
{
	m_score = nScore;
}
