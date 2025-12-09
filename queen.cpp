//=========================================================
//
// 防衛対象の処理 [ queen.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "queen.h"
#include "collisionsphere.h"
#include "spherecollider.h"
#include "parameter.h"
#include "statemachine.h"

//=========================================================
// コンストラクタ
//=========================================================
CQueen::CQueen(int nPriority) : CNoMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CQueen::~CQueen()
{

}
//=========================================================
// 生成処理
//=========================================================
CQueen* CQueen::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成
	CQueen* pQueen = new CQueen;
	if (pQueen == nullptr) return nullptr;

	// オブジェクト設定
	pQueen->SetPos(pos);
	pQueen->SetRot(rot);
	pQueen->SetUseStencil(false);

	// 初期化失敗時
	if (FAILED(pQueen->Init())) return nullptr;

	// 生成されたポインタ
	return pQueen;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CQueen::Init(void)
{
	// 親クラスの初期化
	CNoMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_QUEEN);

	// モーションセット
	MotionLoad("data/MOTION/Queen/Queen_Motion.txt", MOTION_MAX,true);

	// パラメーター生成
	m_pParameter = std::make_unique<CParameter>();
	m_pParameter->SetMaxHp(QueenInfo::Hp);
	m_pParameter->SetHp(QueenInfo::Hp);

	//// ステートマシンを生成
	//m_pStateMachine = std::make_unique<CStateMachine>();

	//// 初期状態をセット
	//// ChangeState(ID_NEUTRAL);

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), QueenInfo::HitRange);

	// モーション取得
	m_pMotion = CNoMoveCharactor::GetMotion();

	// 拡大する
	SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CQueen::Uninit(void)
{
	// ポインタ破棄
	m_pParameter.reset();

	// ステート終了処理
	// m_pStateMachine.reset();

	// コライダー破棄
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// 親クラスの終了処理
	CNoMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CQueen::Update(void)
{
	// 現在座標を取得
	D3DXVECTOR3 pos = GetPos();

	// コライダーの位置更新
	m_pSphereCollider->SetPos(pos);

	// 親クラスの更新
	CNoMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CQueen::Draw(void)
{
	// 親クラスの描画
	CNoMoveCharactor::Draw();
}
//=========================================================
// 当たり判定処理
//=========================================================
bool CQueen::Collision(CSphereCollider* pOther)
{
	// 球同士の当たり判定を返す
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}