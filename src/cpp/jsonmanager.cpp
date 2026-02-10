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
#include "createjsonui.h"
#include "createjsonmeshfield.h"

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
CJsonManager::CJsonManager() : m_Creator{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CJsonManager::~CJsonManager()
{
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CJsonManager::Init(void)
{
	// Ui生成関数
	m_Creator[PATH_TAGNAME::UI] = std::make_unique<CJsonCreateUi>();
	m_Creator[PATH_TAGNAME::MESHFIELD] = std::make_unique<CJsonCreateMeshField>();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CJsonManager::Uninit(void)
{
	m_Creator.clear();
}
//=========================================================
// 実際のファイル読み込み処理
//=========================================================
HRESULT CJsonManager::Load(const char* LoadFileName)
{
	// 開くファイル
	std::ifstream file(LoadFileName);

	// ファイルがない場合
	if (!file.is_open())
	{
		// 例外メッセージ出力
		MessageBox(GetActiveWindow(), "ファイルの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// jsonデータをセットする
	json jsonfile;
	file >> jsonfile;
	file.close();

	// 識別タグで生成関数を呼び出す
	for (auto& Objectlist : jsonfile)
	{
		// オブジェクトのタグ取得
		std::string tag = Objectlist["ObjectTag"];

		// 該当タグを見つける
		auto it = m_Creator.find(tag);

		if (it != m_Creator.end())
		{
			// 生成関数
			it->second->Create(Objectlist);
		}
	}

	return S_OK;
}