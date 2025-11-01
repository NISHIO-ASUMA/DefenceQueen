//=============================================
//
// ゲージ関係のクラス処理 [ gauge.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//**********************
// ゲージクラスを定義
//**********************
class CGauge :public CObject2D
{
public:

	CGauge(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CGauge();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// int型のパラメータのゲージの長さを設定する関数
	/// </summary>
	/// <param name="nMaxHp">最大時のパラメータ</param>
	/// <param name="nCurrentHp">変動する現在のパラメータ</param>
	/// <param name="fMaxWidth">表示するゲージの最大幅</param>
	void SetLengthParamInt(const int nMax,const int nCurrent,const float fMaxWidth);

	/// <summary>
	/// float型のパラメータのゲージの長さを設定する関数
	/// </summary>
	/// <param name="fMax">割合</param>
	/// <param name="fCurrent">現在の値</param>
	/// <param name="fMaxWidth">最大時の横幅</param>
	void SetLengthParamFloat(const float fMax, const float fCurrent, const float fMaxWidth);

	static CGauge* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
};