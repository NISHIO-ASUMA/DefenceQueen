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
class CSelectPoint;
class CWorkerStateBase;

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
		MOTION_NEUTRAL,	// ニュートラル
		MOTION_MOVE,	// 移動
		MOTION_MAX
	};

	//***********************************
	// モーション列挙型
	//***********************************
	enum NUMARRAY
	{
		NUMARRAY_LITTLE, // 最小値
		NUMARRAY_MIDDLE, // 中央値
		NUMARRAY_LARGE,  // 最大値
		NUMARRAY_MAX
	};

	CWorker(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CWorker();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void MoveToPoint(void);
	void MoveToReturnBase(void);

	void ChangeState(CWorkerStateBase* pState, int nId);
	bool Collision(CSphereCollider* other);

	void SetDestPos(const D3DXVECTOR3 pos) { m_DestPos = pos; }
	void SetNeedNumber(const int nNumber) { m_nIdxNumber = nNumber; }
	void SetIsWork(const bool iswork) { m_isWork = iswork; }
	bool GetIsWork(void) const { return m_isWork; }
	bool GetIsCreate(void) const { return m_isCreate; }
	int RequiredNumber(void);

	static CWorker* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

	//****************************
	// 定数格納構造体
	//****************************
	struct Config
	{
		static constexpr float Distance = 80.0f;
		static constexpr float Move = 5.0f;
		static constexpr int LITTLE = 10;
		static constexpr int MIDDLE = 15;
		static constexpr int LARGE = 20;
	};

	std::unique_ptr<CStateMachine>m_pStateMachine;	// ステート基底クラスのポインタ
	CMotion* m_pMotion;					// モーションポインタ
	CSphereCollider* m_pSphereCollider;	// 球形のコライダー
	CSelectPoint* m_pSelect;			// 選択場所取得用
	D3DXVECTOR3 m_DestPos;				// 目的の座標

	D3DXVECTOR3 m_SavePos;				// 保存用座標
	D3DXVECTOR3 m_SaveRot;				// 保存用角度

	int m_nScaleNum;					// 必要な仲間数を返す
	int m_nIdxNumber;					// インデックス番号
	bool m_isMove;						// 移動中かフラグ
	bool m_isWork;						// 動作中かフラグ
	bool m_isCreate;					// 生成したか
};