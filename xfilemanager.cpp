//=================================================
//
// モデルファイル管理クラス [ xfilemanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// インクルードファイル
//**********************
#include "xfilemanager.h"
#include "json.hpp"
#include "manager.h"
#include "texture.h"
#include <fstream>

//**********************
// 使用名前空間
//**********************
using json = nlohmann::json;

//**********************
// 静的メンバ変数宣言
//**********************
int CXfileManager::m_nNumAll = NULL;

//========================
// コンストラクタ
//========================
CXfileManager::CXfileManager() : m_aFileData{}
{

}
//========================
// デストラクタ
//========================
CXfileManager::~CXfileManager()
{
	// 全部の破棄
	UnLoad();
}
//========================
// 全モデル読み込み
//========================
HRESULT CXfileManager::Load(void)
{
	// jsonファイルロード
	LoadJson();

	// 初期化結果を返す
	return S_OK;
}
//========================
// 全モデル破棄
//========================
void CXfileManager::UnLoad(void)
{
	// 情報の破棄
	for (auto iter = m_aFileData.begin(); iter != m_aFileData.end(); iter++)
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
			(*iter).FilePath.shrink_to_fit();
		}

		// マテリアルデータの破棄
		if ((*iter).dwNumMat != NULL)
		{
			(*iter).dwNumMat = 0;
		}
	}

	// 配列クリア
	m_aFileData.clear();
}
//========================
// モデル登録処理
//========================
int CXfileManager::Register(const char* pFileName)
{
	// すでに登録済みならそのインデックスを返す
	for (int nCnt = 0; nCnt < m_aFileData.size(); nCnt++)
	{
		if (m_aFileData[nCnt].FilePath == pFileName)
			return nCnt;
	}

	// 新規登録
	XFILEDATA newData = {};
	newData.FilePath = pFileName;

	//==============================
	// モデル読み込み
	//==============================
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice)
		return -1;

	// Xファイルをロードする
	HRESULT hr = D3DXLoadMeshFromX
	(
		pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&newData.pBuffMat,
		NULL,
		&newData.dwNumMat,
		&newData.pMesh
	);

	// 例外メッセージ
	if (FAILED(hr))
	{
		std::string msg = "モデル読み込みに失敗しました: ";
		msg += pFileName;
		MessageBox(GetActiveWindow(), msg.c_str(), "CXfileManager", MB_OK);
		return -1;
	}

	//==============================
	// モデルサイズ算出
	//==============================
	D3DXVECTOR3 Vtxmax = VECTOR3_NULL;
	D3DXVECTOR3 Vtxmin = VECTOR3_NULL;

	int nNumVtx = newData.pMesh->GetNumVertices();

	DWORD sizeFVF = D3DXGetFVFVertexSize(newData.pMesh->GetFVF());
	BYTE* pVtxBuff = nullptr;
	newData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ローカルポインタ
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (Vtx.x > Vtxmax.x) Vtxmax.x = Vtx.x;
		if (Vtx.y > Vtxmax.y) Vtxmax.y = Vtx.y;
		if (Vtx.z > Vtxmax.z) Vtxmax.z = Vtx.z;

		if (Vtx.x < Vtxmin.x) Vtxmin.x = Vtx.x;
		if (Vtx.y < Vtxmin.y) Vtxmin.y = Vtx.y;
		if (Vtx.z < Vtxmin.z) Vtxmin.z = Vtx.z;

		pVtxBuff += sizeFVF;
	}

	// アンロック
	newData.pMesh->UnlockVertexBuffer();

	// 矩形のサイズ生成
	newData.Size.x = Vtxmax.x - Vtxmin.x;
	newData.Size.y = Vtxmax.y - Vtxmin.y;
	newData.Size.z = Vtxmax.z - Vtxmin.z;

	//==============================
	// テクスチャ登録
	//==============================
	newData.pTexture.clear();
	newData.pTexture.resize(newData.dwNumMat);

	if (newData.pBuffMat)
	{
		// マテリアルデータのポインタ
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)newData.pBuffMat->GetBufferPointer();

		// テクスチャポインタ取得
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < newData.dwNumMat; nCnt++)
		{
			if (pMat[nCnt].pTextureFilename)
			{
				// テクスチャID登録
				int TexID = pTexture->Register(pMat[nCnt].pTextureFilename);
				newData.pTexture[nCnt] = TexID;
			}
			else
			{
				// 初期値をセット
				newData.pTexture[nCnt] = -1;
			}
		}
	}

	// 配列に登録する
	m_aFileData.push_back(newData);

	// 登録数を更新して返す
	return m_nNumAll++; 
}
//========================
// jsonファイル読み込み
//========================
HRESULT CXfileManager::LoadJson(void)
{
	// ファイルオープン
	std::ifstream openfile("data/JSON/XFile.json");

	// 例外処理
	if (!openfile.is_open())
	{
		MessageBox(GetActiveWindow(), "XFile.json が開けません", "xfilemanager", MB_OK);
		return E_FAIL;
	}

	// json読み込み
	json j;
	openfile >> j;
	openfile.close();

	// 情報がなかったら
	if (j.is_null() || j.empty())
	{
		MessageBox(GetActiveWindow(), "XFile.json にデータがありません", "xfilemanager", MB_OK);
		return E_FAIL;
	}

	// 配列クリア
	m_aFileData.clear();

	// 情報をセットしていく
	for (const auto& entry : j)
	{
		// 文字がなかったら
		if (!entry.contains("XFile") || entry["XFile"].is_null())
			continue;

		// ファイルパス取得
		std::string filePath = entry["XFile"].get<std::string>();

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
//========================
// モデル登録処理
//========================
void CXfileManager::LoadModel(const char* pModelName)
{
	// 新規登録
	XFILEDATA newData = {};
	newData.FilePath = pModelName;

	//==============================
	// モデル読み込み
	//==============================
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice)
		return;

	// モデル読み込み
	HRESULT hr = D3DXLoadMeshFromX(
		pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&newData.pBuffMat,
		NULL,
		&newData.dwNumMat,
		&newData.pMesh);

	// 例外設定
	if (FAILED(hr))
	{
		std::string msg = "モデル読み込みに失敗しました: ";
		msg += pModelName;
		MessageBox(GetActiveWindow(), msg.c_str(), "CXfileManager", MB_OK);
		return;
	}

	//==============================
	// モデルサイズ算出
	//==============================
	D3DXVECTOR3 Vtxmax = VECTOR3_NULL;
	D3DXVECTOR3 Vtxmin = VECTOR3_NULL;

	// 頂点数の取得
	int nNumVtx = newData.pMesh->GetNumVertices();

	DWORD sizeFVF = D3DXGetFVFVertexSize(newData.pMesh->GetFVF());
	BYTE* pVtxBuff = nullptr;
	newData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ローカルポインタ
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (Vtx.x > Vtxmax.x) Vtxmax.x = Vtx.x;
		if (Vtx.y > Vtxmax.y) Vtxmax.y = Vtx.y;
		if (Vtx.z > Vtxmax.z) Vtxmax.z = Vtx.z;

		if (Vtx.x < Vtxmin.x) Vtxmin.x = Vtx.x;
		if (Vtx.y < Vtxmin.y) Vtxmin.y = Vtx.y;
		if (Vtx.z < Vtxmin.z) Vtxmin.z = Vtx.z;

		pVtxBuff += sizeFVF;
	}

	// アンロック
	newData.pMesh->UnlockVertexBuffer();

	// サイズ
	newData.Size.x = Vtxmax.x - Vtxmin.x;
	newData.Size.y = Vtxmax.y - Vtxmin.y;
	newData.Size.z = Vtxmax.z - Vtxmin.z;

	//==============================
	// テクスチャ登録
	//==============================
	newData.pTexture.clear();
	newData.pTexture.resize(newData.dwNumMat);

	if (newData.pBuffMat)
	{
		// マテリアルポインタ
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)newData.pBuffMat->GetBufferPointer();

		// テクスチャクラスポインタ取得
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < newData.dwNumMat; nCnt++)
		{
			// nullチェック
			if (pMat[nCnt].pTextureFilename)
			{
				// テクスチャIDセット
				int texID = pTexture->Register(pMat[nCnt].pTextureFilename);

				// 配列に登録
				newData.pTexture[nCnt] = texID;
			}
			else
			{
				// -1で初期化
				newData.pTexture[nCnt] = -1;
			}
		}
	}

	// 登録完了
	m_aFileData.push_back(newData);
}