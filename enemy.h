//=========================================================
//
// 敵の処理 [ enemy.h ]
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
#include "model.h"
#include "motion.h"
#include "movecharactor.h"
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CParameter;
class CShadowS;
class CStateMachine;
class CEnemyStateBase;
class CSphereCollider;
class CFeed;

//*********************************************************
// 敵クラスを定義
//*********************************************************
class CEnemy : public CMoveCharactor
{
public:

	//***********************************
	// 敵モーション列挙型
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,	// ニュートラル
		MOTION_MOVE,	// 移動
		MOTION_MAX
	};

	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CEnemy();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	
	void MoveToFeed(void);
	void AttackToAnt(void);
	void RobToFeed(void);
	void MoveToQueen(void);
	CFeed* FindFeed(void);

	void CollisionFeed(void);
	void CollisionQueen(void);
	bool Collision(CSphereCollider* pOther);

	inline void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	inline bool GetIsActive(void) const { return m_isActive; }

	CParameter* GetParameter(void) { return m_pParameter.get(); }

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife);

private:

	void NodeSetting(void); // 敵のAIノードツリー

	bool m_isActive;		// 有効かどうか
	bool m_isDestFeed;		// 餌のフラグ
	bool m_isDestQueen;		// 女王へのフラグ

	CMotion * m_pMotion;				// モーションクラス
	CFeed* m_pTargetFeed;				// ターゲットの餌

	std::unique_ptr<CSphereCollider>m_pSphereCollider; // 球形コライダー
	std::unique_ptr<CParameter>m_pParameter;		 // パラメータクラス
};