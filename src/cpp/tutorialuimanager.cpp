//=========================================================
//
// チュートリアルui複数管理処理 [ tutorialuimanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// クラス定義インクルードファイル
//*********************************************************
#include "tutorialuimanager.h"

//*********************************************************
// インクルードファイル
//*********************************************************
#include "manager.h"
#include "input.h"
#include "tutorialui.h"
#include "tutorialstatebase.h"
#include "tutorialstatemove.h"
#include "tutorialstatesepalation.h"
#include "tutorialstatefeedorder.h"

//*********************************************************
// 定数名前空間
//*********************************************************
namespace TUTORIALUIMANAGER
{
	const D3DXVECTOR3 ActivePos = { 1400.0f,110.0f,0.0f };	// 出現座標

	constexpr int MAX_SIZE = 3;							// 最大テクスチャ枚数
	constexpr float WIDTH = 180.0f;						// 横幅
	constexpr float HEIGHT = 100.0f;					// 高さ

	constexpr const char* TEXTURELIST[MAX_SIZE] =		// テクスチャリスト
	{
		"Manual_Move.jpg",
		"Manual_Sepalation.jpg",
		"Manual_GoFeed.jpg"
	};
};

//=========================================================
// コンストラクタ
//=========================================================
CTutorialUiManager::CTutorialUiManager() : m_pUiList{},
m_pStateList{},
m_nStateIndex(NULL)
{

}
//=========================================================
// デストラクタ
//=========================================================
CTutorialUiManager::~CTutorialUiManager()
{

}
//=========================================================
// インスタンス取得処理
//=========================================================
CTutorialUiManager* CTutorialUiManager::GetInstance(void)
{
	static CTutorialUiManager Instance;
	return &Instance;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTutorialUiManager::Init(void)
{
	// 名前空間を使用し省略
	using namespace TUTORIALUIMANAGER;

	// リストのクリア
	m_pUiList.clear();

	// 動的リストのサイズ設定
	for (int nCnt = 0; nCnt < MAX_SIZE; nCnt++)
	{
		// チュートリアルui生成
		CTutorialUi * pUi = CTutorialUi::Create(ActivePos, WIDTH, HEIGHT, TEXTURELIST[nCnt]);
		if (nCnt == 0) pUi->SetIsActive(true);

		// 配列に追加
		m_pUiList.push_back(pUi);
	}

	// ステートを作成する
	m_pStateList.push_back(std::make_unique<CTutorialStateMove>());
	m_pStateList.push_back(std::make_unique<CTutorialStateSepalation>());
	m_pStateList.push_back(std::make_unique<CTutorialStateFeedOrder>());

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTutorialUiManager::Uninit(void)
{
	// 配列のクリア
	m_pUiList.clear();
	m_pStateList.clear();
}
//=========================================================
// 更新処理
//=========================================================
void CTutorialUiManager::Update(void)
{
	// リストに何も無かったら
	if (m_pUiList.empty()) return;

	// 現在の表示uiを取得
	CTutorialUi* pCurrent = m_pUiList.front();
	
	// 現在のステートを取得
	CTutorialStateBase* pState = m_pStateList[m_nStateIndex].get();

	if (pState->OnCheck() && pCurrent->GetIsCheck())
	{
		// 今表示しているUIを消去しリスト内の次のuiを表示する
		pCurrent->SetIsAlpha(true);
	}

	// フェード終了したら削除
	if (pCurrent->GetIsFinish())
	{
		// 現在のuiを消去
		Erase(pCurrent);

		// ステートインデックスを進める
		m_nStateIndex++;

		// 次のUIを表示
		if (!m_pUiList.empty())
		{
			m_pUiList.front()->SetIsActive(true);
		}
	}
}
//=========================================================
// 消去処理
//=========================================================
void CTutorialUiManager::Erase(CTutorialUi* pUi)
{
	// uiの配列取得
	auto EraseObject = std::find(m_pUiList.begin(), m_pUiList.end(), pUi);

	// もし最後尾なら
	if (EraseObject == m_pUiList.end()) return;

	// 破棄
	(*EraseObject)->Uninit();

	// リストの修正
	EraseObject = m_pUiList.erase(EraseObject);
}