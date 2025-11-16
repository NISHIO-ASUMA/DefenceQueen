//=====================================
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
CObjectX::CObjectX(int nPriority) : CObject(nPriority),
m_mtxWorld{},
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_Scale(INITSCALE),
m_isShadow(false),
m_nIdxModel(-1)
{
	// 値のクリア
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
	if (m_nIdxModel >= static_cast<int>(fileData.size())) return;

	// 配列
	auto& model = fileData[m_nIdxModel];
	if (!model.pMesh) return;

	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxScale,mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

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
		// マテリアルデータのポインタ
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

	// マトリックスシャドウ描画
	if (m_isShadow)
	{
		DrawShadow();
	}
}
//=============================
// マトリックスシャドウ描画
//=============================
void CObjectX::DrawShadow(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice) return;

	// Xファイルマネージャー取得
	CXfileManager* pXMgr = CManager::GetInstance()->GetXManager();
	if (!pXMgr) return;

	// 配列情報の取得
	auto& fileData = pXMgr->GetList();
	if (m_nIdxModel < NULL || m_nIdxModel >= static_cast<int>(fileData.size())) return;

	// モデル要素を取得
	auto& model = fileData[m_nIdxModel];
	if (!model.pMesh) return;

	// ライト方向
	D3DXVECTOR4 lightDir(0.2f, -0.63f, -0.02f, 0.0f);

	// 平面投影座標を設定
	D3DXPLANE plane;
	D3DXVECTOR3 point = D3DXVECTOR3(0.0f,0.5f,0.0f);
	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f,-0.5f,0.0f);
	D3DXPlaneFromPointNormal(&plane, &point, &normal);

	// 影マトリックス生成
	D3DXMATRIX mtxShadow;
	D3DXMatrixShadow(&mtxShadow, &lightDir, &plane);

	// 影をモデルの位置に合わせる
	D3DXMATRIX mtxWorldShadow;
	D3DXMatrixMultiply(&mtxWorldShadow, &m_mtxWorld, &mtxShadow);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldShadow);

	// 半透明に設定
	D3DMATERIAL9 shadowMat = {};
	shadowMat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.35f);
	shadowMat.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.35f);

	// マテリアルセット
	pDevice->SetMaterial(&shadowMat);

	// メッシュ描画
	for (int nCnt = 0; nCnt < model.dwNumMat; nCnt++)
	{
		model.pMesh->DrawSubset(nCnt);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&shadowMat);
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
CObjectX* CObjectX::Create(const char * pModelName,D3DXVECTOR3 pos)
{
	// インスタンス生成
	CObjectX* pObjX = new CObjectX;
	if (pObjX == nullptr) return nullptr;

	pObjX->SetPos(pos);
	pObjX->SetFilePass(pModelName);

	// 初期化処理
	if (FAILED(pObjX->Init())) return nullptr;

	// ポインタを返す
	return pObjX;
}