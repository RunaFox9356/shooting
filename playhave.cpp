//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************

#include "playhave.h"
#include "ranking.h"

//=============================================================================
//プロトタイプ宣言
//=============================================================================


std::string CPlayhave::m_PlayName;
std::map<std::string, std::string>CPlayhave::m_Data;


void OnLoginFail(const PlayFabError& error, void*)
{
	printf("Something went wrong with your first API call.\n");
	printf("Here's some debug information:\n");
	printf(error.GenerateErrorReport().c_str());
	printf("\n");

}




//========================
//ログイン
//========================

LoginWithCustomIDRequest CPlayhave::IdSet(char*Id)
{
	PlayFabSettings::staticSettings->titleId = (Id);

	LoginWithCustomIDRequest request;
	request.CreateAccount = true;
	if (m_PlayName =="")
	{
		request.CustomId = GetMACAddr();
	}
	else
	{
		request.CustomId = m_PlayName;
	}

	return request;
}


//========================
//オンライン更新
//========================
void CPlayhave::APIUp()
{
	PlayFabClientAPI::Update();
}

//========================
// 任意のネットワークアダプタのMACアドレスを取得
//========================
std::string CPlayhave::GetMACAddr()
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
	if (GetAdaptersInfo(adapterInfo, &dwBufLen) == NO_ERROR)
	{
		PIP_ADAPTER_INFO pAdapterInfo = adapterInfo;
		sprintf(pOutMacAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

		pAdapterInfo = pAdapterInfo->Next;
	}
	else
	{
		// macアドレスが見つからない場合は固定文字列
		sprintf(pOutMacAddr, "user");
	}
	free(adapterInfo);
	return std::string(pOutMacAddr);
}

//========================
// GetScore
//========================
void CPlayhave::GetScore(std::function<void(const ClientModels::GetLeaderboardResult&)> func)
{
	LoginWithCustomIDRequest request = IdSet("323A0");
	
	PlayFabClientAPI::LoginWithCustomID(request, [func](PlayFab::ClientModels::LoginResult result, void* customData) {
		
		GetLeaderboardRequest req;

		req.StatisticName = "ScoreFox";//ゲームマネージャーでランキング名のやつ

		PlayFabClientAPI::GetLeaderboard(req,
			[func](const ClientModels::GetLeaderboardResult& resul, void*)
		{
			func(resul);
		});
	}, OnLoginFail);

}
//========================
// GetMasterData
//========================
void CPlayhave::GetMasterData()
{

	LoginWithCustomIDRequest request = IdSet("323A0");

	PlayFabClientAPI::LoginWithCustomID(request, [](PlayFab::ClientModels::LoginResult result, void* customData) {

		GetTitleDataRequest req;

		PlayFabClientAPI::GetTitleData(req,
			[](const ClientModels::GetTitleDataResult& result, void*)
		{//成功時
			m_Data = result.Data;
		});
	});
	
}

//========================
// SetScore
//========================
void CPlayhave::SetScore(const std::string playName, const int score)
{
	m_PlayName = playName;

	LoginWithCustomIDRequest request = IdSet("323A0");

	PlayFabClientAPI::LoginWithCustomID(request, [playName, score](PlayFab::ClientModels::LoginResult result, void* customData) {

		UpdateUserTitleDisplayNameRequest Namereq;
		
		Namereq.DisplayName = playName;

		PlayFabClientAPI::UpdateUserTitleDisplayName(Namereq, [](const UpdateUserTitleDisplayNameResult result, void*)
		{
			//成功

		});
		
		UpdatePlayerStatisticsRequest Scorereq;
		StatisticUpdate statistic;
		statistic.StatisticName = "ScoreFox";//ゲームマネージャーでランキング名のやつ

		statistic.Value = score;//小さい順にするためにの-１かける

		Scorereq.Statistics.push_back(statistic);

		PlayFabClientAPI::UpdatePlayerStatistics(Scorereq,
			[](const ClientModels::UpdatePlayerStatisticsResult&, void*)
		{//成功時

		});

		
	}, OnLoginFail);


}
