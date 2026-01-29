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
#include "score.h"
#include "enemymanager.h"
#include "enemy.h"
#include "motioninstancing.h"
#include "basemapfeed.h"

//=========================================================
// コンストラクタ
//=========================================================
CArray::CArray(int nPriority) : CInstancingCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pBoxCollider(nullptr),
m_pFollowTarget(nullptr),
m_pTopAnt(nullptr),
m_isActive(false),
m_isMove(false),
m_isTopAntFollow(false),
m_isReturn(false),
m_isAtBase(true),
m_isStop(false),
m_isCheckNearFeed(false),
m_isAttackMode(false),
m_isGettingTopOrder(false),
m_isSetPoint(false),
m_MoveDestPos(VECTOR3_NULL),
m_ActivePos(VECTOR3_NULL),
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
	pArray->m_ActivePos = pos;

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
	CInstancingCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_ARRAY);

	// モーションセット
	MotionLoad(Arrayinfo::SCRIPT, MOTION_MAX,true);

	// スフィアコライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), Arrayinfo::SphereRange);

	// モーション取得
	m_pMotion = CInstancingCharactor::GetMotion();

	// フラグ初期化
	m_isActive = false;
	m_isMove = false;

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

	// ビヘイビアツリーの破棄
	if (m_pBehaviorTree)
	{
		m_pBehaviorTree->Exit();
		delete m_pBehaviorTree;
		m_pBehaviorTree = nullptr;
	}

	// ブラックボードの破棄
	if (m_pBlackBoard)
	{
		m_pBlackBoard->Clear();
		delete m_pBlackBoard;
		m_pBlackBoard = nullptr;
	}

	// キャラクターの破棄
	CInstancingCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CArray::Update(void)
{
	// falseなら通さない
	if (!m_isActive) return;
	
	// ボードの毎フレーム更新
	SyncBlackBoard();

	// ツリーノードの更新処理
	m_pBehaviorTree->Update();

	// 座標のみの更新
	CInstancingCharactor::UpdatePosition();

	// 更新座標の取得
	auto UpdatePos = GetPos();

	// コライダー座標の更新
	m_pSphereCollider->SetPos(UpdatePos);

	// 全判定関数
	CollsionAll(UpdatePos);

	// キャラクターの更新
	CInstancingCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CArray::Draw(void)
{
	// キャラクターの描画
	CInstancingCharactor::Draw();
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
		D3DXVECTOR3 rotDest = CInstancingCharactor::GetRotDest();
		rotDest.y = angleY;

		// 正規化する
		rotDest.y = NormalAngle(rotDest.y);

		// 目的角を更新
		CInstancingCharactor::SetRotDest(rotDest);

		// 移動量をセット
		CInstancingCharactor::SetMove(movevec);

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
// 切り離される処理
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
	// 命令フラグが有効なら
	if (m_isGettingTopOrder)
	{
		// 追従切り替え
		FollowTop(m_pBlackBoard->GetValue<D3DXVECTOR3>("TopPos"));
		return;
	}

	// 目的地までの距離を算出
	D3DXVECTOR3 moveVec = DestPos - GetPos();
	float distToDest = D3DXVec3Length(&moveVec);

	// 目的地が近いなら隊列を切って直接目的地へ
	if (distToDest < Arrayinfo::ARRAY_DISTANCE)
	{
		// 基地判定がtrueなら
		if (m_isAtBase)
		{
			m_isAtBase = false;
		}

		// 到着したら止まる
		if (distToDest < Arrayinfo::STOP_DISTANCE)
		{
			// 待機モーションに設定
			m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);

			// フラグを有効化
			m_isStop = true;

			// ブラックボードを更新する
			if (!m_isCheckNearFeed)
			{
				m_isCheckNearFeed = true;
				m_pBlackBoard->SetValue("CheckNearFeed", m_isCheckNearFeed);
			}

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

	// 単独で目的に向かう
	D3DXVec3Normalize(&moveVec, &moveVec);
	moveVec *= Arrayinfo::MoveSpeed;

	float angle = atan2(-moveVec.x, -moveVec.z);
	D3DXVECTOR3 rotdest = GetRotDest();
	rotdest.y = NormalAngle(angle);
	SetRotDest(rotdest);

	// キャラクターの移動量に設定
	SetMove(moveVec);

	// 移動モーションに設定
	m_pMotion->SetMotion(CArray::MOTION_MOVE);
}

//=========================================================
// トップのアリを追従する関数
//=========================================================
void CArray::FollowTop(D3DXVECTOR3 vpos)
{
	// 目的地までの距離を算出
	D3DXVECTOR3 moveVec = vpos - GetPos();
	float distToDest = D3DXVec3Length(&moveVec);

	// 到着したら止まる
	if (distToDest < Arrayinfo::TOP_DISTANCE)
	{
		// 移動量を0にする
		SetMove(VECTOR3_NULL);

		// 待機モーションに設定
		m_pMotion->SetMotion(CArray::MOTION_NEUTRAL);
	}
	else
	{
		// 目的地へ直接移動
		D3DXVec3Normalize(&moveVec, &moveVec);
		moveVec *= Arrayinfo::MoveSpeed;

		// 目的角を計算
		float fAngle = atan2(-moveVec.x, -moveVec.z);
		D3DXVECTOR3 Rotdest = GetRotDest();

		// 正規化関数
		Rotdest.y = NormalAngle(fAngle);

		// 目的角の値をセット
		SetRotDest(Rotdest);

		// 移動量を加算
		SetMove(moveVec);

		// 移動モーションにセット
		m_pMotion->SetMotion(CArray::MOTION_MOVE);
	}
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
//=========================================================
void CArray::SpawnReturn(void)
{
#if 1
	// ベクトルの成分計算
	D3DXVECTOR3 followVec = m_ActivePos - GetPos();
	float fDistance = D3DXVec3Length(&followVec);

	// 距離が一定値以上の場合
	if (fDistance > 5.0f)
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
		m_pFollowTarget = nullptr;
		m_isCheckNearFeed = false;

		if (!m_isCheckNearFeed)
			m_pBlackBoard->SetValue("CheckNearFeed", m_isCheckNearFeed);

		SetPrevAnt(nullptr);
		SetIsStop(false);

		// 保存されている座標を設定する
		m_MoveDestPos = m_SaveDestPos;
		m_pBlackBoard->SetValue<D3DXVECTOR3>("ArrayDestPos", m_MoveDestPos);
	}
#endif
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
	m_pBlackBoard->SetValue<CArray*>("Array", this);					 // 自身のポインタ
	m_pBlackBoard->SetValue<CTopAnt*>("TopAnt",m_pTopAnt);				 // トップアリのポインタ
	m_pBlackBoard->SetValue<D3DXVECTOR3>("ArrayDestPos", m_MoveDestPos); // 目的座標
	m_pBlackBoard->SetValue<D3DXVECTOR3>("TopPos", m_pTopAnt->GetPos()); // 目的座標
	m_pBlackBoard->SetValue<bool>("ReturnSpawn", m_isReturn);			 // 基地に帰るフラグ
	m_pBlackBoard->SetValue<bool>("GetTopOrder", m_isGettingTopOrder);	 // トップからの命令取得
	m_pBlackBoard->SetValue<bool>("AttackMode", m_isAttackMode);		 // 攻撃状態フラグ
	m_pBlackBoard->SetValue<bool>("CheckNearFeed", m_isCheckNearFeed);	 // 餌近くの判別フラグ
	m_pBlackBoard->SetValue<bool>("SetPoint", m_isSetPoint);			 // セットポイントフラグ

	// 仲間に使用するツリーノードにセットする
	m_pBehaviorTree = CArrayBehaviorTree::SetArrayTreeNode(m_pBlackBoard);
	m_pBehaviorTree->Init();
}
//=========================================================
// 球の当たり判定処理
//=========================================================
bool CArray::Colision(CSphereCollider* other)
{
	// 球同士の当たり判定の関数を返す
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}
//=========================================================
// 当たり判定格納関数
//=========================================================
void CArray::CollsionAll(const D3DXVECTOR3& pos)
{
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
				feed->DecLife(Arrayinfo::Damage);

				// スコアを加算
				CGameSceneObject::GetInstance()->GetScore()->AddScore(Arrayinfo::SCORE_UP);

				// コライダーの更新と指示変更
				m_pSphereCollider->SetPos(pos);

				// 基地に帰るフラグを有効化
				this->m_isReturn = true;

				break;
			}
		}
	}

	// 自分が移動状態じゃなかったら
	if (!this->m_isMove) return;
}
//=========================================================
// 敵との当たり判定関数
//=========================================================
void CArray::CollisionEnemy(void)
{
	// マップ内の敵の当たり判定
	CEnemyManager* pEnemyManager = CGameSceneObject::GetInstance()->GetEnemyManager();
	if (pEnemyManager == nullptr) return;

	// 最大の物と判定
	for (int nCnt = 0; nCnt < pEnemyManager->GetSize(); nCnt++)
	{
		// 単体取得
		auto Enemy = pEnemyManager->GetEnemyIdx(nCnt);
		if (!Enemy->GetIsActive()) continue;

		// 球形同士の当たり判定を実行
		if (Colision(Enemy->GetCollider()))
		{
			// 管理クラスの配列の要素を消す
			CGameSceneObject::GetInstance()->GetEnemyManager()->Erase(Enemy);

			// 敵の終了
			Enemy->Uninit();

			// 自身は有効化を終了する
			this->m_isActive = false;

			// 自身の出てきたスポナーに戻る
			SetPos(m_ActivePos);

			// フラグ初期化
			SetIsTopOrder(false);
			
			m_isAttackMode = false;

			return;
		}
	}
}
//=========================================================
// ベースの餌との当たり判定
//=========================================================
void CArray::CollisionBase(void)
{
	// 配列を取得する
	CBaseMapFeed* BaseFeed = CGameSceneObject::GetInstance()->GetBaseMapFeed();
	if (BaseFeed == nullptr) return;

	for (int nCnt = 0; nCnt < BaseFeed->GetFeedArraySize(); nCnt++)
	{
		// 各餌の要素を取得する
		auto Feed = BaseFeed->GetFeedIdx(nCnt);

		// 有効なら
		if (Colision(Feed->GetCollider()))
		{
			// スコアを加算
			CGameSceneObject::GetInstance()->GetScore()->AddScore(Arrayinfo::BASESCORE_UP);

			// 基地に帰るフラグを有効化し、ブラックボードを更新する
			if (!m_isReturn)
			{
				m_isReturn = true;
				m_pBlackBoard->SetValue("ReturnSpawn", m_isReturn);
			}

			return;
		}
	}
}
//=========================================================
// 目的座標設定関数
//=========================================================
void CArray::SetDestPos(const D3DXVECTOR3& pos)
{
	// 値を変更する
	m_MoveDestPos = pos;

	// 格納状態から変更されていたら値を再設定
	m_pBlackBoard->SetValue("ArrayDestPos", m_MoveDestPos);
}
//=========================================================
// 命令設定関数
//=========================================================
void CArray::SetIsTopOrder(const bool& isToporder)
{
	// フラグ変更
	m_isGettingTopOrder = isToporder;

	// 格納状態から変更されていたら値を再設定
	m_pBlackBoard->SetValue("GetTopOrder", m_isGettingTopOrder);
}
//=========================================================
// セットポイントフラグ関数
//=========================================================
void CArray::SetIsPointFlag(const bool& isSetpoint)
{
	// フラグ変更
	m_isSetPoint = isSetpoint;

	// 値を再設定
	m_pBlackBoard->SetValue("SetPoint", m_isSetPoint);
}
//=========================================================
// ブラックボード更新関数
//=========================================================
void CArray::SyncBlackBoard(void)
{
	m_pBlackBoard->SetValue("TopPos", m_pTopAnt->GetPos());
}