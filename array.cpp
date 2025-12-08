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
#include "template.h"
#include "arrayspawnmanager.h"
#include "arrayspawner.h"
#include "player.h"
#include "topant.h"

//=========================================================
// コンストラクタ
//=========================================================
CArray::CArray(int nPriority) : CMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr),
m_pFollowTarget(nullptr),
m_pFollowTargetTop(nullptr),
m_isActive(false),
m_isMove(false),
m_isTopAntFollow(false),
m_MoveDestPos(VECTOR3_NULL)
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

	// フラグ初期化
	m_isActive = false;
	m_isMove = false;

	// 拡大する
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

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

	// 移動させるなら
	// if (m_isMove) Moving();

	// 先頭に追従設定があるなら
	if (m_pFollowTargetTop && m_isMove)
	{
		TopAntFollow();
	}
	else if (m_pFollowTarget && m_isMove)
	{
		ArrayFollow();		// 仲間アリ追従
	}

	// 座標のみの更新処理
	CMoveCharactor::UpdatePosition();

	// 座標取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// コライダー座標の更新
	m_pSphereCollider->SetPos(UpdatePos);

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
// 指定のポイントに移動する関数
//=========================================================
void CArray::Moving(void)
{
	// 進行方向への方向ベクトルを作成
	D3DXVECTOR3 movevec = m_MoveDestPos - GetPos();
	float fDis = D3DXVec3Length(&movevec);

	// 範囲外なら移動する
	if (fDis > 60.0f)
	{
		// 正規化
		D3DXVec3Normalize(&movevec, &movevec);

		// 速度を乗算する
		movevec *= Arrayinfo::MoveSpeed;

		// 計算角度
		float angleY = atan2(-movevec.x, -movevec.z);
		D3DXVECTOR3 rotDest = CMoveCharactor::GetRotDest();
		rotDest.y = angleY;

		// 正規化する
		rotDest.y = NormalAngle(rotDest.y);

		// 目的角を更新
		CMoveCharactor::SetRotDest(rotDest);

		// 移動量をセット
		CMoveCharactor::SetMove(movevec);

		// モーション変更
		m_pMotion->SetMotion(CArray::MOTION_MOVE);
	}
	else
	{
		// 固定
		SetMove(VECTOR3_NULL);

		// モーション変更
		m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);
	}
}
//=========================================================
// スポナーの先頭アリに追従する処理
//=========================================================
void CArray::TopAntFollow(void)
{
	if (!m_pFollowTargetTop) return;

	// 追従対象の座標
	D3DXVECTOR3 targetPos = m_pFollowTargetTop->GetPos();

	// 自分との差分
	D3DXVECTOR3 followVec = targetPos - GetPos();
	float fDistance = D3DXVec3Length(&followVec);

	if (fDistance > Arrayinfo::TOP_DISTANCE)
	{
		// 正規化
		D3DXVec3Normalize(&followVec, &followVec);

		// 移動速度
		followVec *= Arrayinfo::MoveSpeed;

		// 向き調整
		float angleY = atan2(-followVec.x, -followVec.z);
		D3DXVECTOR3 rotDest = GetRotDest();
		rotDest.y = NormalAngle(angleY);
		SetRotDest(rotDest);

		// 移動設定
		SetMove(followVec);

		// モーション変更
		m_pMotion->SetMotion(CArray::MOTION_MOVE);
	}
	else
	{
		SetMove(VECTOR3_NULL);
		m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);
	}
}
//=========================================================
// 仲間を追従する
//=========================================================
void CArray::ArrayFollow(void)
{
	// ターゲット座標を取得
	D3DXVECTOR3 targetPos = m_pFollowTarget->GetPos();
	D3DXVECTOR3 followVec = targetPos - GetPos();
	float fDistance = D3DXVec3Length(&followVec);

	if (fDistance > Arrayinfo::ARRAY_DISTANCE)
	{
		// ベクトルを正規化
		D3DXVec3Normalize(&followVec, &followVec);
		followVec *= Arrayinfo::MoveSpeed;

		// 角度設定
		float angleY = atan2(-followVec.x, -followVec.z);
		D3DXVECTOR3 rotDest = GetRotDest();
		rotDest.y = NormalAngle(angleY);

		// 目的角に設定
		SetRotDest(rotDest);

		// 移動量を設定
		SetMove(followVec);

		// 移動モーションに変更
		m_pMotion->SetMotion(CArray::MOTION_MOVE);
	}
	else
	{
		// 停止
		SetMove(VECTOR3_NULL);

		// ニュートラルモーションに変更
		m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);
	}
}
//=========================================================
// 球の当たり判定処理
//=========================================================
bool CArray::Colision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}