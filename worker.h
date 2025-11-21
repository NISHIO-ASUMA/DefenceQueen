//=========================================================
//
// 指示を出す働きアリの処理 [ worker.h ]
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
class CMotion;
class CStateMachine;
class CSphereCollider;

//*********************************************************
// 働きアリクラスの定義
//*********************************************************
class CWorker : public CMoveCharactor
{
public:

	//***********************************
	// モーション列挙型
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// ニュートラル
		MOTION_MOVE,		// 移動
		MOTION_ACTION,		// アクション
		MOTION_MAX
	};

	CWorker(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CWorker();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(CSphereCollider* other);

	static CWorker* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CMotion* m_pMotion;					// モーションポインタ
	CSphereCollider* m_pSphereCollider;	// 球形のコライダー

};
