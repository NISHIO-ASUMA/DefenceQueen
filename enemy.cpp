//=========================================================
//
// 敵の処理 [ enemy.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "enemy.h"
#include "parameter.h"
#include "motion.h"
#include "shadowS.h"
#include "manager.h"
#include "enemystatebase.h"
#include "statemachine.h"
#include "spherecollider.h"
#include "collisionsphere.h"
#include "blackboard.h"
#include "node.h"
#include "behaviortree.h"
#include "gamesceneobject.h"
#include "selectpoint.h"
#include "enemybehaviortree.h"
#include "queen.h"
#include "template.h"
#include "input.h"
#include "feedmanager.h"
#include "feed.h"

//*********************************************************
// 定数宣言空間
//*********************************************************
namespace EnemyInfo
{
	constexpr float HitRange = 80.0f; // 球形範囲
	const char* MOTION_NAME = "data/MOTION/Enemy/Enemy_Motion.txt";
};

//=========================================================
// コンストラクタ
//=========================================================
CEnemy::CEnemy(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pSphereCollider(nullptr),
m_pTargetFeed(nullptr),
m_isActive(false),
m_isDestQueen(false),
m_isDestFeed(false)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CEnemy::~CEnemy()
{
	// 無し
}
//=========================================================
// 生成処理
//=========================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// インスタンス生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// オブジェクト設定
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetUseStencil(false);

	// ポインタ生成
	pEnemy->m_pParameter = std::make_unique<CParameter>();

	// nullチェック
	if (pEnemy->m_pParameter != nullptr)
	{
		pEnemy->m_pParameter->SetMaxHp(nLife);
		pEnemy->m_pParameter->SetHp(nLife);
	}

	// 初期化失敗時
	if (FAILED(pEnemy->Init())) return nullptr;

	return pEnemy;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CEnemy::Init(void)
{
	// キャラクタ―の初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_ENEMY);

	// モーションセット
	MotionLoad(EnemyInfo::MOTION_NAME, MOTION_MAX,true);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), EnemyInfo::HitRange);

	// 敵で使うAIノードをセットする
	// NodeSetting();

	// 拡大する
	// SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	// 有効化
	
	m_isDestQueen = true;
	//// ランダム数
	//int nRand = rand() % 2;

	//switch (nRand)
	//{
	//case 0:
	//	m_isDestQueen = true;
	//	break;

	//case 1:
	//	m_isDestFeed = true;
	//	break;

	//default:
	//	break;
	

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CEnemy::Uninit(void)
{
	// パラメータ終了処理
	m_pParameter.reset();

	// ステート終了処理
	m_pStateMachine.reset();

	// コライダー破棄
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// キャラクターの破棄
	CMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CEnemy::Update(void)
{
	// 未使用なら
	if (!m_isActive) return;

	// 座標取得
	D3DXVECTOR3 pos = GetPos();

#if 0
	//// ツリーの更新
	//m_pBehaviorTree->Update();
#endif

	// 餌移動
	if (m_isDestFeed) MoveToFeed();

	// 女王移動
	if (m_isDestQueen) MoveToQueen();

	// 座標のみの更新
	CMoveCharactor::UpdatePosition();

	// 更新後の座標
	D3DXVECTOR3 UpdatePos = GetPos();

	if (m_isDestFeed)
	{
		// 当たり判定関数
		CollisionFeed();
	}

	if (m_isDestQueen)
	{
		// 当たり判定関数
		CollisionQueen();
	}

	// 球更新
	if (m_pSphereCollider)
	m_pSphereCollider->SetPos(UpdatePos);

	// キャラクターの更新処理
	CMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CEnemy::Draw(void)
{
	// 未使用なら
	if (!m_isActive) return;

	// キャラクターの描画処理
	CMoveCharactor::Draw();
}

//=========================================================
// 餌に向かう処理
//=========================================================
void CEnemy::MoveToFeed(void)
{
	// 餌判定を有効化
	m_isDestFeed = true;

	// ターゲットが無い or 消えたら再取得
	if (!m_pTargetFeed || m_pTargetFeed->GetParam()->GetHp() <= 0)
	{
		if (!m_pTargetFeed) return;
		m_pTargetFeed = FindFeed();
	}

	// 目的地（XZのみ）
	D3DXVECTOR3 destPos = m_pTargetFeed->GetPos();
	destPos.y = 0.0f;

	D3DXVECTOR3 vec = destPos - GetPos();
	float dist = D3DXVec3Length(&vec);

	// 一定距離以内なら止まる
	if (dist < 10.0f)
	{
		SetMove(VECTOR3_NULL);
		GetMotion()->SetMotion(MOTION_NEUTRAL);
		return;
	}

	// 正規化して移動
	D3DXVec3Normalize(&vec, &vec);
	vec *= 1.0f; // 移動速度

	// 向き
	float angleY = atan2(-vec.x, -vec.z);
	D3DXVECTOR3 rot = GetRotDest();
	rot.y = NormalAngle(angleY);
	SetRotDest(rot);

	SetMove(vec);
	GetMotion()->SetMotion(MOTION_MOVE);
}
//=========================================================
// 仲間アリを攻撃する処理
//=========================================================
void CEnemy::AttackToAnt(void)
{

}
//=========================================================
// 女王アリを攻撃する処理
//=========================================================
void CEnemy::AttackToQueen(void)
{

}
//=========================================================
// 餌を奪う処理
//=========================================================
void CEnemy::RobToFeed(void)
{

}
//=========================================================
// 女王アリに向かう処理
//=========================================================
void CEnemy::MoveToQueen(void)
{
	// 対象を取得
	auto Queen = CGameSceneObject::GetInstance()->GetQueen();
	auto DestinationPos = D3DXVECTOR3(Queen->GetPos().x,0.0f,Queen->GetPos().z);

	D3DXVECTOR3 VecToQueen = DestinationPos - GetPos();
	float fDiff = D3DXVec3Length(&VecToQueen);

	if (fDiff > 10.0f)
	{
		// ベクトルを正規化
		D3DXVec3Normalize(&VecToQueen, &VecToQueen);
		VecToQueen *= 1.0f;

		// 角度設定
		float angleY = atan2(-VecToQueen.x, -VecToQueen.z);
		D3DXVECTOR3 rotDest = GetRotDest();
		rotDest.y = NormalAngle(angleY);

		// 目的角に設定
		SetRotDest(rotDest);

		// 移動量を設定
		SetMove(VecToQueen);

		// 移動モーションに変更
		GetMotion()->SetMotion(MOTION_MOVE);
	}
	else
	{
		SetMove(VECTOR3_NULL);
		GetMotion()->SetMotion(MOTION_NEUTRAL, true, 10);
	}
}
//=========================================================
// 餌を見つける処理
//=========================================================
CFeed* CEnemy::FindFeed(void)
{
	// 餌取得
	CFeedManager* pFeed = CGameSceneObject::GetInstance()->GetFeedManager();
	if (!pFeed || pFeed->GetSize() <= 0) return nullptr;

	// 最近点を生成
	CFeed* pNearest = nullptr;
	float minDist = FLT_MAX;

	// 座標取得
	D3DXVECTOR3 myPos = GetPos();

	for (int nCnt = 0; nCnt < pFeed->GetSize(); nCnt++)
	{
		CFeed* feed = pFeed->GetFeed(nCnt);
		if (!feed) continue;

		D3DXVECTOR3 diff = feed->GetPos() - myPos;
		float dist = D3DXVec3Length(&diff);

		if (dist < minDist)
		{
			minDist = dist;
			pNearest = feed;
		}
	}

	return pNearest;
}
//==========================================================
// 餌との当たり判定
//==========================================================
void CEnemy::CollisionFeed(void)
{
	// アリと餌の当たり判定
	CFeedManager* pFeed = CGameSceneObject::GetInstance()->GetFeedManager();

	// nullじゃないとき
	if (pFeed != nullptr)
	{
		// 配列取得
		for (int nCnt = 0; nCnt < pFeed->GetSize(); nCnt++)
		{
			// 変数格納
			auto feed = pFeed->GetFeed(nCnt);
			auto Collider = feed->GetCollider();

			// 当たっていたら
			if (Collision(Collider))
			{
				// 当たった対象物の体力値を減らす
				feed->DecLife(1);
				m_pTargetFeed = nullptr;

				// 自身の破棄
				Uninit();

				break;
			}
		}
	}
}
//==========================================================
// 女王との当たり判定
//==========================================================
void CEnemy::CollisionQueen(void)
{
	// 女王の取得
	auto Queen = CGameSceneObject::GetInstance()->GetQueen();
	auto Collider = Queen->GetCollider();

	// 有効時
	if (Collision(Collider))
	{
		// 対象オブジェクトの体力値を減算する
		Queen->Hit(3);

		// 自身の破棄
		Uninit();

		return;
	}
}

//==========================================================
// 状態変更処理
//==========================================================
void CEnemy::ChangeState(CEnemyStateBase* pNewState, int Id)
{
	// ステート変更
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}
//==========================================================
// 当たり判定処理
//==========================================================
bool CEnemy::Collision(CSphereCollider* pOther)
{
	// 球形同士の当たり判定
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}
//=========================================================
// ノード作成処理
//=========================================================
void CEnemy::NodeSetting(void)
{
	// 名前空間取得
	using namespace EnemyTree;

	// ブラックボード生成
	m_pBlackBoard = new CBlackBoard;

	// 自身の情報
	auto pos = GetPos();
	m_pBlackBoard->SetValue<D3DXVECTOR3>("EnemyPos", pos);
	m_pBlackBoard->SetValue<CEnemy*>("Enemy", this);

	// 防衛対象の情報
	auto Queen = CGameSceneObject::GetInstance()->GetQueen();
	m_pBlackBoard->SetValue<CQueen*>("Queen", Queen);
	m_pBlackBoard->SetValue<D3DXVECTOR3>("QueenPos", Queen->GetPos());

	// 餌の情報
	auto Feed = CGameSceneObject::GetInstance()->GetFeedManager();

	// 敵に使用するツリーノードにセットする
	m_pBehaviorTree = CEnemyBehaviorTree::SetEnemyTreeNode(m_pBlackBoard);
	m_pBehaviorTree->Init();
}