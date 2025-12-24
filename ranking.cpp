//=========================================================
//
// ランキングシーン処理 [ ranking.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "ranking.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "rankingobject.h"
#include "sound.h"
#include <memory>

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{

}
//=========================================================
// デストラクタ
//=========================================================
CRanking::~CRanking()
{
	// 無し
}
//=========================================================
// 生成処理
//=========================================================
CRanking* CRanking::Create(void)
{
	// インスタンス生成
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pRanking->Init())) return nullptr;

	return pRanking;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CRanking::Init(void)
{
	// ランキングオブジェクト生成
	CRankingObject::GetInstance()->Init();

	// サウンド取得
	auto Sound = CManager::GetInstance()->GetSound();
	if (Sound == nullptr)return E_FAIL;

	// BGM再生
	Sound->Play(CSound::SOUND_LABEL_RANKING);

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CRanking::Uninit(void)
{
	// インスタンスの破棄
	CRankingObject::GetInstance()->Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CRanking::Update(void)
{
	// オブジェクト更新
	CRankingObject::GetInstance()->Update();

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
//=========================================================
// 描画処理
//=========================================================
void CRanking::Draw(void)
{
	// 無し
}