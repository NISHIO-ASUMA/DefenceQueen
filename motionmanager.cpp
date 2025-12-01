//=========================================================
//
// モーションファイル管理クラス [ motionmanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "motionmanager.h"
#include "json.hpp"
#include <fstream>
#include "motion.h"

//*********************************************************
// 使用名前空間
//*********************************************************
using json = nlohmann::json;

//=========================================================
// コンストラクタ
//=========================================================
CMotionManager::CMotionManager() : m_File{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CMotionManager::~CMotionManager()
{
	UnLoad();
}
//=========================================================
// 全読み込み処理
//=========================================================
HRESULT CMotionManager::Load(void)
{
	// 配列のクリア
	m_File.clear();

	// ファイル読み込み

	return S_OK;
}
//=========================================================
// 全破棄処理
//=========================================================
void CMotionManager::UnLoad(void)
{
	// 配列の破棄
	m_File.clear();
}
//=========================================================
// モーションファイルの登録処理
//=========================================================
int CMotionManager::Register(const char* pMotionName, std::vector<CModel*>& pModel, const int nNumMotion, const bool isShadow)
{
	// モーションファイル名があったら
	for (int nCnt = 0; nCnt < m_File.size(); nCnt++)
	{
		if (m_File[nCnt].FilePath == pMotionName)
			return nCnt;
	}

	// 無いなら読み込んで登録
	MOTIONFILE newData = {};
	newData.FilePath = pMotionName;

	// モーションのロード関数
	newData.pMotion = LoadMotionFile(pMotionName, pModel,nNumMotion, isShadow);

	// 配列に追加する
	m_File.push_back(std::move(newData));

	// 番号を返す
	return static_cast<int>(m_File.size() - 1);
}
//=========================================================
// 実際にモーションファイルを読み込む
//=========================================================
std::unique_ptr<CMotion> CMotionManager::LoadMotionFile(const char* pScript, std::vector<CModel*>& pModel, const int nNumMotion, const bool isShadow)
{
	return CMotion::Load(pScript, pModel, nNumMotion, isShadow);
}