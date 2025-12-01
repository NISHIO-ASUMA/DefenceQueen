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
#include "parameter.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstatebase.h"
#include "effect.h"
#include "game.h"
#include "sound.h"
#include "statemachine.h"
#include "boxcollider.h"
#include "collisionbox.h"
#include "motion.h"
#include "blockmanager.h"
#include "collisionbox.h"
#include "playerstateneutral.h"
#include "gamesceneobject.h"
#include "selectpoint.h"
#include "workermanager.h"
#include "worker.h"




//*********************************************************
// 名前空間
//*********************************************************
namespace PLAYERINFO
{
	constexpr float MOVE = 4.5f;	// 1フレームの移動量
	constexpr float NorRot = D3DX_PI * 2.0f; // 正規化値
};

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CPlayer::CPlayer(int nPriority) : CNoMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr)
{
	// 値のクリア
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
	
	// パラメーターポインタ生成
	pPlayer->m_pParameter = std::make_unique<CParameter>();

	// nullチェック
	if (pPlayer->m_pParameter != nullptr)
	{
		// 体力パラメーターを設定
		pPlayer->m_pParameter->SetHp(nLife);
		pPlayer->m_pParameter->SetMaxHp(nLife);
	}
	
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

	// 結果を返す
	return S_OK;
}
//=========================================================
// プレイヤー終了処理
//=========================================================
void CPlayer::Uninit(void)
{
	// パラメータ終了処理
	m_pParameter.reset();

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

	// デバッグ表示
	CDebugproc::Print("モーションタイプ [ %d ]", m_pMotion->GetMotionType());
	CDebugproc::Draw(0, 100);

	CDebugproc::Print("Player POS [ %.2f, %.2f,%.2f ]", GetPos().x,GetPos().y,GetPos().z);
	CDebugproc::Draw(0, 120);
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
}
//===================================================================
// ブロックとの当たり判定
//===================================================================
bool CPlayer::CollisionBlock(CBoxCollider* other,D3DXVECTOR3 * pos)
{
	// 矩形との当たり判定を返す
	return CCollisionBox::Collision(m_pBoxCollider, other, pos);
}