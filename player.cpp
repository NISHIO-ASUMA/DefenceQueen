//=========================================
//
// プレイヤー処理 [ player.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "player.h"
#include "manager.h"
#include "texture.h"
#include "particle.h"
#include "shadow.h"
#include "meshimpact.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "parameter.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstate.h"
#include "effect.h"
#include "game.h"
#include "effectsmoke.h"
#include "sound.h"
#include "statemachine.h"

//**********************
// 名前空間
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 0.015f;		 // 1フレームの移動量
	constexpr float JUMPVALUE = 18.3f;	 // ジャンプ量
	constexpr float GRAVITY = 1.5f;		 // 重力値
	constexpr float HITRADIUS = 25.0f;	 // 当たり判定の半径
	constexpr float AVOID_COOLTIME = 5.0f;	// 回避のクールタイム
	constexpr float RADIUS = 550.0f;		// 半径
	constexpr int   NUMBER_MAIN = 0;	 // メイン操作プレイヤー番号
	constexpr int   NUMBER_SUB = 1;		 // 分身操作プレイヤー番号
	constexpr int   KeyRepeatCount = 15; // キーのリピート最大カウント
};

//**********************
// 静的メンバ変数宣言
//**********************
bool CPlayer::m_isDeath = false;  // 死亡フラグ

//===============================
// オーバーロードコンストラクタ
//===============================
CPlayer::CPlayer(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CPlayer::~CPlayer()
{
	// 無し
}
//===============================
// プレイヤー生成処理
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife, const char* pFilename)
{
	// プレイヤーのインスタンス生成
	CPlayer* pPlayer = new CPlayer;
	if (pPlayer == nullptr) return nullptr;

	// オブジェクト設定
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	// ポインタ生成
	pPlayer->m_pParameter = std::make_unique<CParameter>();

	// nullチェック
	if (pPlayer->m_pParameter != nullptr)
	{
		// 体力パラメーターを設定
		pPlayer->m_pParameter->SetHp(nLife);
		pPlayer->m_pParameter->SetMaxHp(nLife);
	}
	
	// プレイヤー初期化処理
	if (FAILED(pPlayer->Init()))
	{
		// nullptrを返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}
//===============================
// プレイヤー初期化処理
//===============================
HRESULT CPlayer::Init(void)
{
	// キャラクタ―の初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_PLAYER);

	// モーションセット
	MotionLoad("data/MOTION/Player/Player100motion.txt", MOTION_MAX);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// 初期状態をセット
	ChangeState(new CPlayerStateNeutral,CPlayerStateBase::ID_NEUTRAL); 

	// 結果を返す
	return S_OK;
}
//===============================
// プレイヤー終了処理
//===============================
void CPlayer::Uninit(void)
{
	// パラメータ終了処理
	m_pParameter.reset();

	// ステート終了処理
	m_pStateMachine.reset();

	// キャラクターの破棄
	CMoveCharactor::Uninit();
}
//============================================================
// プレイヤー更新処理
//============================================================
void CPlayer::Update(void)
{
	// 死んでるなら処理しない
	if (m_isDeath) return;

	// 現在シーン取得
	CScene::MODE nMode = CManager::GetInstance()->GetInstance()->GetScene();

	// 入力デバイスのポインタ取得
	CInputKeyboard* pInput = nullptr;
	CJoyPad* pJoyPad = nullptr;
	pInput = CManager::GetInstance()->GetInputKeyboard();
	pJoyPad = CManager::GetInstance()->GetJoyPad();

	// nullptrじゃないとき
	if (m_pStateMachine != nullptr)
	{
		// ステート更新
		m_pStateMachine->Update();
	}

	// キャラクターの更新処理
	CMoveCharactor::Update();
}
//===============================
// プレイヤー描画処理
//===============================
void CPlayer::Draw(void)
{
	// キャラクターの描画処理
	CMoveCharactor::Draw();
}
//=========================================
// ステート変更
//=========================================
void CPlayer::ChangeState(CPlayerStateBase* pNewState,int id)
{
	// 自分自身を代入
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}
//===============================
// キー押下時の入力取得
//===============================
bool CPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// いずれかの移動キー入力
	return (pKeyInput->GetPress(DIK_A) || pKeyInput->GetPress(DIK_D));
}
//===============================
// キー押下時の入力取得
//===============================
bool CPlayer::isMovePadButton(CJoyPad* pPad)
{
	// いずれかの移動キー入力
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
