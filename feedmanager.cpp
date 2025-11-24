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

	// サイズセット
	m_pFeed.resize(3);

	// あらかじめ最大数生成する
	for (int nCnt = 0; nCnt < m_pFeed.size(); nCnt++)
	{
		// インスタンス生成
		m_pFeed[nCnt] = CFeed::Create(D3DXVECTOR3(300.0f * nCnt, 60.0f, nCnt * 200.0f), VECTOR3_NULL, INITSCALE, "FEED/Suger.x",85.0f);

		// 円柱生成
		CMeshCylinder::Create(D3DXVECTOR3(300.0f * nCnt, 0.0f, nCnt * 200.0f), m_pFeed[nCnt]->GetRadius());
	}

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
	auto GameSceneObject = CGameSceneObject::GetInstance();
	auto time = GameSceneObject->GetTime();


}
//=========================================================
// 描画処理
//=========================================================
void CFeedManager::Draw(void)
{

}