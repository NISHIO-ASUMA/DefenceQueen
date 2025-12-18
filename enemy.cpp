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

//*********************************************************
// 定数宣言空間
//*********************************************************
namespace EnemyInfo
{
	constexpr float HitRange = 80.0f; // 球形範囲
};

//=========================================================
// コンストラクタ
//=========================================================
CEnemy::CEnemy(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pSphereCollider(nullptr),
m_isActive(false)
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

	// 敵のポインタを返す
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
	MotionLoad("data/MOTION/Enemy/Enemy_Motion.txt", MOTION_MAX,true);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), EnemyInfo::HitRange);

	// 敵で使うAIノードをセットする
	// NodeSetting();

	// 拡大する
	// SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	m_isActive = true;

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

#ifdef _DEBUG

	// 女王に移動する
	MoveToQueen();

#endif // _DEBUG


	// 座標のみの更新
	CMoveCharactor::UpdatePosition();

	// 更新後の座標
	D3DXVECTOR3 UpdatePos = GetPos();

	// 餌との当たり判定 TODO : これに関しては餌に向かっていくものだけが判定するべき
	
	// 球の座標更新
	if (m_pSphereCollider) m_pSphereCollider->SetPos(UpdatePos);

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

	float fRadius = Queen->GetCollider()->GetRadius();
	D3DXVECTOR3 VecToQueen = DestinationPos - GetPos();
	float fDiff = D3DXVec3Length(&VecToQueen);

	if (fDiff > fRadius)
	{
		// ベクトルを正規化
		D3DXVec3Normalize(&VecToQueen, &VecToQueen);
		VecToQueen *= 1.5f;

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