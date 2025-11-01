//===========================================
//
// 司令塔キャラクターの処理 [ order.h ]
// Author: Asuma Nishio
//
//===========================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "movecharactor.h"
#include <memory>

//**********************
// 前方宣言
//**********************
class CMotion;
class CStateMachine;
class CSphereCollider;

//********************************
// 司令塔キャラクタークラスを定義
//********************************
class COrder : public CMoveCharactor
{
public:

	//***********************************
	// 使うモーションの種類
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// ニュートラル
		MOTION_MOVE,		// 移動
		MOTION_ACTION,		// アクション
		MOTION_MAX
	};

	COrder(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~COrder();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(CSphereCollider* other);

	static COrder* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

	CMotion* m_pMotion;								// モーションクラスのポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CSphereCollider* m_pSphereCollider;				// 球形のコライダー
};