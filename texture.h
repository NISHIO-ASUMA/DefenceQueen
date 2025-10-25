//=====================================
//
// テクスチャ処理 [ texture.h ]
// Author: Asuma Nishio
// 
//=====================================

//*****************************
// インクルードガード
//*****************************
#pragma once

//*****************************
// インクルードファイル
//*****************************
#include <string>

//*****************************
// テクスチャ管理クラスを定義
//*****************************
class CTexture
{
public:
	// コンストラクタ・デストラクタ
	CTexture();
	~CTexture();

	// メンバ関数
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:

	HRESULT LoadJson(void);

	//*************************
	// テクスチャデータ構造体
	//*************************
	struct TEXDATA
	{
		std::string TexName; // テクスチャ名
		LPDIRECT3DTEXTURE9 TexData; // テクスチャポインタ
	};

	static constexpr int NUM_TEXTURE = 128;	// 最大テクスチャ数

	TEXDATA m_pTextureData[NUM_TEXTURE]; // テクスチャ管理配列
	static int m_nNumAll;				 // テクスチャカウント変数
};
