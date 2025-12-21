//=========================================================
//
// 防衛対象アリの処理 [ queen.cpp ]
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
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//=========================================================
// コンストラクタ
//=========================================================
CQueen::CQueen(int nPriority) : CNoMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_isUse(false)
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
CQueen* CQueen::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// インスタンス生成
	CQueen* pQueen = new CQueen;
	if (pQueen == nullptr) return nullptr;

	// オブジェクト設定
	pQueen->SetPos(pos);
	pQueen->SetRot(rot);
	pQueen->SetUseStencil(false);
	pQueen->SetUseOutLine(true);

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
	MotionLoad(QueenInfo::SCRIPT, MOTION_MAX,true);

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

	// 使用する
	SetIsUse(true);

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
	// 未使用なら
	if (!m_isUse) return;

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
	// 未使用なら
	if (!m_isUse) return;

	// 親クラスの描画
	CNoMoveCharactor::Draw();

#ifdef _DEBUG

	// デバッグ表示
	CDebugproc::Print("女王の体力値 [ %d / 100 ]", m_pParameter->GetHp());
	CDebugproc::Draw(0, 340);

#endif // _DEBUG
}
//=========================================================
// ダメージ処理
//=========================================================
void CQueen::Hit(const int& nDamage)
{
	// 体力値を減らす
	int nHp = m_pParameter->GetHp();
	nHp -= nDamage;

	if (nHp <= NULL)
	{
		// 体力を0にする
		m_pParameter->SetHp(NULL);

		// フラグをセット
		SetIsUse(false);

		// 処理終了
		return;
	}

	// 現在の体力値をセット
	m_pParameter->SetHp(nHp);
}
//=========================================================
// 当たり判定処理
//=========================================================
bool CQueen::Collision(CSphereCollider* pOther)
{
	// 球同士の当たり判定を返す
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}