//=====================================
//
// 草のビルボード処理 [ grass.h ]
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
#include "object3D.h"
#include <vector>

//**********************
// 前方宣言
//**********************
class CSphereCollider;

//********************************
// 草クラスを定義
//********************************
class CGrass : public CObject3D
{
public:

	CGrass(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CGrass();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetRadius(const float fRadius) { m_fRadius = fRadius; }

	static CGrass* Create(const D3DXVECTOR3 pos, int numgrass,float fradius);

private:

	CSphereCollider* m_pSphere; // 球形コライダー
	int m_nNumAll;	 // 総数
	float m_fRadius; // 半径
};