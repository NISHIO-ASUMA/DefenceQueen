//===========================================
//
// 司令塔キャラクターの処理 [ order.cpp ]
// Author: Asuma Nishio
//
//===========================================

//************************
// インクルードファイル
//************************
#include "order.h"
#include "motion.h"
#include "statemachine.h"
#include "spherecollider.h"
#include "collisionsphere.h"

//************************
// 定数空間
//************************
namespace ORDERINFO
{

};

//======================================
// コンストラクタ
//======================================
COrder::COrder(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pSphereCollider(nullptr),
m_pStateMachine(nullptr)
{
	// 値のクリア
}
//======================================
// デストラクタ
//======================================
COrder::~COrder()
{
	// 無し
}
//======================================
// 生成処理
//======================================
COrder* COrder::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// インスタンス生成
	COrder* pOrder = new COrder;
	if (pOrder == nullptr) return nullptr;

	// オブジェクト設定
	pOrder->SetPos(pos);
	pOrder->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pOrder->Init())) return nullptr;

	return pOrder;
}
//======================================
// 初期化処理
//======================================
HRESULT COrder::Init(void)
{
	// 親クラスの初期化
	CMoveCharactor::Init();

	// オブジェクトの種類セット
	CObject::SetObjType(TYPE_ORDER);

	// モーションロード
	MotionLoad("data/MOTION/Order/Order.txt", MOTION_MAX);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// 初期状態をセット
	// ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(),60.0f);

	// モーション取得
	m_pMotion = CMoveCharactor::GetMotion();

	return S_OK;
}
//======================================
// 終了処理
//======================================
void COrder::Uninit(void)
{
	// ステート終了処理
	m_pStateMachine.reset();

	// コライダー破棄
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// 親クラスの終了処理
	CMoveCharactor::Uninit();
}
//======================================
// 更新処理
//======================================
void COrder::Update(void)
{
	// 現在の座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 座標の更新
	CMoveCharactor::UpdatePosition();

	// 更新後の座標を取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// コライダー座標の更新
	m_pSphereCollider->SetPos(UpdatePos);

	// コリジョン処理
	
	// 親クラスの更新
	CMoveCharactor::Update();
}
//======================================
// 描画処理
//======================================
void COrder::Draw(void)
{
	// 親クラスの描画
	CMoveCharactor::Draw();
}
//======================================
// 当たり判定処理
//======================================
bool COrder::Collision(CSphereCollider* other)
{
	// 球形の当たり判定
	return CCollisionSphere::Collision(m_pSphereCollider, other);
}