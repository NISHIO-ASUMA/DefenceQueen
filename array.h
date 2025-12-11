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

//*********************************************************
// アリ一匹に対するクラスを定義
//*********************************************************
class CArray : public CMoveCharactor
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
	void Reset(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nLife);
	void Moving(void);
	void OnSeparation(void);

	void FollowDestination(const D3DXVECTOR3& DestPos);

	void ArrayFollow(void);
	void SpawnReturn(void);
	void NodeSetting(void);
	
	bool Colision(CSphereCollider* other);

	void SetDestPos(const D3DXVECTOR3 pos) { m_MoveDestPos = pos; }
	void SetPrevAnt(CArray* pPrev) { m_pFollowTarget = pPrev;}
	void SetActive(bool isFlags) { m_isActive = isFlags; }
	void SetIsMove(bool isMove) { m_isMove = isMove; }
	void SetTopFollow(bool isFollow) { m_isTopAntFollow = isFollow; }
	void SetReturnSpawn(const bool& isReturn) { m_isReturn = isReturn; }
	void SetAtBase(const bool& isBase) { m_isAtBase = isBase; }
	void SetIsStop(const bool& isStop) { m_isStop = isStop; }
	bool GetActive(void) { return m_isActive; }
	bool GetMove(void) { return m_isMove; }
	bool GetReturn(void) { return m_isReturn; }
	bool GetIsAtBase(void) { return m_isAtBase; }
	bool GetisStop(void) { return m_isStop; }

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife);

private:

	//***********************
	// 定数構造体
	//***********************
	struct Arrayinfo
	{
		static constexpr float MoveSpeed = 4.0f;	// 移動速度
		static constexpr float SphereRange = 80.0f; // 球形範囲
		static constexpr float ARRAY_DISTANCE = 60.0f; // 仲間アリとの距離
		static constexpr float TOP_DISTANCE = 30.0f; // 先頭のアリとの距離
		static constexpr float PRIORITY_DISTANCE = 150.0f;
		static constexpr float STOP_DISTANCE = 20.0f;
	};

	bool m_isActive;					// 使用状態かどうか
	bool m_isMove;						// 移動するかどうか
	bool m_isTopAntFollow;				// トップアリについて行くかどうか
	bool m_isReturn;					// 巣にもどるかどうか
	bool m_isAtBase;					// スポナーにいるか
	bool m_isStop;						// 停止フラグ

	D3DXVECTOR3 m_MoveDestPos;			// 目的の座標
	CMotion* m_pMotion;					// モーションポインタ
	CSphereCollider* m_pSphereCollider;	// 球形のコライダー
	CBoxCollider* m_pBoxCollider;		// 矩形のコライダー
	std::unique_ptr<CParameter>m_pParameter;		// パラメータークラスポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ

	CArray* m_pFollowTarget;		// 一個前の自身のポインタ
};