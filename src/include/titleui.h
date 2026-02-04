//=========================================================
//
// タイトルui処理 [ titleui.h ]
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
#include "object2D.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CObject;

//*********************************************************
// タイトルUIオブジェクトクラスを定義
//*********************************************************
class CTitleUi : public CObject2D
{
public:

	CTitleUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleUi();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	/// <summary>
	/// ポインタ生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="col">カラー</param>
	/// <param name="fWidth">横幅</param>
	/// <param name="fHeight">高さ</param>
	/// <param name="pTexName">テクスチャファイル名</param>
	/// <returns></returns>
	static CTitleUi* Create
	(
		const D3DXVECTOR3& pos,
		const D3DXCOLOR& col,
		const float& fWidth,
		const float& fHeight,
		const char* pTexName
	);

private:
};