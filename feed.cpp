//===============================================
//
// 出現する餌の処理 [ feed.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルードファイル
//**********************
#include "feed.h"

//============================
// コンストラクタ
//============================
CFeed::CFeed(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
}
//============================
// デストラクタ
//============================
CFeed::~CFeed()
{

}
//============================
// 生成処理
//============================
CFeed* CFeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName)
{
	// インスタンス生成
	CFeed* pFeed = new CFeed;
	if (pFeed == nullptr) return nullptr;

	// オブジェクト設定
	pFeed->SetPos(pos);
	pFeed->SetRot(rot);
	pFeed->SetScale(scale);
	pFeed->SetFilePass(pModelName);
	pFeed->SetShadow(true);

	// 初期化失敗時
	if (FAILED(pFeed->Init())) 	return nullptr;

	return pFeed;
}
//============================
// 初期化処理
//============================
HRESULT CFeed::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	return S_OK;
}
//============================
// 終了処理
//============================
void CFeed::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//============================
// 更新処理
//============================
void CFeed::Update(void)
{
	// 親クラスの更新
	CObjectX::Uninit();
}
//============================
// 描画処理
//===========================
void CFeed::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}