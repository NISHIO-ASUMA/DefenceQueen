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

//*********************************************************
// プレイヤーの仲間クラスを定義
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
	bool Colision(CSphereCollider* other);

	void SetActive(bool isFlags) { m_isActive = isFlags; }
	bool GetActive(void) { return m_isActive; }

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife);

private:

	//***********************
	// 定数構造体
	//***********************
	struct Arrayinfo
	{
		static constexpr float SphereRange = 80.0f; // 球形範囲
	};

	bool m_isActive;					// 使用状態かどうか
	CMotion* m_pMotion;					// モーションポインタ
	CSphereCollider* m_pSphereCollider;	// 球形のコライダー
	std::unique_ptr<CParameter>m_pParameter;		// パラメータークラスポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
};