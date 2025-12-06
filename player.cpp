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
#include "meshimpact.h"
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

//*********************************************************
// 名前空間
//*********************************************************
namespace PLAYERINFO
{
	constexpr float NorRot = D3DX_PI * 2.0f; // 正規化値
	constexpr float SPRED = 75.0f;			 // 散らす範囲
};

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CPlayer::CPlayer(int nPriority) : CNoMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr),
m_nNum(NULL),
m_nSelectSpawn(NULL),
m_nPrevSelectSpawn(-1)
{
	for (int nCnt = 0; nCnt < NUM_SPAWN; nCnt++)
	{
		m_pSpawnData[nCnt] = 0;
	}
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
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife, const char* pFilename)
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
	MotionLoad("data/MOTION/Player/Player100motion.txt", MOTION_MAX,false);

	// コライダー生成
	m_pBoxCollider = CBoxCollider::Create(GetPos(), GetOldPos(), D3DXVECTOR3(50.0f,50.0f,50.0f));

	// モーション取得
	m_pMotion = CNoMoveCharactor::GetMotion();

	// 味方のスポナーを取得
	auto pArraySpawn = CGameSceneObject::GetInstance()->GetArraySpawn();
	auto spawn = pArraySpawn->GetIndexSpawner(m_nSelectSpawn);

	// 存在時
	if (spawn)
	{
		auto topant = spawn->GetTopAnt();

		if (topant)
		{
			topant->SetIsActive(true);		// 最初からONになる
		}

		// 選択インデックス変更
		m_nPrevSelectSpawn = m_nSelectSpawn;
	}

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
//======================================================================================
// プレイヤー更新処理
//======================================================================================
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

	// 選択スポナーの処理
	if (pKeyboard->GetTrigger(DIK_L))
	{
		// インデックスを変更
		m_nSelectSpawn = Wrap(m_nSelectSpawn + 1, 0, 2);

		// アリスポナー配列取得
		auto pArraySpawn = CGameSceneObject::GetInstance()->GetArraySpawn();

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

			// 有効化
			if (currentTop)
			{
				currentTop->SetIsActive(true);
			}
		}

		// 選択インデックスを更新
		m_nPrevSelectSpawn = m_nSelectSpawn;
	}

	// 引数の数だけポイントに送る
	if (pKeyboard->GetTrigger(DIK_UP))
	{
		m_nNum += 2;
		m_nNum = Clump(m_nNum, 0, 10);
	}

	if (pKeyboard->GetTrigger(DIK_DOWN))
	{
		m_nNum -= 2;
		m_nNum = Clump(m_nNum, 0, 10);
	}

	if (pKeyboard->GetTrigger(DIK_K))
	{
		// スポナーに送る数とインデックスをセット
		SetSendArrayMoving(m_nSelectSpawn, m_nNum);
	}

	// 取得
	auto spawn = CGameSceneObject::GetInstance()->GetArraySpawn()->GetIndexSpawner(m_nSelectSpawn);
	if (spawn == nullptr) return;

	// テスト
	if (pKeyboard->GetTrigger(DIK_J))
	{
		// 取得
		auto top = spawn->GetTopAnt();
		if (top == nullptr) return;

		// 有効化
		top->SetIsActive(true);
	}

	// 当たり判定の管理関数
	CollisionAll(UpdatePos,pKeyboard,pJoyPad);

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

	CDebugproc::Print("Player Pos [ %.2f, %.2f,%.2f ]", GetPos().x,GetPos().y,GetPos().z);
	CDebugproc::Draw(0, 120);

	CDebugproc::Print("選択インデックス : [ %d ]", m_nSelectSpawn);
	CDebugproc::Draw(0, 200);

	CDebugproc::Print("設定する移動数 : [ %d ]", m_nNum);
	CDebugproc::Draw(0, 220);

}
//===========================================================
// 全コリジョンチェック関数
//===========================================================
void CPlayer::CollisionAll(D3DXVECTOR3 pPos, CInputKeyboard* pInput, CJoyPad* pPad)
{
	// 配置されているブロックを取得
	auto Block = CGameSceneObject::GetInstance()->GetBlockManager();
	if (Block == nullptr) return;

	// ブロックオブジェクトとの当たり判定
	for (int nBlock = 0; nBlock < Block->GetAll(); nBlock++)
	{
		// コライダー取得
		CBoxCollider* pOtherCollider = Block->GetBlock(nBlock)->GetCollider();
		if (pOtherCollider == nullptr) continue;

		// 実際のコリジョン
		if (CollisionBlock(pOtherCollider, &pPos))
		{
			// 座標セット
			SetPos(pPos);

			// コライダー座標更新
			m_pBoxCollider->SetPos(pPos);
		}
	}

	// 選択ポインタークラス
	auto pPoint = CGameSceneObject::GetInstance()->GetPoint();
	if (pPoint == nullptr) return;

	// 働きアリの配列取得
	auto pWorker = CGameSceneObject::GetInstance()->GetWorkerM();
	if (pWorker == nullptr) return;

	// 当たっていたら
	if (pPoint->GetIsHit())
	{
		// 決定キー or Aボタン入力
		if (pPad->GetTrigger(CJoyPad::JOYKEY_A) || pInput->GetTrigger(DIK_RETURN))
		{
			for (int nCnt = 0; nCnt < pWorker->GetSize(); nCnt++)
			{
				// キャラクター取得
				auto UseWorker = pWorker->GetWorker(nCnt);
				if (UseWorker == nullptr) continue;

				// 動かせるなら
				if (!UseWorker->GetIsWork())
				{
					// 有効状態にする
					UseWorker->SetIsWork(true);

					// 追跡対象にする座標を設定
					UseWorker->SetDestPos(pPoint->GetPos());

					// 一個に当たったら抜ける
					break;
				}

			}
		}
	}


	// キー入力
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// 一斉指示
	if (pKeyboard->GetTrigger(DIK_V))
	{
		// 指令
		OrderToArray(m_nNum, pPoint->GetPos());
	}
}
//===================================================================
// ブロックとの当たり判定
//===================================================================
bool CPlayer::CollisionBlock(CBoxCollider* other,D3DXVECTOR3 * pos)
{
	// 矩形との当たり判定を返す
	return false;
}
//===================================================================
// 指示を出して特定数のアリを送る処理
//===================================================================
void CPlayer::OrderToArray(int nNum,D3DXVECTOR3 destpos)
{// ここの関数をスポナーのインデックスを見てどのスポナーから何体動かすかを決めて一括でポイントに送れるように変更すること

#if 0
   // スポナーマネージャ取得
	auto pSpawnMgr = CGameSceneObject::GetInstance()->GetArraySpawn();
	if (!pSpawnMgr) return;

	// 現在選択中のスポナー
	auto pSpawner = pSpawnMgr->GetIndexSpawner(m_nSelectSpawn);
	if (!pSpawner) return;

	// 移動命令はスポナーに丸投げ
	pSpawner->OrderMove(nNum, destpos);
#endif

	// スポナーマネージャ取得
	auto pSpawnMgr = CGameSceneObject::GetInstance()->GetArraySpawn();
	if (!pSpawnMgr) return;

	for (int i = 0; i < NUM_SPAWN; i++)
	{
		int sendNum = m_pSpawnData[i];
		if (sendNum <= 0) continue;

		auto pSpawner = pSpawnMgr->GetIndexSpawner(i);
		if (!pSpawner) continue;

		// 各スポナーへ同時命令
		pSpawner->OrderMove(sendNum, destpos);
	}
}
//===================================================================
// あらかじめセットをしておく関数
//===================================================================
void CPlayer::SetSendArrayMoving(int nIdx, int nNum)
{
	// 値をセット
	m_pSpawnData[nIdx] = nNum;
}
//===================================================================
// 一定の範囲にランダムに設置する関数
//===================================================================
D3DXVECTOR3 CPlayer::RandomSetPos(const D3DXVECTOR3& pos, float fRadius,int nMoveActiveNum,int nIdx)
{
	// 以下なら
	if (nMoveActiveNum <= 0) return pos;

	// 角度を均等に割る
	float fAngle = (2.0f * D3DX_PI) * (static_cast<float>(nIdx) / nMoveActiveNum);

	// 基準値座標を設定する
	D3DXVECTOR3 OffSet = VECTOR3_NULL;
	OffSet.x = cosf(fAngle) * fRadius;
	OffSet.z = sinf(fAngle) * fRadius;
	OffSet.y = 0.0f;

	return pos + OffSet;
}
