//=========================================================
//
// チュートリアルUI処理 [ tutorialui.h ]
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
// チュートリアルuiクラスを定義
//*********************************************************
class CTutorialUi : public CObject2D
{
public:

	CTutorialUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTutorialUi();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	inline void SetIsAlpha(const bool& isAlpha) { m_isAlpha = isAlpha; }
	inline void SetIsActive(const bool& isActive) { m_isActive = isActive; }

	bool GetIsAlpha(void) const { return m_isAlpha; }
	bool GetIsActive(void) const { return m_isActive; }
	bool GetIsCheck(void) const { return m_isCheck; }
	bool GetIsFinish(void) const { return (m_isAlpha && m_fAlpha <= 0.0f); }

	/// <summary>
	/// ポインタ生成処理
	/// </summary>
	/// <param name="pos">生成座標</param>
	/// <param name="fWidth">横幅</param>
	/// <param name="fHeight">高さ</param>
	/// <param name="pFileName">テクスチャファイル名</param>
	/// <returns></returns>
	static CTutorialUi* Create
	(
		const D3DXVECTOR3& pos,
		const float& fWidth,
		const float& fHeight,
		const char * pFileName
	);

private:

	//******************************
	// 定数構造体
	//******************************
	struct Config
	{
		static constexpr float MOVE = 2.0f;			// 移動量
		static constexpr float DECALPHA = 0.03f;	// α値減少量
	};

	bool m_isAlpha;		// 透明になったかどうか
	bool m_isActive;	// 使用中かどうか
	bool m_isCheck;		// セットポイントについたかどうか
	float m_fAlpha;		// 透明度
};