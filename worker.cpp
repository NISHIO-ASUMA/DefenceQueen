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
#include "template.h"
#include "numberpanel.h"

//=========================================================
// コンストラクタ
//=========================================================
CWorker::CWorker(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pSphereCollider(nullptr),
m_pStateMachine(nullptr),
m_pSelect(nullptr),
m_isMove(false),
m_isWork(false),
m_isCreate(false),
m_DestPos(VECTOR3_NULL),
m_nIdxNumber(NULL),
m_nScaleNum(NULL)
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
	pWorker->SetUseStencil(false);

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
	MotionLoad("data/MOTION/Work/Worker_Motion.txt", MOTION_MAX,true);

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), 60.0f);

	// モーションポインタ取得
	m_pMotion = CMoveCharactor::GetMotion();

	// ステートマシン生成
	//m_pStateMachine = std::make_unique<CStateMachine>();
	//ChangeState(new CWorkerStateNeutral, CWorkerStateBase::ID_NEUTRAL);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CWorker::Uninit(void)
{
	// ステートポインタ破棄
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
	// 有効なら
	if (m_isWork)
	{
		// 移動関数
		MoveToPoint();
	}

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
// 対象の座標に移動する関数
//=========================================================
void CWorker::MoveToPoint(void)
{
	// 現在の座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 目的から現在の座標までのベクトル
	D3DXVECTOR3 VecMove = m_DestPos - pos;
	float dist = D3DXVec3Length(&VecMove);

	// 距離が一定範囲外だったら
	if (dist > Config::Distance)
	{
		// 正規化
		D3DXVec3Normalize(&VecMove, &VecMove);

		// 速度を乗算する
		VecMove *= 5.0f;

		// 計算角度
		float angleY = atan2(-VecMove.x, -VecMove.z);
		D3DXVECTOR3 rotDest = GetRotDest();
		rotDest.y = angleY;

		// 正規化する
		rotDest.y = NormalAngle(rotDest.y);

		// 目的角を更新
		SetRotDest(rotDest);

		// 移動量をセット
		SetMove(VecMove);

		// 移動モーションに変更
		GetMotion()->SetMotion(CWorker::MOTION_MOVE);
	}
	else
	{
		// 待機モーションに変更
		GetMotion()->SetMotion(CWorker::MOTION_NEUTRAL);

		// ランダム値
		int nrand = rand() % 3;

		if (!m_isCreate)
		{
			// パネル生成
			CNumberPanel::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 200.0f, GetPos().z), D3DXVECTOR3(0.0f,0.0f,0.0f), nrand);

			// セットする
			SetNeedNumber(nrand);
			
			// フラグを有効化
			m_isCreate = true;
		}
	}
}

//=========================================================
// 球の当たり判定処理
//=========================================================
bool CWorker::Collision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}
//=========================================================
// 状態切り替え関数
//=========================================================
void CWorker::ChangeState(CWorkerStateBase* pState, int nId)
{
	// 自分自身を代入
	pState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pState);
}
//=========================================================
// プレイヤー側に通知する数を返す関数
//=========================================================
int CWorker::RequiredNumber(void)
{
	// インデックスに応じて変更
	switch (m_nIdxNumber)
	{
	case NUMARRAY_LITTLE: // 最小値
		m_nScaleNum = Config::LITTLE;
		break;

	case NUMARRAY_MIDDLE: // 中間値
		m_nScaleNum = Config::MIDDLE;
		break;

	case NUMARRAY_LARGE: // 最大値
		m_nScaleNum = Config::LARGE;
		break;

	default:
		m_nScaleNum = NULL;
		break;
	}
	
	// 取得する値を返す
	return m_nScaleNum;
}