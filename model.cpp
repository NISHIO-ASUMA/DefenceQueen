//=========================================================
//
// モデル処理 [ model.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "model.h"
#include "manager.h"
#include "texture.h"

//=========================================================
// コンストラクタ
//=========================================================
CModel::CModel() : m_dwNumMat{},
m_pBuffMat(nullptr),
m_pMesh(nullptr),
m_pTexture(nullptr),
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_offPos(VECTOR3_NULL),
m_offRot(VECTOR3_NULL),
m_scale(INITSCALE),
m_parttype(PARTTYPE_NONE),
m_isColorChange(false),
m_isShadow(false)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CModel::~CModel()
{
	// 無し
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char * pFilename,const bool isShadow)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// 位置の設定
	m_pos = pos;
	m_rot = rot;

	// オフセットを代入
	m_offPos = pos;
	m_offRot = rot;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// テクスチャインデックス配列の動的確保
	m_pTexture = new int[m_dwNumMat];

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// テクスチャが読み込めたら
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			// テクスチャポインタ取得
			CTexture* pTexture = CManager::GetInstance()->GetTexture();

			// テクスチャセット
			m_pTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_pTexture[nCntMat] = -1; // テクスチャなし
		}
	}

	// フラグを設定する
	SetMtxShadow(isShadow);

	// 結果を返す
	return S_OK;
}
//=========================================================
// 生成処理
//=========================================================
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename,const bool isShadow)
{
	// インスタンス生成
	CModel* pModel = new CModel;
	if (pModel == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pModel->Init(pos, rot, pFilename,isShadow))) return  nullptr;

	// ポインタを返す
	return pModel;
}
//=========================================================
// 終了処理
//=========================================================
void CModel::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	// マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	// テクスチャポインタの破棄
	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}
//=========================================================
// 更新処理
//=========================================================
void CModel::Update(void)
{

}
//=========================================================
// 描画処理
//=========================================================
void CModel::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScale);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_offRot.y, m_rot.x + m_offRot.x, m_rot.z + m_offRot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offPos.x, m_pos.y + m_offPos.y, m_pos.z + m_offPos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// 親のペアネント格納用変数
	D3DXMATRIX mtxParent;

	if (m_pParent != nullptr)
	{// 親が存在する
		// ワールドマトリックス取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// 親が存在しない
		// マトリックス取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 親のマトリックスとかけ合わせる
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// 現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < static_cast<int>(m_dwNumMat); nCntMat++)
	{
		// カラー変更マテリアル
		if (m_isColorChange)
		{
			D3DXMATERIAL Col = pMat[nCntMat];

			Col.MatD3D.Diffuse.a = 0.5f;

			// マテリアル設定
			pDevice->SetMaterial(&Col.MatD3D);
		}
		else
		{
			// マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}


		// インデックスに応じて変更する
		if (m_pTexture[nCntMat] != -1)
		{
			// テクスチャ取得
			CTexture* pTexture = CManager::GetInstance()->GetTexture();

			// テクスチャセット
			pDevice->SetTexture(0, pTexture->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			// テクスチャなし
			pDevice->SetTexture(0, nullptr); 
		}

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);

	// 有効なら
	if (m_isShadow)
	{
		DrawMtxShadow();
	}
}
//=========================================================
// マトリックスシャドウ処理
//=========================================================
void CModel::DrawMtxShadow(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice) return;

	// ライト方向
	D3DXVECTOR4 lightDir(0.2f, -0.63f, -0.02f, 0.0f);

	// 平面投影座標を設定
	D3DXPLANE plane;
	D3DXVECTOR3 point = D3DXVECTOR3(0.0f, 0.7f, 0.0f);
	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f, -0.7f, 0.0f);
	D3DXPlaneFromPointNormal(&plane, &point, &normal);

	// 影マトリックス生成
	D3DXMATRIX mtxShadow;
	D3DXMatrixShadow(&mtxShadow, &lightDir, &plane);

	// 影をモデルの位置に合わせる
	D3DXMATRIX mtxWorldShadow;
	D3DXMatrixMultiply(&mtxWorldShadow, &m_mtxworld, &mtxShadow);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldShadow);

	// 半透明に設定
	D3DMATERIAL9 shadowMat = {};
	shadowMat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.35f);
	shadowMat.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.35f);

	// マテリアルセット
	pDevice->SetMaterial(&shadowMat);

	// メッシュ描画
	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{
		m_pMesh->DrawSubset(nCnt);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&shadowMat);
}
//=========================================================
// 親パーツ設定処理
//=========================================================
void CModel::SetParent(CModel* pModel)
{
	// 設定
	m_pParent = pModel;
}