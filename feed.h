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
class CParameter;

//*********************************************************
// 餌クラスを定義
//*********************************************************
class CFeed : public CObjectX
{
public:

	CFeed(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CFeed();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DecLife(const int& nDecValue);
	bool Collision(CSphereCollider* other);

	// イベントで使う関数を登録する
	void RegisterEvent(std::function<void(void)> Event) { m_event = Event; }

	void SetRadius(const float fRadius) { m_fRadius = fRadius; }
	void SetAssigned(const bool isAssing) { m_isAssing = isAssing; }

	bool IsAssigned() const { return m_isAssing; }
	bool GetIsDeath(void) { return m_isDeath; }
	float GetRadius(void) const { return m_fRadius; }

	CSphereCollider* GetCollider(void) const { return m_pSphere; }
	CParameter* GetParam(void) { return m_pParam.get(); }

	static CFeed* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName,const float fRadius);

private:

	std::function<void(void)>m_event; // 死亡時に呼ばれる処理

	CSphereCollider* m_pSphere; // 球形コライダー
	std::unique_ptr<CParameter>m_pParam; // パラメーター
	float m_fRadius;			// 半径
	bool m_isDeath;
	bool m_isAssing;			// 割り当てられたかどうか
};