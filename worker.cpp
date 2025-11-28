//=========================================================
//
// 指示を出す働きアリの処理 [ worker.cpp ]
// Author: Asuma Nishio
// 
// TODO : ステート入れる
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "worker.h"
#include "spherecollider.h"
#include "collisionsphere.h"
#include "motion.h"
#include "statemachine.h"
#include "gamesceneobject.h"
#include "selectpoint.h"
#include "workerstateneutral.h"

//=========================================================
// コンストラクタ
//=========================================================
CWorker::CWorker(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pSphereCollider(nullptr),
m_pStateMachine(nullptr),
m_pSelect(nullptr),
m_isMove(false),
m_isWork(false)
{

}
//=========================================================
// デストラクタ
//=========================================================
CWorker::~CWorker()
{

}
//=========================================================
// 生成処理
//=========================================================
CWorker* CWorker::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// インスタンス生成
	CWorker* pWorker = new CWorker;
	if (pWorker == nullptr) return nullptr;

	// オブジェクト設定
	pWorker->SetPos(pos);
	pWorker->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pWorker->Init())) return nullptr;

	return pWorker;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CWorker::Init(void)
{
	// 親クラスの初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_WORKER);

	// モーションセット
	MotionLoad("data/MOTION/Worker/Worker.txt", MOTION_MAX);

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), 60.0f);

	// モーションポインタ取得
	m_pMotion = CMoveCharactor::GetMotion();

	// ステートマシン生成
	
	// ゲームオブジェクトから選択ポイントを取得
	// m_pSelect = CGameSceneObject::GetInstance()->GetPoint();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CWorker::Uninit(void)
{
	// ポインタ破棄
	m_pStateMachine.reset();

	// ポインタ破棄
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// 親クラスの終了
	CMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CWorker::Update(void)
{
	// 現在のキャラクター座標を取得
	D3DXVECTOR3 pos = GetPos();

	// キャラクターの座標更新
	CMoveCharactor::UpdatePosition();

	// 更新後の座標を取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// コライダー座標の更新
	if (m_pSphereCollider) m_pSphereCollider->SetPos(UpdatePos);

	// キャラクター全体の更新処理
	CMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CWorker::Draw(void)
{
	// キャラクター描画
	CMoveCharactor::Draw();
}
//=========================================================
// 球の当たり判定処理
//=========================================================
bool CWorker::Collision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}