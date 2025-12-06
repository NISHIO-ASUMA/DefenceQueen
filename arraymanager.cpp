//=========================================================
//
// 仲間クラス全体の管理処理 [ arraymanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "arraymanager.h"
#include "array.h"
#include "manager.h"
#include "input.h"
#include "template.h"
#include "debugproc.h"

//=========================================================
// コンストラクタ
//=========================================================
CArrayManager::CArrayManager() : m_pArrays{},m_nActiveAll(NULL)
{
	//
}
//=========================================================
// デストラクタ
//=========================================================
CArrayManager::~CArrayManager()
{
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CArrayManager::Init(const int nActives)
{
	// 配列初期化
	m_pArrays.clear();

	// 構造体変数
	ArrayConfig config = {};

	// メモリの箱だけ先に確保
	m_pArrays.reserve(config.ALLARRAYS);

	// ポインタのセット
	for (int nCnt = 0; nCnt < config.ALLARRAYS; nCnt++)
	{
		// インスタンス生成
		auto pArray = CArray::Create(VECTOR3_NULL,VECTOR3_NULL, config.LIFE);

		// 配列に追加
		m_pArrays.push_back(pArray);
	}

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CArrayManager::Uninit(void)
{
	// 動的配列の破棄
	m_pArrays.clear();
}
//=========================================================
// 更新処理
//=========================================================
void CArrayManager::Update(void)
{

}
//=========================================================
// 描画処理
//=========================================================
void CArrayManager::Draw(void)
{
	// デバッグ表示
	//CDebugproc::Print("アクティブ数 : [ %d / %d ]", m_nActiveAll, ArrayConfig::ALLARRAYS);
	//CDebugproc::Draw(0, 200);

}
//=========================================================
// スポナーに渡す関数
//=========================================================
std::vector<CArray*> CArrayManager::Allocate(const int& nStock)
{
	// ローカル配列
	std::vector<CArray*> result;

	// 要素数
	for (auto& pArray : m_pArrays)
	{
		// 未使用なら
		if (!pArray->GetActive())
		{
			// スポナー用に作成
			result.push_back(pArray);

			if (static_cast<int>(result.size()) >= nStock)
				break;
		}
	}

	// 要素数を返す
	return result;
}