//=========================================================
//
// 防衛対象の処理 [ queen.h ]
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
#include "nomovecharactor.h"
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CParameter;
class CShadowS;
class CStateMachine;
class CSphereCollider;
class CMotion;

//*********************************************************
// 女王キャラクタークラスを定義
//*********************************************************
class CQueen : public CNoMoveCharactor
{
public:

	//***********************************
	// モーション列挙型
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// ニュートラル
		//MOTION_ACTION,	// アクション
		//MOTION_DAMAGE,	// ダメージ
		//MOTION_DEATH,		// 死亡状態
		MOTION_MAX
	};

	CQueen(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CQueen();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CSphereCollider * pOther);

	static CQueen* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	//***********************************
	// 定数構造体
	//***********************************
	struct QueenInfo
	{
		static constexpr int Hp = 100;
		static constexpr float HitRange = 80.0f;
	};

	std::unique_ptr<CParameter>m_pParameter;		// パラメータークラスポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CMotion* m_pMotion;								// モーションポインタ
	CSphereCollider* m_pSphereCollider;				// 円形ののコライダー

	LPD3DXEFFECT m_pOutLine;		// エフェクトハンドル
};