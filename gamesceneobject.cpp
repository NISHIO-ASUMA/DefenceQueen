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

//**********************
// 静的メンバ変数
//**********************
CScore* CGameSceneObject::m_pScore = nullptr; // スコアクラス

//===========================
// コンストラクタ
//===========================
CGameSceneObject::CGameSceneObject()
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
	// プレイヤー生成
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, "data/MOTION/Player/Player100motion.txt");

	// スコアクラス生成
	m_pScore = CScore::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f), 60.0f, 40.0f);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3000.0f,3000.0f,1,1);

	return S_OK;
}
//===========================
// 終了処理
//===========================
void CGameSceneObject::Uninit(void)
{
	// null初期化
	m_pScore = nullptr;
}
//===========================
// 更新処理
//===========================
void CGameSceneObject::Update(void)
{
	// 無し
}