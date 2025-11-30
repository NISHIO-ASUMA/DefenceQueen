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
class CSelectPoint;

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
	void ChangeState(CEnemyStateBase* pNewState, int Id);
	bool Collision(CSphereCollider* pOther);

	CParameter* GetParameter(void) { return m_pParameter.get(); }
	CStateMachine* GetStateMachine() { return m_pStateMachine.get(); }

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife);

private:

	void NodeSetting(void);

	CMotion * m_pMotion;				// モーションクラス
	CSphereCollider* m_pSphereCollider; // 球形コライダー
	CSelectPoint* m_pSelect;			// 判定の受け皿ポインタ
	std::unique_ptr <CParameter>m_pParameter;		 // パラメータクラス
	std::unique_ptr<CStateMachine>m_pStateMachine;	 // ステート基底クラスのポインタ
};