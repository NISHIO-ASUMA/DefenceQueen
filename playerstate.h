//=============================================
//
// プレイヤー状態管理処理 [ playerstate.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**************************
// インクルードファイル宣言
//**************************
#include "state.h"
#include "player.h"

//*********************************
// プレイヤーのベース状態管理
//*********************************
class CPlayerStateBase : public CStateBase
{
public:
	//***************************
	// 状態管理ID列挙型
	//***************************
	enum ID
	{
		ID_NEUTRAL, // 待機
		ID_MOVE, // 移動
		ID_ACTION, // 攻撃
		ID_JUMP, // ジャンプ
		ID_GUARD, // 防御
		ID_DAMAGE,// ダメージ
		ID_AVOIDRIGHT, // 回避
		ID_AVOIDLEFT, // 回避
		ID_MAX
	};

	CPlayerStateBase();
	~CPlayerStateBase();

	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnExit() {}

	int GetID() const override { return m_ID; }
	
	void SetID(ID id) { m_ID = id; }
	void SetOwner(CPlayer* pPlayer) { m_pPlayer = pPlayer; }

protected:
	CPlayer* m_pPlayer;		// プレイヤーのポインタ

private:
	ID m_ID;		// 列挙型のポインタ
};

//*********************************
// 待機状態時の状態管理
//*********************************
class CPlayerStateNeutral : public CPlayerStateBase
{
public:

	CPlayerStateNeutral();
	~CPlayerStateNeutral();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:
};


//*********************************
// 移動時の状態管理
//*********************************
class CPlayerStateMove : public CPlayerStateBase
{
public:

	CPlayerStateMove();
	~CPlayerStateMove();

	void OnStart();
	void OnUpdate();
	void OnExit();
};

//*********************************
// 攻撃時の状態管理
//*********************************
class CPlayerStateAction : public CPlayerStateBase
{
public:

	CPlayerStateAction();
	~CPlayerStateAction();

	void OnStart();
	void OnUpdate();
	void OnExit();
};

//*********************************
// ジャンプ状態時の管理
//*********************************
class CPlayerStateJump : public CPlayerStateBase
{
public:

	CPlayerStateJump();
	~CPlayerStateJump();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};

//*********************************
// 左回避状態時の管理
//*********************************
class CPlayerStateAvoidLeft : public CPlayerStateBase
{
public:

	CPlayerStateAvoidLeft();
	~CPlayerStateAvoidLeft();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};

//*********************************
// 右回避状態時の管理
//*********************************
class CPlayerStateAvoidRight : public CPlayerStateBase
{
public:

	CPlayerStateAvoidRight();
	~CPlayerStateAvoidRight();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};
