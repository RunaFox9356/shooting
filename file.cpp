//============================
//
// ファイル設定
// Author:hamada ryuuga
//
//============================

#include "file.h"
#include "letter.h"
#include "particle.h"
#include "manager.h"
#include "texture.h"
#include "particle_manager.h"

static int index = 0;
namespace nl = nlohmann;

nl::json j;//リストの生成

//============================
// 全部出力（置くだけ）
//============================
void OutputStatus()
{
	/*DataEffect = GetImguiParticle();

	j["POS"] = {{ "X", DataEffect.pos.x} ,{ "Y", DataEffect.pos.y} ,{ "Z", DataEffect.pos.z } };
	j["POSMAX"] = {{ "X", DataEffect.maxPopPos.x } ,{ "Y", DataEffect.maxPopPos.y } ,{ "Z", DataEffect.maxPopPos.z } };
	j["POSMIN"] = {{ "X", DataEffect.minPopPos.x } ,{ "Y", DataEffect.minPopPos.y } ,{ "Z", DataEffect.minPopPos.z } };
	j["MOVE"] = { { "X", DataEffect.move.x } ,{ "Y", DataEffect.move.y } ,{ "Z", DataEffect.move.z } };
	j["MOVETRANSITION"] = { { "X", DataEffect.moveTransition.x } ,{ "Y", DataEffect.moveTransition.y } ,{ "Z", DataEffect.moveTransition.z } };
	j["ROT"] = { {"X", DataEffect.rot.x} ,{ "Y", DataEffect.rot.y },{ "Z", DataEffect.rot.z } };
	
	j["COL"] = { { "R", DataEffect.color.col.r }, {"G" ,DataEffect.color.col.g} ,{ "B", DataEffect.color.col.b } ,{ "A", DataEffect.color.col.a } };
	j["COLRANDAMMAX"] = { { "R", DataEffect.color.colRandamMax.r },{ "G" ,DataEffect.color.colRandamMax.g } ,{ "B", DataEffect.color.colRandamMax.b } ,{ "A", DataEffect.color.colRandamMax.a } };
	j["COLRANDAMMIN"] = { { "R", DataEffect.color.colRandamMin.r },{ "G" ,DataEffect.color.colRandamMin.g } ,{ "B", DataEffect.color.colRandamMin.b } ,{ "A", DataEffect.color.colRandamMin.a } };
	j["COLTRANSITION"] = { { "R", DataEffect.color.colTransition.r },{ "G" ,DataEffect.color.colTransition.g } ,{ "B", DataEffect.color.colTransition.b } ,{ "A", DataEffect.color.colTransition.a } };
	j["DESTCOL"] = { { "R", DataEffect.color.destCol.r },{ "G" ,DataEffect.color.destCol.g } ,{ "B", DataEffect.color.destCol.b } ,{ "A", DataEffect.color.destCol.a } };
	j["ENDTIME"] = DataEffect.color.nEndTime;
	j["CNTTRANSITIONTIME"] = DataEffect.color.nCntTransitionTime;
	j["BCOLTRANSITION"] = DataEffect.color.bColTransition;
	j["COLRANDOM"] = DataEffect.color.bColRandom;
	j["RANDOMTRANSITIONTIME"] = DataEffect.color.bRandomTransitionTime;
	
	j["TYPE"] = DataEffect.type;
	j["WIDTH"] = DataEffect.fWidth;
	j["HEIGHT"] = DataEffect.fHeight;
	j["ANGLE"] = DataEffect.fAngle;
	j["ATTENUATION"] = DataEffect.fAttenuation;
	j["RADIUS"] = DataEffect.fRadius;
	j["WEIGHT"] = DataEffect.fWeight;
	j["WEIGHTTRANSITION"] = DataEffect.fWeightTransition;
	j["LIFE"] = DataEffect.nLife;
	j["BACKROT"] = DataEffect.bBackrot;
	j["SCALE"] = DataEffect.fScale;

	auto jobj = j.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = "data/FILE/DataEffectOutput.json";
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();*/
}

void LoadJson(const char* cUrl)
{
	std::ifstream ifs(cUrl);

	if (ifs)
	{
		CParticleManager::BundledData loadData = {};
		CParticle::Info& particleInfo = loadData.particleData;

		//StringToWString(UTF8toSjis(j["name"]));
		//DataSet.unionsname = StringToWString(UTF8toSjis(j["unions"] ["name"]));
		ifs >> j;

		particleInfo.maxPopPos = D3DXVECTOR3(j["POSMAX"]["X"], j["POSMAX"]["Y"], j["POSMAX"]["Z"]);
		particleInfo.minPopPos = D3DXVECTOR3(j["POSMIN"]["X"], j["POSMIN"]["Y"], j["POSMIN"]["Z"]);
		//こっちで構造体にデータを入れてます//文字は変換つけないとばぐるぞ＾＾これ-＞UTF8toSjis()
		particleInfo.move = D3DXVECTOR3(j["MOVE"]["X"], j["MOVE"]["Y"], j["MOVE"]["Z"]);
		particleInfo.rot = D3DXVECTOR3(j["ROT"]["X"], j["ROT"]["Y"], j["ROT"]["Z"]);
		particleInfo.moveTransition = D3DXVECTOR3(j["MOVETRANSITION"]["X"], j["MOVETRANSITION"]["Y"], j["MOVETRANSITION"]["Z"]);;

		particleInfo.color.colBigin = D3DXCOLOR(j["COL"]["R"], j["COL"]["G"], j["COL"]["B"], j["COL"]["A"]);
		particleInfo.color.colRandamMax = D3DXCOLOR(j["COLRANDAMMAX"]["R"], j["COLRANDAMMAX"]["G"], j["COLRANDAMMAX"]["B"], j["COLRANDAMMAX"]["A"]);
		particleInfo.color.colRandamMin = D3DXCOLOR(j["COLRANDAMMIN"]["R"], j["COLRANDAMMIN"]["G"], j["COLRANDAMMIN"]["B"], j["COLRANDAMMIN"]["A"]);
		particleInfo.color.colTransition = D3DXCOLOR(j["COLTRANSITION"]["R"], j["COLTRANSITION"]["G"], j["COLTRANSITION"]["B"], j["COLTRANSITION"]["A"]);
		particleInfo.color.destCol = D3DXCOLOR(j["DESTCOL"]["R"], j["DESTCOL"]["G"], j["DESTCOL"]["B"], j["DESTCOL"]["A"]);
		particleInfo.color.nEndTime = j["ENDTIME"];
		particleInfo.color.nCntTransitionTime = j["CNTTRANSITIONTIME"];
		particleInfo.color.bColTransition = j["BCOLTRANSITION"];
		particleInfo.color.bColRandom = j["COLRANDOM"];
		particleInfo.color.bRandomTransitionTime = j["RANDOMTRANSITIONTIME"];

		particleInfo.type = j["TYPE"];
		particleInfo.fWidth = j["WIDTH"];
		particleInfo.fHeight = j["HEIGHT"];
		particleInfo.fRadius = j["RADIUS"];
		particleInfo.fAngle = j["ANGLE"];
		particleInfo.fWeight = j["WEIGHT"];
		particleInfo.nLife = j["LIFE"];
		particleInfo.fAttenuation = j["ATTENUATION"];
		particleInfo.fWeightTransition = j["WEIGHTTRANSITION"];
		particleInfo.nLife = j["LIFE"];
		particleInfo.bBackrot = j["BACKROT"];
		particleInfo.fScale = j["SCALE"];

		static bool chack = true;

		if (chack)
		{
			CManager::GetParticleManager()->SetBundledData(loadData, index);
			index++;
		}
		else
		{
			CManager::GetParticleManager()->ChangeBundledData(0, loadData);
		}
	}

}
