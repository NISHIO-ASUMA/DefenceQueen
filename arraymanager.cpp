//===============================================
//
// 仲間クラス全体の管理処理 [ arraymanager.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルードファイル
//**********************
#include "arraymanager.h"
#include "array.h"
#include "manager.h"
#include "input.h"
#include "template.h"
#include "debugproc.h"

//**********************
// 定数宣言空間
//**********************
namespace ARRAYINFO
{
	constexpr int LIFE = 10; // 体力値
	constexpr int ALLARRAYS = 100; // 最大使用数
};

//===========================
// コンストラクタ
//============================
CArrayManager::CArrayManager() : m_pArrays{}, m_nActiveAll(NULL)
{

}
//===========================
// デストラクタ
//============================
CArrayManager::~CArrayManager()
{
	Uninit();
}
//===========================
// 初期化処理
//============================
HRESULT CArrayManager::Init(const int nActives)
{
	// 配列初期化
	m_pArrays.clear();

	// メモリの箱だけ先に確保
	m_pArrays.reserve(ARRAYINFO::ALLARRAYS);

	// ポインタのセット
	for (int nCnt = 0; nCnt < ARRAYINFO::ALLARRAYS; nCnt++)
	{
		// インスタンス生成
		auto pArray = CArray::Create(VECTOR3_NULL,VECTOR3_NULL,ARRAYINFO::LIFE);

		// 配列に追加
		m_pArrays.push_back(pArray);
	}

	// サイズの範囲内にあるかどうかチェック
	int nUse = Clump(nActives, 0, ARRAYINFO::ALLARRAYS);

	for (int nActive = 0; nActive < nUse; nActive++)
	{
		// 要素を代入
		auto pArray = m_pArrays[nActive];

		// 有効状態にする
		pArray->SetActive(true);

		// アクティブ数を加算
		m_nActiveAll++;
	}

	return S_OK;
}
//===========================
// 終了処理
//============================
void CArrayManager::Uninit(void)
{
	// 動的配列の破棄
	m_pArrays.clear();
}
//===========================
// 更新処理
//============================
void CArrayManager::Update(void)
{
#ifdef _DEBUG

	// キー入力情報取得
	auto* pInputKey = CManager::GetInstance()->GetInputKeyboard();

	// キー入力で増減確認
	if (pInputKey->GetTrigger(DIK_N))
	{// 増加させる
		m_nActiveAll = Clump(m_nActiveAll + 1, 0, static_cast<int>(m_pArrays.size()));
	}
	else if (pInputKey->GetTrigger(DIK_M))
	{// 減少させる
		m_nActiveAll = Clump(m_nActiveAll - 1, 0, static_cast<int>(m_pArrays.size()));
	}

#endif // _DEBUG
}
//===========================
// 描画処理
//============================
void CArrayManager::Draw(void)
{
	// デバッグ表示
	CDebugproc::Print("アクティブ数 : [ %d / %d ]", m_nActiveAll, ARRAYINFO::ALLARRAYS);
	CDebugproc::Draw(0, 140);
}
//===========================
// 出現管理処理
//============================
void CArrayManager::Spawn(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,const int nNumSpawn)
{
	// 出現数超過の時
	if (m_nActiveAll >= ARRAYINFO::ALLARRAYS)
	{
		// 例外設定
		OutputDebugStringA("出現上限に達しました!\n");
		return;
	}

	// 出現数を範囲内に制限
	int nSpawnCount = Clump(nNumSpawn, 0, ARRAYINFO::ALLARRAYS - m_nActiveAll);

	// スポーンするカウント
	int nSpawned = 0;

	for (auto& pArray : m_pArrays)
	{
		// falseの物を探す
		if (!pArray->GetActive())
		{
			// 再設定処理
			pArray->Reset(pos, rot, nLife);

			// カウント加算
			nSpawned++;
			m_nActiveAll++;

			// 指定数出現したら終了
			if (nSpawned >= nSpawnCount) break;

			// 最大数に達したら出現させない
			if (m_nActiveAll >= ARRAYINFO::ALLARRAYS) break;
		}
	}
}