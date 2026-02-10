//=========================================================
//
// jsonファイル読み込み管理処理 [ jsonmanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "jsonmanager.h"
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

//*********************************************************
// json空間を使用
//*********************************************************
using json = nlohmann::json;

//*********************************************************
// タグ名の定数宣言
//*********************************************************
namespace PATH_TAGNAME
{
	constexpr const char* UI		= "Ui";			// UIパラメータ
	constexpr const char* MESHDOME	= "MeshDome";	// メッシュドームパラメータ
	constexpr const char* MESHFIELD = "MeshField";	// メッシュフィールドパラメータ
};

//=========================================================
// コンストラクタ
//=========================================================
CJsonManager::CJsonManager() : TagName{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CJsonManager::~CJsonManager()
{

}
//=========================================================
// 実際のファイル読み込み処理
//=========================================================
HRESULT CJsonManager::Load(const char* LoadFileName)
{
	// 配列のクリア
	TagName.clear();

	// 開くファイル
	std::ifstream file(LoadFileName);

	// ファイルがない場合
	if (!file.is_open())
	{
		// 例外メッセージ出力
		MessageBox(GetActiveWindow(), "ファイルの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);

		// 終了
		return E_FAIL;
	}

	// jsonデータをセットする
	json jsonfile;
	file >> jsonfile;

	// ファイルを閉じる
	file.close();

	// 識別タグを取得
	
	return S_OK;
}