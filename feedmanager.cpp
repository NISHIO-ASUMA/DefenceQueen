//=========================================================
//
// 複数の餌を管理する処理 [ feedmanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "feedmanager.h"
#include "feed.h"
#include "meshcylinder.h"
#include "gamesceneobject.h"

//=========================================================
// コンストラクタ
//=========================================================
CFeedManager::CFeedManager() :m_pFeed{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CFeedManager::~CFeedManager()
{
	Uninit();
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CFeedManager::Init(void)
{
	// クリア
	m_pFeed.clear();

	// TODO : 一旦挙動を確認したらメモリだけ確保しておく処理に変更
	m_pFeed.resize(Config::ALLFEED);

	// TODO : のちに変更
	m_pFeed[0] = CFeed::Create(D3DXVECTOR3(-300.0f, 60.0f,-200.0f), VECTOR3_NULL, INITSCALE, "FEED/Suger.x",85.0f);
	m_pFeed[1] = CFeed::Create(D3DXVECTOR3(300.0f, 60.0f, -600.0f), VECTOR3_NULL, INITSCALE, "FEED/Suger.x", 85.0f);
	m_pFeed[2] = CFeed::Create(D3DXVECTOR3(0.0f, 60.0f, 550.0f), VECTOR3_NULL, INITSCALE, "FEED/Suger.x", 85.0f);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CFeedManager::Uninit(void)
{
	m_pFeed.clear();
}
//=========================================================
// 更新処理
//=========================================================
void CFeedManager::Update(void)
{
	// 経過時間によって出現する
	// auto GameSceneObject = CGameSceneObject::GetInstance();
	// auto time = GameSceneObject->GetTime();
}
//=========================================================
// 描画処理
//=========================================================
void CFeedManager::Draw(void)
{
	// 無し
}