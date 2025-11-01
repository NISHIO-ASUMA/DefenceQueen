//=======================================
//
// ランキングシーン処理 [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// インクルードファイル宣言
//******************************
#include "ranking.h"
#include "manager.h"
#include "rankingmanager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include <memory>

//===================================
// オーバーロードコンストラクタ
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{

}
//===================================
// デストラクタ
//===================================
CRanking::~CRanking()
{
	// 無し
}
//===================================
// 生成処理
//===================================
CRanking* CRanking::Create(void)
{
	// インスタンス生成
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pRanking->Init())) return nullptr;

	return pRanking;
}
//===================================
// 初期化処理
//===================================
HRESULT CRanking::Init(void)
{
	// インスタンス生成
	//m_pRankManager = new CRankingManager;

	//// nullじゃなかったら
	//if (m_pRankManager != nullptr)
	//{
	//	// 初期化処理
	//	m_pRankManager->Init();
	//}

	// 初期化結果を返す
	return S_OK;
}
//===================================
// 終了処理
//===================================
void CRanking::Uninit(void)
{

}
//===================================
// 更新処理
//===================================
void CRanking::Update(void)
{
	// nullチェック
	// if (m_pRankManager != nullptr) m_pRankManager->Update();

	// 決定キー入力
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// フェード取得
		CFade* pFade = CManager::GetInstance()->GetFade();
		if (pFade == nullptr) return;

		// 画面遷移
		pFade->SetFade(std::make_unique<CTitle>());
		return;
	}
}
//===================================
// 描画処理
//===================================
void CRanking::Draw(void)
{
	// 無し
}