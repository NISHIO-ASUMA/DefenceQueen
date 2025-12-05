//=========================================================
//
// 各スポナーの仲間に指示を出すアリのクラス [ topant.h ]
// Author: Asuma Nishio
// NOTE : これは一体に関する処理
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
class CBoxCollider;
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
	void Moving(CJoyPad* pPad, CInputKeyboard* pKey);
	void MovePad(CJoyPad* pPad);

	static CTopAnt* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:

	//**********************
	// 定数構造体宣言
	//**********************
	struct Config
	{
		static constexpr float SPEED = 7.0f; // 移動速度
		static constexpr float NorRot = D3DX_PI * 2.0f; // 回転速度
	};

	CBoxCollider* m_pColliderBox; // 矩形コライダー

};