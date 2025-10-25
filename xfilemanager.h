//=================================================
//
// モデルファイル管理クラス [ xfilemanager.h ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <string>
#include <vector>

//**********************
// 管理クラスを定義
//**********************
class CXfileManager
{
public:
	//*************************
	// Xファイルデータ構造体
	//*************************
	struct XFILEDATA
	{
		D3DXVECTOR3 Size;		// モデルのサイズ
		LPD3DXMESH pMesh;		// メッシュのポインタ
		LPD3DXBUFFER pBuffMat;	// マテリアルのポインタ
		DWORD dwNumMat;			// マテリアル数
		std::vector<int>pTexture; // テクスチャの動的ポインタ
		std::string FilePath;	// ファイル名
	};

	CXfileManager();
	~CXfileManager();

	HRESULT Load(void);
	void UnLoad(void);
	void LoadModel(const char* pModelName);
	int Register(const char* pFileName);

	XFILEDATA GetInfo(const int nIdx) { return m_aFileData[nIdx]; } // 配列番号取得
	std::vector<XFILEDATA>& GetList(void) { return m_aFileData; } // オブジェクト本体

private:

	HRESULT LoadJson(void); // json読み込み

	// 動的配列
	std::vector<XFILEDATA>m_aFileData;	// モデル管理配列
	static int m_nNumAll; // モデルの総数
};

