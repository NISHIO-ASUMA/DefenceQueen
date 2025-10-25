//=====================================
//
// 敵の処理 [ enemy.h ]
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
#include "object.h"
#include "model.h"
#include "motion.h"
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
class CEnemyStateBase;

//**********************
// 敵クラスを定義
//**********************
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
		MOTION_ACTION,	// アクション
		MOTION_DAMAGE,	// ダメージ
		MOTION_MAX
	};

	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CEnemy();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void ChangeState(CEnemyStateBase* pNewState, int Id);

	CParameter* GetParameter(void) { return m_pParameter.get(); }
	CStateMachine* GetStateMachine() { return m_pStateMachine.get(); }

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife,const char * pFileName);

private:

	const char* m_pFileName; // スクリプトファイル

	std::unique_ptr <CParameter>m_pParameter;		 // パラメータクラス
	std::unique_ptr<CStateMachine>m_pStateMachine;	 // ステート基底クラスのポインタ
	CMotion * m_pMotion;			 // モーションクラス
};