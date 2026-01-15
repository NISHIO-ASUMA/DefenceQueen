//=========================================================
//
// チュートリアルの仲間アリの処理クラス [ tutoarrayant.h ]
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

//*********************************************************
// 前方宣言
//*********************************************************
class CCollisionBox;
class CSphereCollider;

//*********************************************************
// チュートリアル用の仲間アリクラスを定義
//*********************************************************
class CTutoArrayAnt : public CMoveCharactor
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

	CTutoArrayAnt(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutoArrayAnt();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(CSphereCollider* other);

	inline void SetDestPos(const D3DXVECTOR3& pos) { m_DestPos = pos; }

	static CTutoArrayAnt* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:

	//**********************
	// 定数構造体宣言
	//**********************
	struct Config
	{
		static constexpr float SPEED = 3.0f;											 // 移動速度
		static constexpr float MAX_RADIUS = 40.0f;										 // 最大範囲
		static constexpr float NorRot = D3DX_PI * 2.0f;									 // 回転補正
		static constexpr const char* MOTION_NAME = "data/MOTION/Array/Array_Motion.txt"; // モーションパス
	};

	CSphereCollider* m_pSphereCollider; // 球形コライダー
	D3DXVECTOR3 m_DestPos;				// 座標設置用
};