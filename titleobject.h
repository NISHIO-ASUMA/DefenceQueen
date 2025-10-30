//=======================================================
//
// タイトルで出現するオブジェクト処理 [ titleobject.h ]
// Author: Asuma Nishio
//
//=======================================================

//**********************
// インクルードガード
//**********************
#pragma once

//****************************************
// タイトルオブジェクト管理クラスを定義
//****************************************
class CTitleObject
{
public:

	CTitleObject();
	~CTitleObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};