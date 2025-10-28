//=====================================
//
// プレイヤー処理 [ player.h ]
// Author: Asuma Nishio
//
//=====================================

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
class CShadow;
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;
class CBoxCollider;
class CMotion;

//*************************
// プレイヤークラスを定義
//*************************
class CPlayer : public CMoveCharactor
{
public:
	//***********************************
	// プレイヤーが行うモーション列挙型
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// ニュートラル
		MOTION_MOVE,		// 移動
		MOTION_ACTION,		// アクション
		MOTION_JUMP,		// ジャンプ
		MOTION_LANDING,		// 着地
		MOTION_JUMPATTACK,	// ジャンプ攻撃
		MOTION_DAMAGE,		// ダメージ
		MOTION_AVOID,		// 回避
		MOTION_MAX
	};

	CPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CPlayer();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void ChangeState(CPlayerStateBase* pNewState,int Id);
	bool CollisionBlock(D3DXVECTOR3 * pos);

	CParameter* GetParameter(void) { return m_pParameter.get(); }
	CStateMachine* GetStateMachine() { return m_pStateMachine.get(); }

	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,const char* pFilename);
	static bool IsDeath(void) { return m_isDeath; }

private:
	static bool m_isDeath;  // 静的
	std::unique_ptr<CParameter>m_pParameter; // パラメータークラスポインタ
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CMotion* m_pMotion;				// モーションポインタ
	CBoxCollider* m_pBoxCollider;	// 矩形のコライダー
};