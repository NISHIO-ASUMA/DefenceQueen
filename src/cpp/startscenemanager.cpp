//=========================================================
//
// 開始シーンの管理処理 [ startscenemanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// クラス定義ヘッダーファイル
//*********************************************************
#include "startscenemanager.h"

//*********************************************************
// システムインクルードファイル
//*********************************************************
#include <memory>

//*********************************************************
// インクルードファイル
//*********************************************************
#include "manager.h"
#include "fade.h"
#include "title.h"
#include "sound.h"
#include "ui.h"

//*********************************************************
// 定数名前空間
//*********************************************************
namespace STARTOBJECT
{
	constexpr int SIZE = 300;
	constexpr int ALPHAFRAME = 170;
	constexpr const char* FILENAME = "startgameicon.png";
};

//=========================================================
// コンストラクタ
//=========================================================
CStartSceneManager::CStartSceneManager() : m_nChangeCount(NULL)
{

}
//=========================================================
// デストラクタ
//=========================================================
CStartSceneManager::~CStartSceneManager()
{
	Uninit();
}
//=========================================================
// シングルトン取得
//=========================================================
CStartSceneManager* CStartSceneManager::GetInstance()
{
	static CStartSceneManager Instance;
	return &Instance;
};
//=========================================================
// 初期化処理
//=========================================================
HRESULT CStartSceneManager::Init(void)
{
	// ロゴUI生成
	CUi::Create(CENTERPOS, 0, STARTOBJECT::SIZE, STARTOBJECT::SIZE, STARTOBJECT::FILENAME,false,true, STARTOBJECT::ALPHAFRAME);

	// サウンド再生
	auto Sound = CManager::GetInstance()->GetSound();
	if (Sound) Sound->Play(CSound::SOUND_LABEL_START);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CStartSceneManager::Uninit(void)
{

}
//=========================================================
// 更新処理
//=========================================================
void CStartSceneManager::Update(void)
{
	// カウントを加算
	m_nChangeCount++;

	// 最大値より大きくなったら
	if (m_nChangeCount >= Config::MAX_CHANGECOUNT)
	{
		// フェードインスタンス取得
		auto Fade = CManager::GetInstance()->GetFade();

		if (Fade != nullptr)
		{
			// タイトルにシーンを切り替える
			Fade->SetFade(std::make_unique<CTitle>());
			return;
		}
	}
}