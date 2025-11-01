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

//===============================
// コンストラクタ
//===============================
CEnemy::CEnemy(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pSphereCollider(nullptr)
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
	// キャラクタ―の初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_ENEMY);

	// モーションセット
	MotionLoad("data/MOTION/Enemy/EnemyMotion.txt", MOTION_MAX);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// 初期状態をセット
	// ChangeState(new CEnemyStateNeutral, CEnemyStateBase::ID_NEUTRAL);

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), 60.0f);

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

	// 状態管理更新
	if (m_pStateMachine != nullptr) m_pStateMachine->Update();

	// 座標のみの更新
	CMoveCharactor::UpdatePosition();

	// 球の座標更新
	if (m_pSphereCollider) m_pSphereCollider->SetPos(pos);

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