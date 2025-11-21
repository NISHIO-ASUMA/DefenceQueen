//=========================================================
//
// タイトルで出現するオブジェクト管理処理 [ titleobject.h ]
// Author: Asuma Nishio
//
//=========================================================

//****************************************
// インクルードガード
//****************************************
#pragma once

//****************************************
// タイトルオブジェクト管理クラスを定義
//****************************************
class CTitleObject
{
public:

	~CTitleObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	
	static CTitleObject* GetInstance(void);

private:

	CTitleObject();	// コンストラクタ

	static CTitleObject* m_pInstance; // シングルトン変数
};