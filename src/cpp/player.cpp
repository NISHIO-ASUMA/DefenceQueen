//=========================================================
//
// プレイヤー処理 [ player.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "player.h"
#include "manager.h"
#include "particle.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "effect.h"
#include "game.h"
#include "sound.h"
#include "statemachine.h"
#include "boxcollider.h"
#include "motion.h"
#include "blockmanager.h"
#include "playerstateneutral.h"
#include "gamesceneobject.h"
#include "selectpoint.h"
#include "workermanager.h"
#include "worker.h"
#include "playerstatebase.h"
#include "arraymanager.h"
#include "array.h"
#include "arrayspawnmanager.h"
#include "arrayspawner.h"
#include "template.h"
#include "topant.h"
#include "meshcylinder.h"
#include "pointobj.h"

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CPlayer::CPlayer(int nPriority) : CNoMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pStateMachine(nullptr),
m_pPointObj(nullptr),
m_nSendNum(NULL),
m_nSelectSpawn(NULL),
m_nPrevSelectSpawn(-1),
m_pSpawnData{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CPlayer::~CPlayer()
{
	// 無し
}
//=========================================================
// プレイヤー生成処理
//=========================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// プレイヤーのインスタンス生成
	CPlayer* pPlayer = new CPlayer;
	if (pPlayer == nullptr) return nullptr;

	// オブジェクト設定
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);
	pPlayer->SetUseStencil(true);
	
	// プレイヤー初期化処理
	if (FAILED(pPlayer->Init())) return nullptr;

	return pPlayer;
}
//=========================================================
// プレイヤー初期化処理
//=========================================================
HRESULT CPlayer::Init(void)
{
	// キャラクタ―の初期化
	CNoMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_PLAYER);

	// モーションセット
	MotionLoad("data/MOTION/Enemy/Enemy_Motion.txt", MOTION_MAX,false);

	// モーション取得
	m_pMotion = CNoMoveCharactor::GetMotion();

	 // オブジェクト生成
	 m_pPointObj = CPointObj::Create(D3DXVECTOR3(0.0f, Config::POINT_VALUE, 0.0f),D3DXVECTOR3(-D3DX_PI * 0.5f,0.0f,0.0f));

	// 味方のスポナーを取得
	auto pArraySpawn = CGameSceneObject::GetInstance()->GetArraySpawn();
	auto spawn = pArraySpawn->GetIndexSpawner(m_nSelectSpawn);
	if (spawn == nullptr) return E_FAIL;

	// 結果を返す
	return S_OK;
}
//=========================================================
// プレイヤー終了処理
//=========================================================
void CPlayer::Uninit(void)
{
	// キャラクターの破棄
	CNoMoveCharactor::Uninit();
}
//=========================================================
// プレイヤー更新処理
//=========================================================
void CPlayer::Update(void)
{
	// 現在の座標取得
	D3DXVECTOR3 posOld = GetOldPos();

	// 入力デバイスのポインタ取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// 更新された座標を取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// キャラクターの全体更新処理
	CNoMoveCharactor::Update();
}
//=========================================================
// プレイヤー描画処理
//=========================================================
void CPlayer::Draw(void)
{
#if 0
	// キャラクターの描画処理
	CNoMoveCharactor::Draw();
#endif

#ifdef _DEBUG
	CDebugproc::Print("Player Pos [ %.2f, %.2f,%.2f ]", GetPos().x,GetPos().y,GetPos().z);
	CDebugproc::Draw(0, 120);

	CDebugproc::Print("選択中のスポナーのインデックス : [ %d ]", m_nSelectSpawn);
	CDebugproc::Draw(0, 200);

	CDebugproc::Print("設定するアリの数 : [ %d ]", m_nSendNum);
	CDebugproc::Draw(0, 220);
#endif // _DEBUG
}
//===================================================================
// 指示を出して特定数のアリを送る処理
//===================================================================
void CPlayer::OrderToArray(const D3DXVECTOR3& destpos)
{
#if 0
	// スポナーマネージャ取得
	auto pSpawnMgr = CGameSceneObject::GetInstance()->GetArraySpawn();
	if (!pSpawnMgr) return;

	for (int nCnt = 0; nCnt < Config::NUM_SPAWN; nCnt++)
	{
		// 送る数を設定
		int sendNum = m_pSpawnData[nCnt];
		if (sendNum <= NULL) continue;

		// スポナーのインデックスを取得
		auto pSpawner = pSpawnMgr->GetIndexSpawner(nCnt);
		if (!pSpawner) continue;

		// トップのアリがアクティブの物だけから命令を生成する
		auto UseTop = pSpawner->GetTopAnt()->GetIsActive();
		if (!UseTop) continue;

		// ここでスポナーがもっているリストのインデックスを加算
		pSpawner->IncrementIdx();

		// 各スポナーへ命令する
		pSpawner->OrderMove(sendNum, destpos);

		// 値をクリア
		m_pSpawnData[nCnt] = 0;
	}

#endif
}
//===================================================================
// 設定を保存しておく関数
//===================================================================
void CPlayer::SetSendArrayMoving(int nIdx, int nNum)
{
	// 値をセット
	m_pSpawnData[nIdx] = nNum;
}