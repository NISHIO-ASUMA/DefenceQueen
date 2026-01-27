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
HRESULT CArrayManager::Init(void)
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
#ifdef _DEBUG
	// デバッグ表示
	CDebugproc::Print("最大アリ数 : [ %d ]", ArrayConfig::ALLARRAYS);
	CDebugproc::Draw(0, 240);
#endif // _DEBUG
}
//=========================================================
// 各スポナーに渡す関数
//=========================================================
std::vector<CArray*> CArrayManager::Allocate(const int& nStock)
{
	// ローカル配列
	std::vector<CArray*> result;
	result.reserve(nStock);

	// カウント用変数
	int nCnt = 0;

	// 要素数
	for (auto& pArray : m_pArrays)
	{
		// 未使用なら
		if (!pArray->GetActive())
		{
			// スポナー用に作成
			result.push_back(pArray);
			pArray->SetActive(true);
			nCnt++;
		}
		
		if (nCnt >= nStock) break;
	}

	// 要素数を返す
	return result;
}
//=========================================================
// 仲間の切り離し設定関数
//=========================================================
void CArrayManager::ApplySeparation(const D3DXVECTOR3& center, float radius)
{
	// 0以下なら
	if (radius <= 0.0f) return;

	for (auto pArray : m_pArrays)
	{
		// nullなら
		if (!pArray) continue;

		// 座標を取得
		D3DXVECTOR3 pos = pArray->GetPos();
		D3DXVECTOR3 diff =  center - pos;
		float fDis = D3DXVec3Length(&diff);

		if (fDis < radius)
		{
			// TODO : ここで当たったアリはノード切り替えを走らせる処理に変更する
			pArray->OnSeparation(); // アリに伝える
		}
	}
}
//=========================================================
// 配列のアクティブ数をセットする
//=========================================================
void CArrayManager::CountActiveArrays(const int& nCountArrays)
{
	m_nActiveAll += nCountArrays;
}
//=========================================================
// フラグをセットする
//=========================================================
void CArrayManager::SetActiveAll(void)
{
	for (int nCnt = 0; nCnt < m_nActiveAll; nCnt++)
	{
		// すでにアクティブなら
		if (m_pArrays[nCnt]->GetActive()) continue;

		// 指定数だけアクティブ数に設定する
		m_pArrays[nCnt]->SetActive(true);
	}
}