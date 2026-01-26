//=========================================================
//
// 出現する餌の処理 [ feed.h ]
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
#include "objectX.h"
#include <memory>
#include <functional>

//*********************************************************
// 前方宣言
//*********************************************************
class CSphereCollider;
class CBoxCollider;
class CParameter;

//*********************************************************
// 餌クラスを定義
//*********************************************************
class CFeed : public CObjectX
{
public:

	//******************************************
	// カラー変更状態列挙型 
	//******************************************
	enum COLTYPE
	{
		COLTYPE_NONE,	// 通常
		COLTYPE_CHANGE,	// 変更
		COLTYPE_MAX
	};

	CFeed(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CFeed();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DecLife(const int& nDecValue);
	bool Collision(CSphereCollider* other);
	bool CollisionBox(CBoxCollider* pOther, D3DXVECTOR3* OutPos);

	void RegisterEvent(std::function<void(void)> Event) { m_event = Event; }

	inline void SetRadius(const float fRadius) { m_fRadius = fRadius; }
	inline void SetAssigned(const bool isAssing) { m_isAssing = isAssing; }
	inline void SetLife(const int nLife) { m_nLife = nLife; }

	inline bool IsAssigned() const { return m_isAssing; }
	inline float GetRadius(void) const { return m_fRadius; }

	CSphereCollider* GetCollider(void) const { return m_pSphere; }
	CBoxCollider* GetBoxCollider(void) const { return m_pBoxCollider; }
	CParameter* GetParam(void) { return m_pParam.get(); }

	static CFeed* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName, const float fRadius, const int nLife = 25);

private:

	void ColorCheck(void);
	D3DCOLORVALUE LerpColor(const D3DCOLORVALUE& a,const D3DCOLORVALUE& b,float t);

	std::function<void(void)>m_event;	// 死亡時に呼ばれる処理

	CSphereCollider* m_pSphere;			// 球形コライダー
	CBoxCollider* m_pBoxCollider;		 // 矩形コライダー
	std::unique_ptr<CParameter>m_pParam; // パラメーター

	COLTYPE m_ColType;			// カラー状態

	int m_ColorFrameCnt;		// カラー変更からの経過フレーム
	int m_nLife;				// 体力値
	float m_fRadius;			// 半径
	bool m_isAssing;			// 割り当てられたかどうか
};