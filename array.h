//=========================================================
//
// プレイヤーの仲間に関するクラス処理 [ array.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "movecharactor.h"
#include <memory>
#include "instancingcharactor.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CMotion;
class CSphereCollider;
class CBoxCollider;
class CTopAnt;
class CMotionInstancing;

//*********************************************************
// アリ一匹に対するクラスを定義
//*********************************************************
class CArray : public CInstancingCharactor
{
public:

	//************************
	// モーション列挙型
	//************************
	enum MOTION
	{
		MOTION_NEUTRAL,
		MOTION_MOVE,
		MOTION_MAX
	};

	CArray(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CArray();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Moving(void);
	void OnSeparation(void);
	void FollowDestination(const D3DXVECTOR3& DestPos);
	void FollowTop(D3DXVECTOR3 vpos);
	void ArrayFollow(void);
	void SpawnReturn(void);
	void NodeSetting(void);
	
	bool Colision(CSphereCollider* other);
	void CollsionAll(const D3DXVECTOR3& pos);
	void CollisionEnemy(void);
	void CollisionEventFeed(void);
	void CollisionBase(void);

	void SetDestPos(const D3DXVECTOR3& pos);
	void SetIsTopOrder(const bool& isToporder);
	void SetIsPointFlag(const bool& isSetpoint);
	void SetIsAtackMode(const bool& isMode);

	inline void SetTopAntPointer(CTopAnt* pAnt) { m_pTopAnt = pAnt; }
	inline void SetSaveDestPos(const D3DXVECTOR3& pos) { m_SaveDestPos = pos; }

	inline void SetActivePos(const D3DXVECTOR3& pos) { m_ActivePos = pos; }
	inline void SetPrevAnt(CArray* pPrev) { m_pFollowTarget = pPrev;}
	inline void SetMyListId(const int& nIdx) { m_nListGroupId = nIdx; }
	inline void SetActive(bool isFlags) { m_isActive = isFlags; }
	inline void SetIsMove(bool isMove) { m_isMove = isMove; }
	inline void SetTopFollow(bool isFollow) { m_isTopAntFollow = isFollow; }
	inline void SetReturnSpawn(const bool& isReturn) { m_isReturn = isReturn; }
	inline void SetAtBase(const bool& isBase) { m_isAtBase = isBase; }
	inline void SetIsStop(const bool& isStop) { m_isStop = isStop; }

	inline D3DXVECTOR3 GetActivePos(void) const { return m_ActivePos; }
	inline bool GetActive(void) const { return m_isActive; }
	inline bool GetMove(void) const { return m_isMove; }
	inline bool GetReturn(void) const { return m_isReturn; }
	inline bool GetIsAtBase(void) const { return m_isAtBase; }
	inline bool GetisStop(void) const { return m_isStop; }
	inline bool GetIsTopOrder(void) const { return m_isGettingTopOrder; }
	inline bool GetIsAttackMode(void) const { return m_isAttackMode; }
	inline bool GetIsSetPoint(void) const { return m_isSetPoint; }

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife);

private:

	//***********************
	// 定数構造体
	//***********************
	struct Arrayinfo
	{
		static constexpr float MoveSpeed = 2.0;			// 移動速度
		static constexpr float SphereRange = 40.0f;		// 球形範囲
		static constexpr float ARRAY_DISTANCE = 80.0f;	// 仲間アリとの距離
		static constexpr float TOP_DISTANCE = 60.0f;	// 先頭のアリとの距離
		static constexpr float STOP_DISTANCE = 10.0f;	// 停止距離

		static constexpr int SCORE_UP = 15000;			// スコアの加算量
		static constexpr int BASESCORE_UP = 50;			// スコアの加算量
		static constexpr int Damage = 1;				// ダメージ値
		static constexpr const char* SCRIPT = "data/MOTION/Array/Array_Motion.txt"; // モーションスクリプトファイル
	};

	int m_nListGroupId;					// 自身が動いているidのリスト番号
	int m_nStopCount;					// ストップカウント

	bool m_isActive;					// 使用状態かどうか
	bool m_isMove;						// 移動するかどうか
	bool m_isTopAntFollow;				// トップアリについて行くかどうか
	bool m_isReturn;					// 巣にもどるかどうか
	bool m_isAtBase;					// スポナーにいるか
	bool m_isStop;						// 停止フラグ
	bool m_isAttackMode;				// 攻撃状態フラグ
	bool m_isCheckNearFeed;				// 餌があるかフラグ
	bool m_isSetPoint;					// 餌があるかフラグ
	bool m_isGettingTopOrder;			// トップからの命令を取得したか

	D3DXVECTOR3 m_MoveDestPos;			// 目的の座標
	D3DXVECTOR3 m_ActivePos;			// 出現時の座標
	D3DXVECTOR3 m_SaveDestPos;			// 保存しておく目的座標
	CMotionInstancing* m_pMotion;		// モーションポインタ
	CSphereCollider* m_pSphereCollider;	// 球形のコライダー
	CBoxCollider* m_pBoxCollider;		// 矩形のコライダー
	
	CArray* m_pFollowTarget;			// 一個前の自身のポインタ
	CTopAnt* m_pTopAnt;					// 追従対象のトップアリのポインタ

	std::unique_ptr<CParameter>m_pParameter;	// パラメータークラスポインタ

	void SyncBlackBoard(void);
};