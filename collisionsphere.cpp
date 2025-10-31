//=================================================
//
// 球形当たり判定処理 [ collisionsphere.cpp ]
// Author: Asuma Nishio
// 
//=================================================

//**********************
// インクルードファイル
//**********************
#include "collisionsphere.h"
#include "spherecollider.h"

//================================
// コンストラクタ
//================================
CCollisionSphere::CCollisionSphere() : CCollision(CCollision::TYPE_SPHERE)
{
	// 値のクリア
}
//================================
// デストラクタ
//================================
CCollisionSphere::~CCollisionSphere()
{
	// 無し
}
//================================
// 球同士の当たり判定
//================================
bool CCollisionSphere::Collision(CSphereCollider* thisCollider, CSphereCollider* otherCollider)
{
	// コライダー情報をセット
	CSphereCollider* MySphere = thisCollider;
	CSphereCollider* OtherSphere = otherCollider;

	// 座標を取得する
	D3DXVECTOR3 MyPos = MySphere->GetPos();
	D3DXVECTOR3 OtherPos = OtherSphere->GetPos();

	// 範囲を取得する
	float fMyRadius = MySphere->GetRadius();
	float fOtherRadius = OtherSphere->GetRadius();

	// 2点の座標の距離差分を算出する
	D3DXVECTOR3 DiffPos = MyPos - OtherPos;

	// 当たる距離を計算する
	float fDistance = (DiffPos.x * DiffPos.x) + (DiffPos.y * DiffPos.y) + (DiffPos.z * DiffPos.z);

	// 半径の2乗を計算
	float fAllRadius = fMyRadius + fOtherRadius;
	fAllRadius = fAllRadius * fAllRadius;
	
	// 半径の値よりも小さかったら
	if (fDistance <= fAllRadius)return true;

	// 未ヒット時
	return false;
}