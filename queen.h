//=========================================================
//
// 防衛対象アリの処理 [ queen.h ]
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
	void Hit(const int& nDamage);
	bool Collision(CSphereCollider * pOther);

	CSphereCollider* GetCollider(void) { return m_pSphereCollider; }

	static CQueen* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:

	//***********************************
	// 定数構造体
	//***********************************
	struct QueenInfo
	{
		static constexpr int Hp = 100;			// 体力値
		static constexpr float HitRange = 80.0f;// コリジョン半径
		static constexpr const char* SCRIPT = "data/MOTION/Queen/Queen_Motion.txt"; // ロードファイル名
	};

	std::unique_ptr<CParameter>m_pParameter;		// パラメータークラスポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CMotion* m_pMotion;								// モーションポインタ
	CSphereCollider* m_pSphereCollider;				// 円形ののコライダー
};