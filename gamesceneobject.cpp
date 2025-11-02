//==================================================
//
// ゲームのオブジェクト管理処理 [ gameobject.cpp ]
// Author: Asuma Nishio
//
//==================================================

//**********************
// インクルードファイル
//**********************
#include "gamesceneobject.h"
#include "ui.h"
#include "player.h"
#include "meshfield.h"
#include "blockmanager.h"

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "BS_thread_pool.hpp"

//**********************
// 静的メンバ変数
//**********************
CScore* CGameSceneObject::m_pScore = nullptr; // スコアクラス

//===========================
// コンストラクタ
//===========================
CGameSceneObject::CGameSceneObject() : m_pBlocks(nullptr)
{
	// 値のクリア
}
//===========================
// デストラクタ
//===========================
CGameSceneObject::~CGameSceneObject()
{
	// 無し
}
//===========================
// 初期化処理
//===========================
HRESULT CGameSceneObject::Init(void)
{
#if 1
	// プレイヤー生成
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, "data/MOTION/Player/Player100motion.txt");

	// スコアクラス生成
	// m_pScore = CScore::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f), 60.0f, 40.0f);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 2100.0f,1500.0f,1,1);

	// ブロックマネージャー生成
	m_pBlocks = std::make_unique<CBlockManager>();
	m_pBlocks->Init();
#else
	// スレッドプールを3スレッドで作成
	BS::thread_pool pool(3);

	// 並列にロードする処理を投げる
	auto future_player = pool.submit_task([] {
		// プレイヤー生成
		CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, "data/MOTION/Player/Player100motion.txt");
		});

	auto future_field = pool.submit_task([] {
		// メッシュフィールド生成
		CMeshField::Create(VECTOR3_NULL, 2100.0f, 1500.0f, 1, 1);
		});

	auto future_blocks = pool.submit_task([this] {
		// ブロックマネージャ生成
		m_pBlocks = std::make_unique<CBlockManager>();
		m_pBlocks->Init();
		});

	// 全タスクの完了を待つ
	future_player.get();
	future_field.get();
	future_blocks.get();
#endif
	return S_OK;
}
//===========================
// 終了処理
//===========================
void CGameSceneObject::Uninit(void)
{
	// null初期化
	m_pScore = nullptr;

	// 破棄
	m_pBlocks.reset();
}
//===========================
// 更新処理
//===========================
void CGameSceneObject::Update(void)
{
	// 無し
}