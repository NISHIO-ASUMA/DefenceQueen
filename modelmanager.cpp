//=========================================================
//
// キャラクターモデルファイル管理クラス [ modelmanager.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "modelmanager.h"
#include "json.hpp"
#include "manager.h"
#include "texture.h"
#include <fstream>

//*********************************************************
// 使用名前空間
//*********************************************************
using json = nlohmann::json; // jsonファイルストリーム

//*********************************************************
// 静的メンバ変数宣言
//*********************************************************
int CModelManager::m_nNumAll = NULL; // 総数管理

//=========================================================
// コンストラクタ
//=========================================================
CModelManager::CModelManager() : m_aModelData{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CModelManager::~CModelManager()
{
	// 全破棄
	UnLoad();
}
//=========================================================
// 全モデル読み込み処理
//=========================================================
HRESULT CModelManager::Load(void)
{
	// jsonファイルロード
	LoadJson();

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 全モデル破棄処理
//=========================================================
void CModelManager::UnLoad(void)
{
	// 格納情報の破棄
	for (auto iter = m_aModelData.begin(); iter != m_aModelData.end(); iter++)
	{
		// メッシュの破棄
		if ((*iter).pMesh != nullptr)
		{
			(*iter).pMesh->Release();
			(*iter).pMesh = nullptr;
		}

		// マテリアルポインタの破棄
		if ((*iter).pBuffMat != nullptr)
		{
			(*iter).pBuffMat->Release();
			(*iter).pBuffMat = nullptr;
		}

		// テクスチャの破棄
		(*iter).pTexture.clear();

		// 動的ファイルパスの破棄
		if (!(*iter).FilePath.empty())
		{
			(*iter).FilePath.clear();
		}

		// マテリアルデータの破棄
		if ((*iter).dwNumMat != NULL)
		{
			(*iter).dwNumMat = 0;
		}
	}

	// 配列クリア
	m_aModelData.clear();
}
//=========================================================
// モデル登録
//=========================================================
int CModelManager::Register(const char* pModelName)
{
	// すでに登録済みならそのインデックスを返す
	for (int nCnt = 0; nCnt < static_cast<int>(m_aModelData.size()); nCnt++)
	{
		if (m_aModelData[nCnt].FilePath == pModelName)
			return nCnt;
	}

	// ないなら新規登録処理
	ModelManagerInfo NewModelInfo = {};
	NewModelInfo.FilePath = pModelName;

	//===============================================================
	// モデル読み込み
	//===============================================================
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice)
		return -1;

	// Xファイルを生成する
	HRESULT hr = D3DXLoadMeshFromX
	(
		pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&NewModelInfo.pBuffMat,
		NULL,
		&NewModelInfo.dwNumMat,
		&NewModelInfo.pMesh
	);

	//// xファイルの法線情報関数
	//D3DXComputeNormals();

	// 例外メッセージ
	if (FAILED(hr))
	{
		std::string message = "モデル読み込みに失敗しました: ";
		message += pModelName;
		MessageBox(GetActiveWindow(), message.c_str(), "CModelManager", MB_OK);
		return -1;
	}

	//===============================================================
	// テクスチャ登録
	//===============================================================
	NewModelInfo.pTexture.clear();
	NewModelInfo.pTexture.resize(NewModelInfo.dwNumMat);

	if (NewModelInfo.pBuffMat)
	{
		// マテリアルデータのポインタ
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)NewModelInfo.pBuffMat->GetBufferPointer();

		// テクスチャポインタ取得
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < static_cast<int>(NewModelInfo.dwNumMat); nCnt++)
		{
			if (pMat[nCnt].pTextureFilename)
			{
				// テクスチャID登録
				int nTexID = pTexture->Register(pMat[nCnt].pTextureFilename);
				NewModelInfo.pTexture[nCnt] = nTexID;
			}
			else
			{
				// 例外値をセット
				NewModelInfo.pTexture[nCnt] = -1;
			}
		}
	}

	// 配列に登録する
	m_aModelData.push_back(NewModelInfo);

	// 総数のインデックスを返す
	return m_nNumAll++;
}
//=========================================================
// json読み込み
//=========================================================
HRESULT CModelManager::LoadJson(void)
{
	// ファイルオープン
	std::ifstream openfile(LOAD_FILE);

	// 例外処理
	if (!openfile.is_open())
	{
		MessageBox(GetActiveWindow(), "Model.json が開けません", "CModelmanager", MB_OK);
		return E_FAIL;
	}

	// json読み込み
	json loadjson;
	openfile >> loadjson;
	openfile.close();

	// 情報がなかったら
	if (loadjson.is_null() || loadjson.empty())
	{
		MessageBox(GetActiveWindow(), "Model.json にデータがありません", "CModelmanager", MB_OK);
		return E_FAIL;
	}

	// 配列クリア
	m_aModelData.clear();

	// 情報をセットしていく
	for (const auto& entry : loadjson)
	{
		// 指定の文字がなかったら
		if (!entry.contains("Model") || entry["Model"].is_null())
			continue;

		// jsonからファイルパス取得
		std::string filePath = entry["Model"].get<std::string>();

		if (filePath.empty())
			continue;

		// モデル読み込み
		LoadModel(filePath.c_str());

		// 総数加算
		m_nNumAll++;
	}

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 関数分け読み込み
//=========================================================
void CModelManager::LoadModel(const char* pModelName)
{
	// 格納用変数
	ModelManagerInfo NewModelInfo = {};
	NewModelInfo.FilePath = pModelName;

	//===============================================================
	// モデル読み込み
	//===============================================================
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice) return;

	// Xファイルを生成する
	HRESULT hr = D3DXLoadMeshFromX
	(
		pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&NewModelInfo.pBuffMat,
		NULL,
		&NewModelInfo.dwNumMat,
		&NewModelInfo.pMesh
	);

	// 例外メッセージ
	if (FAILED(hr))
	{
		std::string message = "モデル読み込みに失敗しました: ";
		message += pModelName;
		MessageBox(GetActiveWindow(), message.c_str(), "CModelManager", MB_OK);
		return;
	}

	//===============================================================
	// テクスチャ登録
	//===============================================================
	NewModelInfo.pTexture.clear();
	NewModelInfo.pTexture.resize(NewModelInfo.dwNumMat);

	if (NewModelInfo.pBuffMat)
	{
		// マテリアルデータのポインタ
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)NewModelInfo.pBuffMat->GetBufferPointer();

		// テクスチャポインタ取得
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < static_cast<int>(NewModelInfo.dwNumMat); nCnt++)
		{
			if (pMat[nCnt].pTextureFilename)
			{
				// テクスチャID登録
				int nTexID = pTexture->Register(pMat[nCnt].pTextureFilename);
				NewModelInfo.pTexture[nCnt] = nTexID;
			}
			else
			{
				// 例外値をセット
				NewModelInfo.pTexture[nCnt] = -1;
			}
		}
	}

	// 配列に登録する
	m_aModelData.push_back(NewModelInfo);
}