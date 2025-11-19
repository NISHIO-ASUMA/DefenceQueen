//=====================================
//
// 敵の処理 [ enemy.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
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

//===============================
// コンストラクタ
//===============================
CEnemy::CEnemy(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pSphereCollider(nullptr),
m_pBehaviorTree(nullptr),
m_pSelect(nullptr),
m_pBlackBoard(nullptr)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CEnemy::~CEnemy()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// インスタンス生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// オブジェクト設定
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);

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
//===============================
// 初期化処理
//===============================
HRESULT CEnemy::Init(void)
{
	// 名前空間宣言
	using namespace EnemyTree;

	// キャラクタ―の初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_ENEMY);

	// モーションセット
	MotionLoad("data/MOTION/Enemy/EnemyMotion.txt", MOTION_MAX);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), 60.0f);

	// ブラックボード生成
	m_pBlackBoard = new CBlackBoard;

	// ブラックボードに情報をセットする
	auto pos = GetPos();
	m_pBlackBoard->SetValue<D3DXVECTOR3>("EnemyPos", pos);
	m_pBlackBoard->SetValue<CEnemy*>("Enemy", this);

	// 対象座標を取得
	m_pSelect = CGameSceneObject::GetInstance()->GetPoint();
	m_pBlackBoard->SetValue<CSelectPoint*>("Selector", m_pSelect);

	auto Select = CGameSceneObject::GetInstance()->GetPoint();
	m_pBlackBoard->SetValue("SelectorPos", Select->GetPos());

	// ツリーノードにセットする
	m_pBehaviorTree = CEnemyBehaviorTree::SetEnemyTreeNode(m_pBlackBoard);
	m_pBehaviorTree->Init();

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
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

	// ノードクラスツリーの破棄
	if (m_pBehaviorTree)
	{
		m_pBehaviorTree->Exit();
		delete m_pBehaviorTree;
		m_pBehaviorTree = nullptr;
	}

	// ブラックボードポインタの破棄
	if (m_pBlackBoard)
	{
		delete m_pBlackBoard;
		m_pBlackBoard = nullptr;
	}

	// キャラクターの破棄
	CMoveCharactor::Uninit();
}
//===============================
// 更新処理
//===============================
void CEnemy::Update(void)
{
	// 座標取得
	D3DXVECTOR3 pos = GetPos();

	// 更新されている座標を取得
	auto Select = CGameSceneObject::GetInstance()->GetPoint();
	m_pBlackBoard->SetValue("SelectorPos", Select->GetPos());

	// ツリーの更新
	m_pBehaviorTree->Update();

	// 座標のみの更新
	CMoveCharactor::UpdatePosition();

	// 更新後の座標
	D3DXVECTOR3 UpdatePos = GetPos();

	// 球の座標更新
	if (m_pSphereCollider) m_pSphereCollider->SetPos(UpdatePos);

	// キャラクターの更新処理
	CMoveCharactor::Update();
}
//===============================
// 描画処理
//===============================
void CEnemy::Draw(void)
{
	// キャラクターの描画処理
	CMoveCharactor::Draw();

	// デバッグフォント
	CDebugproc::Print("座標 : %.2f,%.2f,%.2f", GetPos().x, GetPos().y, GetPos().z);
	CDebugproc::Draw(0, 140);
}
//================================
// 状態変更処理
//================================
void CEnemy::ChangeState(CEnemyStateBase* pNewState, int Id)
{
	// ステート変更
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}
//================================
// 当たり判定処理
//================================
bool CEnemy::Collision(CSphereCollider* pOther)
{
	// 球形同士の当たり判定
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}