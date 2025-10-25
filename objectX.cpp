//====================================
//
// Xファイル処理 [ objectX.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "objectX.h"
#include "manager.h"
#include "xfilemanager.h"
#include "texture.h"

//=============================
// コンストラクタ
//=============================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_mtxWorld = {};
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nIdxModel = -1; 
}
//=============================
// デストラクタ
//=============================
CObjectX::~CObjectX()
{
	// 無し
}
//=============================
// 初期化処理
//=============================
HRESULT CObjectX::Init(void)
{
	// 結果を返す
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CObjectX::Uninit(void)
{
	// オブジェクト自身の破棄
	CObject::Release();
}
//=============================
// 更新処理
//=============================
void CObjectX::Update(void)
{
	// 無し
}
//=============================
// 描画処理
//=============================
void CObjectX::Draw(void)
{
	if (m_nIdxModel == -1)
		return;

	// ファイルマネージャー取得
	CXfileManager* pXMgr = CManager::GetInstance()->GetXManager();
	if (!pXMgr) return;

	// 配列情報
	auto& fileData = pXMgr->GetList();
	if (m_nIdxModel >= fileData.size()) return;

	// 配列
	auto& model = fileData[m_nIdxModel];
	if (!model.pMesh) return;

	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマトリックスの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルが取得できたら
	if (model.pBuffMat)
	{
		// ポインタ
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();

		// テクスチャ取得
		CTexture* pTex = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < model.dwNumMat; nCnt++)
		{
			// マテリアルのセット
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);

			// テクスチャ取得
			int texIdx = model.pTexture[nCnt];

			// テクスチャセット
			pDevice->SetTexture(0, (texIdx >= 0) ? pTex->GetAddress(texIdx) : nullptr);

			// モデルの描画
			model.pMesh->DrawSubset(nCnt);
		}
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//=============================
// 新規モデル登録
//=============================
void CObjectX::SetFilePass(const char* pFilePass)
{
	// マネージャー取得
	CXfileManager* pXMgr = CManager::GetInstance()->GetXManager();

	if (pXMgr != nullptr)
	{
		// パス連結
		std::string ModelName = "data/MODEL/";
		ModelName += pFilePass;

		// モデルを登録
		m_nIdxModel = pXMgr->Register(ModelName.c_str());
	}
}
//=============================
// 生成処理
//=============================
CObjectX* CObjectX::Create(int nIdx,D3DXVECTOR3 pos)
{
	// インスタンス生成
	CObjectX* pObjX = new CObjectX;
	if (pObjX == nullptr) return nullptr;

	pObjX->m_pos = pos;
	pObjX->m_nIdxModel = nIdx;

	// 初期化処理
	if (FAILED(pObjX->Init()))
	{
		// 破棄
		delete pObjX;

		// nullptr代入
		pObjX = nullptr;

		// nullptrを返す
		return nullptr;
	}

	// ポインタを返す
	return pObjX;
}
