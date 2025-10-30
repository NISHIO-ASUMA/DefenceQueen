//===============================================
//
// 出現する餌の処理 [ feed.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************
// 前方宣言
//**********************
class CSphereCollider;

//**********************
// 餌クラスを定義
//**********************
class CFeed : public CObjectX
{
public:

	CFeed(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CFeed();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFeed* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName);

private:

};

