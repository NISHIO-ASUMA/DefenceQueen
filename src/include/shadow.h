//=========================================================
//
// 影処理 [ shadow.h ]
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
#include "object3D.h"

//*********************************************************
// 影オブジェクトクラスを定義
//*********************************************************
class CShadow : public CObject3D
{
public:

	CShadow(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadow();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdatePos(const D3DXVECTOR3& pos) { SetPos(pos); }

	/// <summary>
	/// ポインタ生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="rot">角度</param>
	/// <returns></returns>
	static CShadow* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:
};
