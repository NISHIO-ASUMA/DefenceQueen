//=========================================================
//
// プレイヤーの仲間アリ1匹に対する処理 [ array.cpp ]
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
#include "topant.h"
#include "player.h"
#include "separationant.h"
#include "feedmanager.h"
#include "feed.h"
#include "arraybehaviortree.h"
#include "node.h"
#include "blackboard.h"

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
m_isActive(false),
m_isMove(false),
m_isTopAntFollow(false),
m_isReturn(false),
m_isAtBase(true),
m_isStop(false),
m_MoveDestPos(VECTOR3_NULL),
m_nListGroupId(NULL)
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

	// ノードセット
	// NodeSetting();

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

	// 巣にもどる状態が有効時
	if (m_isReturn)
	{
		SpawnReturn();
	}

	// 移動する関数
	FollowDestination(m_MoveDestPos);

	// 座標のみの更新処理
	CMoveCharactor::UpdatePosition();

	// 座標取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// コライダー座標の更新
	m_pSphereCollider->SetPos(UpdatePos);

	// アリと餌の当たり判定
	CFeedManager* pFeed = CGameSceneObject::GetInstance()->GetFeedManager();

	// nullじゃないとき
	if (pFeed != nullptr)
	{
		// 配列取得
		for (int nCnt = 0; nCnt < pFeed->GetSize(); nCnt++)
		{
			// 変数格納
			auto feed = pFeed->GetFeed(nCnt);
			auto Collider = feed->GetCollider();

			// 当たっていたら
			if (Colision(Collider))
			{
				// 当たった対象物の体力値を減らす
				feed->DecLife(1);

				// コライダーの更新と指示変更
				m_pSphereCollider->SetPos(UpdatePos);

				// 基地に帰る
				this->OnSeparation();

				break;
			}
		}
	}

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

	//// ノードに改めてセットする
	//if (m_pBlackBoard)
	//{
	//	// 一時クリア
	//	m_pBlackBoard->Clear();

	//	// 自身の情報をセットする
	//	m_pBlackBoard->SetValue<CArray*>("Array", this);
	//}
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
// 切り離される処理 TODO : ここでノード見る
//=========================================================
void CArray::OnSeparation(void)
{
	// 移動フラグを無効化
	SetIsMove(false);

	// 帰還モードにする
	SetReturnSpawn(true);
}

//=========================================================
// ある一定の目標地点に向かう処理
//=========================================================
void CArray::FollowDestination(const D3DXVECTOR3& DestPos)
{
	// もし移動時状態じゃなかったら
	if (!m_isMove) return;

	// 目的地までの距離を算出
	D3DXVECTOR3 moveVec = DestPos - GetPos();
	float distToDest = D3DXVec3Length(&moveVec);

	// 目的地が近いなら隊列を切って直接目的地へ
	if (distToDest < Arrayinfo::PRIORITY_DISTANCE)
	{
		// 隊列フォロー解除
		m_pFollowTarget = nullptr;

		// 到着したら止まる
		if (distToDest < Arrayinfo::STOP_DISTANCE)
		{
			SetMove(VECTOR3_NULL);

			m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);

			// フラグを有効化
			m_isMove = false;
			m_isStop = true;

			return;
		}

		// 目的地へ直接移動
		D3DXVec3Normalize(&moveVec, &moveVec);
		moveVec *= Arrayinfo::MoveSpeed;

		float fAngle = atan2(-moveVec.x, -moveVec.z);
		D3DXVECTOR3 Rotdest = GetRotDest();

		// 正規化
		Rotdest.y = NormalAngle(fAngle);

		// 値をセット
		SetRotDest(Rotdest);

		// 移動量を加算
		SetMove(moveVec);

		// 移動モーションにセット
		m_pMotion->SetMotion(CArray::MOTION_MOVE);

		return;
	}

	// 隊列を形成する
	if (m_pFollowTarget)
	{
		ArrayFollow();
		return;
	}

	// 単独で目的に向かう
	D3DXVec3Normalize(&moveVec, &moveVec);
	moveVec *= Arrayinfo::MoveSpeed;

	float angle = atan2(-moveVec.x, -moveVec.z);
	D3DXVECTOR3 rotdest = GetRotDest();
	rotdest.y = NormalAngle(angle);
	SetRotDest(rotdest);

	SetMove(moveVec);

	m_pMotion->SetMotion(CArray::MOTION_MOVE);
}


//=========================================================
// 仲間を追従する
//=========================================================
void CArray::ArrayFollow(void)
{
	// 無かったら
	if (!m_isReturn && !m_pFollowTarget) return;

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
// 巣にもどる命令を受けたときの移動
// NOTE : 設置されているランダムなスポーンに行くように変更 これは冬休みか?
//=========================================================
void CArray::SpawnReturn(void)
{
	// ターゲット座標を取得
	auto idx = CGameSceneObject::GetInstance()->GetPlayer()->GetSelectIndex();
	auto targetPos = CGameSceneObject::GetInstance()->GetArraySpawn()->GetIndexSpawner(idx)->GetPos();

	D3DXVECTOR3 followVec = targetPos - GetPos();
	float fDistance = D3DXVec3Length(&followVec);

	if (fDistance > 10.0f)
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

		// 待機させる
		m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);

		// 基地についたのでReturnモード解除
		SetReturnSpawn(false);

		// 基地到着
		SetAtBase(true);

		// リセット
		m_isMove = false;
		m_pFollowTarget = nullptr;
		SetPrevAnt(nullptr);
		SetIsStop(false);

		// この時にグループの要素をクリアする
		CGameSceneObject::GetInstance()->GetArraySpawn()->GetIndexSpawner(idx)->GetSeparationAnt()->ClearListGroup(m_nListGroupId, this);
	}
}
//=========================================================
// ノードを設定する
//=========================================================
void CArray::NodeSetting(void)
{
	// 名前空間取得
	using namespace ArrayTree;

	// ブラックボード生成
	m_pBlackBoard = new CBlackBoard;

	// ブラックボードに情報をセットする
	auto pos = GetPos();
	m_pBlackBoard->SetValue<CArray*>("Array", this);			// 自身
	m_pBlackBoard->SetValue<D3DXVECTOR3>("ArrayPos", pos);		// 自身の座標
	m_pBlackBoard->SetValue<D3DXVECTOR3>("ArrayDestPos", m_MoveDestPos); // 目的座標
	m_pBlackBoard->SetValue<bool>("ReturnSpawn", m_isReturn);	// 基地に帰るフラグ

	// 仲間に使用するツリーノードにセットする
	//m_pBehaviorTree = CArrayBehaviorTree::SetArrayTreeNode(m_pBlackBoard);
	//m_pBehaviorTree->Init();

}
//=========================================================
// 球の当たり判定処理
//=========================================================
bool CArray::Colision(CSphereCollider* other)
{
	// 球同士の当たり判定の関数を返す
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}