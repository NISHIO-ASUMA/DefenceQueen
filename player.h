//=========================================================
//
// プレイヤー処理 [ player.h ]
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
class CInputKeyboard;
class CJoyPad;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;
class CBoxCollider;
class CMotion;

//*********************************************************
// プレイヤークラスを定義
//*********************************************************
class CPlayer : public CNoMoveCharactor
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
	void CollisionAll(D3DXVECTOR3 pPos,CInputKeyboard* pInput, CJoyPad* pPad);
	bool CollisionBlock(CBoxCollider* other, D3DXVECTOR3* pos);
	void OrderToArray(int nNum, D3DXVECTOR3 destpos);
	void SetSendArrayMoving(int nIdx,int nNum);

	int GetSelectIndex() const { return m_nSelectSpawn; }

	D3DXVECTOR3 RandomSetPos(const D3DXVECTOR3& pos,float fRadius, int nMoveActiveNum, int nIdx);
	CStateMachine* GetStateMachine() { return m_pStateMachine.get(); }

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,const char* pFilename);

private:

	static constexpr int NUM_SPAWN = 3; // スポーンポイント数
	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CBoxCollider* m_pBoxCollider;	// 矩形のコライダー
	CMotion* m_pMotion;				// モーションポインタ
	int m_nNum;						// 仮変数
	int m_nSelectSpawn;				// スポーン選択変数
	int m_nPrevSelectSpawn;		// 前回のスポーン選択変数
	int m_pSpawnData[NUM_SPAWN]; // スポーンデータ配列
};