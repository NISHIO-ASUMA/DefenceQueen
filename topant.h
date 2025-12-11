//=========================================================
//
// 各スポナーの仲間に指示を出すアリのクラス [ topant.h ]
// Author: Asuma Nishio
// NOTE : これはトップアリ一体に関する処理
// このクラスのキャラクターが仲間アリの先頭隊列になる
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

//*********************************************************
// 前方宣言
//*********************************************************
class CInputKeyboard;
class CJoyPad;
class CSphereCollider;
class CBoxCollider;
class CCollisionSphere;
class CCollisionBox;

//*********************************************************
// 各スポナーのトップのアリのクラスを定義
//*********************************************************
class CTopAnt : public CMoveCharactor
{
public:

	//********************
	// モーションの種類
	//********************
	enum MOTION
	{
		NEUTRAL,
		MOVE,
		MOTION_MAX
	};

	//********************
	// 命令の種類
	//********************
	enum ORDER
	{
		MOVING,
		STOP,
		RETURN,
		ORDER_MAX
	};

	CTopAnt(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTopAnt();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	bool Collision(CBoxCollider* pOther, D3DXVECTOR3* pOutPos);
	bool CollisionSphere(CSphereCollider* pOther);
	
	void Moving(CJoyPad* pPad, CInputKeyboard* pKey);
	void MovePad(CJoyPad* pPad);
	void Separation(void);

	void SetDestMovePos(const D3DXVECTOR3& pos) { m_DestPos = pos; }
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	void SetSeparationRadius(const float& Radius) { m_fSeparationRadius = Radius; }
	void SetIsReturnPos(const bool& isflags) { m_isReturnNumber = isflags; }

	D3DXVECTOR3 GetDestPos(void) { return m_DestPos; }
	bool GetIsActive(void) const { return m_isActive; }
	bool GetIsReturnPos(void) const { return m_isReturnNumber; }
	float GetSeparationRadius(void) { return m_fSeparationRadius; }

	static CTopAnt* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:

	//**********************
	// 定数構造体宣言
	//**********************
	struct Config
	{
		static constexpr float SPEED = 4.0f; // 移動速度
		static constexpr float MAX_RADIUS = 100.0f; // 最大範囲
		static constexpr float NorRot = D3DX_PI * 2.0f; // 回転補正
		static constexpr float Separation = 3.0f; // 範囲拡大
	};

	CSphereCollider* m_pColliderSphere; // 球形コライダー
	CBoxCollider* m_pColliderBox;		// 矩形コライダー
	bool m_isActive;			  // アクティブフラグ
	bool m_isBranchSet;			  // 切り離し中かどうか
	bool m_isHPressing;   // Hキーを押している間
	bool m_isReturnNumber;// 数字を設定できるかどうか
	float m_fSeparationRadius;	  // 切り離し範囲
	D3DXVECTOR3 m_DestPos;		 // 座標設置用
};