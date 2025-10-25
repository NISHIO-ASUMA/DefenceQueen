//===============================================
//
// 球形コライダー処理 [ spherecollider.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルーファイル
//**********************
#include "spherecollider.h"

//===========================
// コンストラクタ
//===========================
CSphereCollider::CSphereCollider() : m_fRadius(NULL)
{
	// 値のクリア
}
//===========================
// デストラクタ
//===========================
CSphereCollider::~CSphereCollider()
{

}
//===========================
// 球形コライダー生成処理
//===========================
CSphereCollider* CSphereCollider::Create(D3DXVECTOR3 pos, float fRadius)
{
	// インスタンス生成
	CSphereCollider* pSphere = new CSphereCollider;
	if (pSphere == nullptr) return nullptr;

	// 値をセット
	pSphere->SetPos(pos);
	pSphere->m_fRadius = fRadius;

	// 生成されたポインタ
	return pSphere;
}