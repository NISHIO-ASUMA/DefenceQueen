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

//*********************************************************
// 名前空間
//*********************************************************
namespace PLAYERINFO
{
	constexpr float NorRot = D3DX_PI * 2.0f; // 正規化値
	constexpr float SPRED = 75.0f;			 // 散らす範囲
	const D3DXVECTOR3 POS = D3DXVECTOR3(-0.1f,-0.1f,-0.1f);
};

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CPlayer::CPlayer(int nPriority) : CNoMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr),
m_pCylinder(nullptr),
m_nNum(NULL),
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
	// MotionLoad("data/MOTION/Enemy/Enemy_Motion.txt", MOTION_MAX,false);
	MotionLoad("data/MOTION/Player/Player100motion.txt", MOTION_MAX, false);

	// コライダー生成
	m_pBoxCollider = CBoxCollider::Create(GetPos(), GetOldPos(), D3DXVECTOR3(50.0f,50.0f,50.0f));

	// モーション取得
	m_pMotion = CNoMoveCharactor::GetMotion();

	// メッシュ生成
	 m_pCylinder = CMeshCylinder::Create(VECTOR3_NULL, 65.0f);

#if 1
	// 味方のスポナーを取得
	auto pArraySpawn = CGameSceneObject::GetInstance()->GetArraySpawn();
	auto spawn = pArraySpawn->GetIndexSpawner(m_nSelectSpawn);
	if (spawn == nullptr) return E_FAIL;

	// 存在しているなら
	if (spawn)
	{
		// 取得
		auto topant = spawn->GetTopAnt();

		if (topant)
		{
			// 最初からONになる
			topant->SetIsActive(true);	

			// 円柱の座標を移動
			 m_pCylinder->SetPos(topant->GetPos());
		}

		// 選択インデックス変更
		m_nPrevSelectSpawn = m_nSelectSpawn;
	}
#endif
	// 結果を返す
	return S_OK;
}
//=========================================================
// プレイヤー終了処理
//=========================================================
void CPlayer::Uninit(void)
{
	// コライダー破棄
	if (m_pBoxCollider)
	{
		delete m_pBoxCollider;
		m_pBoxCollider = nullptr;
	}

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

	// コライダーの位置更新
	if (m_pBoxCollider)
	{
		m_pBoxCollider->SetPos(UpdatePos);
		m_pBoxCollider->SetPosOld(posOld);
	}

	// アクションキー
	InputAction(pKeyboard, pJoyPad);

	// null値チェック
	if (m_nSelectSpawn != -1)
	{
		auto pArraySpawn = CGameSceneObject::GetInstance()->GetArraySpawn();
		auto pSpawn = pArraySpawn->GetIndexSpawner(m_nSelectSpawn);

		if (pSpawn)
		{
			auto pTop = pSpawn->GetTopAnt();

			if (pTop)
			{
				m_pCylinder->SetPos(pTop->GetPos());
			}
		}
	}

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

	CDebugproc::Print("設定するアリの数 : [ %d ]", m_nNum);
	CDebugproc::Draw(0, 220);
#endif // _DEBUG
}
//===========================================================
// プレイヤーが操作する情報関数
//===========================================================
void CPlayer::InputAction(CInputKeyboard* pKey, CJoyPad* pPad)
{
	// アリスポナー配列取得
	auto pArraySpawn = CGameSceneObject::GetInstance()->GetArraySpawn();

	// スポナーの指示アリを切り替える処理
	if (pKey->GetTrigger(DIK_L) || pPad->GetTrigger(CJoyPad::JOYKEY_LEFT_B) || pPad->GetTrigger(CJoyPad::JOYKEY_RIGHT_B))
	{
		// インデックスを変更
		m_nSelectSpawn = Wrap(m_nSelectSpawn + 1, 0, Config::NUM_SPAWN - 1);

		// トップアリをoffにする
		if (m_nPrevSelectSpawn != -1)
		{
			// 前のスポナーのトップアリを取得
			auto prevSpawn = pArraySpawn->GetIndexSpawner(m_nPrevSelectSpawn);
			if (prevSpawn)
			{
				// アリ取得
				auto prevTop = prevSpawn->GetTopAnt();

				// 取得できたらoffにする
				if (prevTop)
				{
					prevTop->SetIsActive(false);
				}
			}
		}

		// トップアリをonにする
		auto currentSpawn = pArraySpawn->GetIndexSpawner(m_nSelectSpawn);

		// 取得できたら
		if (currentSpawn)
		{
			// 現在インデックスのトップ取得
			auto currentTop = currentSpawn->GetTopAnt();

			if (currentTop)
			{
				// 有効化
				currentTop->SetIsActive(true);

				// ここでメッシュの座標をセットする
				m_pCylinder->SetPos(currentTop->GetPos());
			}
		}

		// 選択インデックスを更新
		m_nPrevSelectSpawn = m_nSelectSpawn;
	}

	// 送る数を加算する
	if (pKey->GetTrigger(DIK_UP) || pPad->GetTriggerLT())
	{
		m_nNum += Config::VALUE_ANT;
		m_nNum = Clump(m_nNum, 0, Config::MAX_VALUE);
	}

	// 送る数を減算する
	if (pKey->GetTrigger(DIK_DOWN) || pPad->GetTriggerRT())
	{
		m_nNum -= Config::VALUE_ANT;
		m_nNum = Clump(m_nNum, 0, Config::MAX_VALUE);
	}

	// イベント登録
	auto TopS = pArraySpawn->GetIndexSpawner(m_nSelectSpawn)->GetTopAnt();

	// 有効化されている物だけ
	if (TopS->GetIsActive())
	{
		TopS->RegisterEvent([&](void) { this->SetSendArrayMoving(m_nSelectSpawn,m_nNum); });
	}

	// 移動命令を送る処理
	if (pKey->GetTrigger(DIK_V) || pPad->GetTrigger(CJoyPad::JOYKEY_X))
	{
		// 指定座標
		D3DXVECTOR3 point = VECTOR3_NULL;
		point = CGameSceneObject::GetInstance()->GetArraySpawn()->GetIndexSpawner(m_nSelectSpawn)->GetTopAnt()->GetDestPos();

		// 指令アリの当たったポイントで判断する
		OrderToArray(point);
	}
}
//===================================================================
// 指示を出して特定数のアリを送る処理
//===================================================================
void CPlayer::OrderToArray(const D3DXVECTOR3& destpos)
{
	// スポナーマネージャ取得
	auto pSpawnMgr = CGameSceneObject::GetInstance()->GetArraySpawn();
	if (!pSpawnMgr) return;

	for (int nCnt = 0; nCnt < Config::NUM_SPAWN; nCnt++)
	{
		// 送る数を設定
		int sendNum = m_pSpawnData[nCnt];
		if (sendNum <= 0) continue;

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
}
//===================================================================
// 設定を保存しておく関数
//===================================================================
void CPlayer::SetSendArrayMoving(int nIdx, int nNum)
{
	// 値をセット
	m_pSpawnData[nIdx] = nNum;
}