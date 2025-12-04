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
	bool Colision(CSphereCollider* other);

	void SetActive(bool isFlags) { m_isActive = isFlags; }
	void SetIsMove(bool isMove) { m_isMove = isMove; }
	void SetDestPos(const D3DXVECTOR3 pos) { m_MoveDestPos = pos; }

	bool GetActive(void) { return m_isActive; }
	bool GetMove(void) { return m_isMove; }

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife);

private:

	//***********************
	// 定数構造体
	//***********************
	struct Arrayinfo
	{
		static constexpr float SphereRange = 80.0f; // 球形範囲
		static constexpr float MoveSpeed = 4.0f;   // 移動速度
	};


	bool m_isActive;					// 使用状態かどうか
	bool m_isMove;						// 移動するかどうか
	D3DXVECTOR3 m_MoveDestPos;			// 目的の座標
	CMotion* m_pMotion;					// モーションポインタ
	CSphereCollider* m_pSphereCollider;	// 球形のコライダー
	CBoxCollider* m_pBoxCollider;
	std::unique_ptr<CParameter>m_pParameter;		// パラメータークラスポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
};