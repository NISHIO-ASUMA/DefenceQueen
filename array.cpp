//=========================================================
//
// プレイヤーの仲間処理 [ array.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "array.h"
#include "parameter.h"
#include "manager.h"
#include "spherecollider.h"
#include "collisionsphere.h"
#include "statemachine.h"
#include "state.h"
#include "blackboard.h"
#include "boxcollider.h"
#include "collisionbox.h"
#include "arraymanager.h"
#include "gamesceneobject.h"

//=========================================================
// コンストラクタ
//=========================================================
CArray::CArray(int nPriority) : CMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr),
m_isActive(false)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CArray::~CArray()
{

}
//=========================================================
// 生成処理
//=========================================================
CArray* CArray::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife)
{
	// インスタンス生成
	CArray* pArray = new CArray;
	if (pArray == nullptr) return nullptr;

	// オブジェクト設定
	pArray->SetPos(pos);
	pArray->SetRot(rot);
	pArray->SetUseStencil(false);
	pArray->m_pParameter = std::make_unique<CParameter>();

	// nullチェック
	if (pArray->m_pParameter)
	{
		// 体力パラメーターを設定
		pArray->m_pParameter->SetHp(nLife);
		pArray->m_pParameter->SetMaxHp(nLife);
	}

	// 初期化処理
	if (FAILED(pArray->Init())) return nullptr;

	return pArray;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CArray::Init(void)
{
	// 親クラスの初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_ARRAY);

	// モーションセット
	MotionLoad("data/MOTION/Array/Array_Motion.txt", MOTION_MAX,true);

	// スフィアコライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), Arrayinfo::SphereRange);

	// モーション取得
	m_pMotion = CMoveCharactor::GetMotion();

	// ノード生成
	m_pBlackBoard = new CBlackBoard;
	m_pBlackBoard->SetValue<CArray*>("Array",this);

	m_isActive = false;

	// 拡大する
	SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CArray::Uninit(void)
{
	// パラメーター終了処理
	m_pParameter.reset();

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
void CArray::Update(void)
{
	// falseなら通さない
	if (!m_isActive) return;

	// 座標のみの更新処理
	CMoveCharactor::UpdatePosition();

	// 座標取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// コライダー座標の更新
	m_pSphereCollider->SetPos(UpdatePos);

#if 0
	// アリ同士の当たり判定
	for (int i = 0; i < arrayall; i++)
	{
		// ポインタ取得
		CArray* pOther = CGameSceneObject::GetInstance()->GetArrayManager()->GetArrays(i);

		// 自分自身 or 非アクティブは無視
		if (pOther == this || !pOther->GetActive()) continue;

		// 距離を計算
		D3DXVECTOR3 posA = UpdatePos;
		D3DXVECTOR3 posB = pOther->GetPos();

		D3DXVECTOR3 diff = posA - posB;
		float dist = D3DXVec3Length(&diff);

		float r = m_pSphereCollider->GetRadius() + pOther->m_pSphereCollider->GetRadius();
		float pushDist = r - dist;

		if (pushDist > 0.0f) // 重なってる
		{
			// 正規化
			D3DXVec3Normalize(&diff, &diff);

			// 押し出し量
			diff *= (pushDist * 0.5f); // お互いに半分ずつ押し出す

			// 新しい位置を適用
			posA += diff;
			posB -= diff;

			SetPos(posA); // 自分の位置更新
			pOther->SetPos(posB); // 相手の位置更新
		}
	}
#endif

	// 体力がなくなった
	if (m_pParameter && m_pParameter->GetHp() <= NULL)
	{
		// 体力を0にする
		m_pParameter->SetHp(NULL);

		// 消さずに未使用にする
		SetActive(false);

		// 下の処理を通さない
		return;
	}

	// キャラクターの更新
	CMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CArray::Draw(void)
{
	// falseなら通さない
	if (!m_isActive) return;

	// キャラクターの描画
	CMoveCharactor::Draw();
}
//=========================================================
// パラメータ再設定処理
//=========================================================
void CArray::Reset(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nLife)
{
	// 再設定用のパラメーター
	SetPos(pos);
	SetRot(rot);
	SetActive(true);

	// 体力値を設定
	if (m_pParameter)
	{
		m_pParameter->SetMaxHp(nLife);
		m_pParameter->SetHp(nLife);
	}

	// ノードに改めてセットする
	if (m_pBlackBoard)
	{
		// 一時クリア
		m_pBlackBoard->Clear();

		// 自身の情報をセットする
		m_pBlackBoard->SetValue<CArray*>("Array", this);
	}
}
//=========================================================
// 球の当たり判定処理
//=========================================================
bool CArray::Colision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}