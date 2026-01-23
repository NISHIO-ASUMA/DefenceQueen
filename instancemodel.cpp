//=========================================================
//
// インスタンシング適用モデル処理 [ instancingmodel.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "instancemodel.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "instancemodelmanager.h"
#include "instancing.h"
#include "pausemanager.h"

//=========================================================
// コンストラクタ
//=========================================================
CInstanceModel::CInstanceModel() : m_pParent(nullptr),
m_pTexture(nullptr),
m_nModelIdx(-1),
m_nUpdateCount(NULL),
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_offPos(VECTOR3_NULL),
m_offRot(VECTOR3_NULL),
m_scale(INITSCALE),
m_isShadow(false),
m_isInst(false),
m_mtxworld{},
m_Locla{}
{
}
//=========================================================
// デストラクタ
//=========================================================
CInstanceModel::~CInstanceModel()
{
	// 無し
}
//=========================================================
// 生成処理
//=========================================================
CInstanceModel* CInstanceModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename, const bool isShadow)
{
	// インスタンス生成
	CInstanceModel* pModelinst = new CInstanceModel;
	if (pModelinst == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pModelinst->Init(pos, rot, pFilename, isShadow))) return  nullptr;

	// ポインタを返す
	return pModelinst;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CInstanceModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename, const bool isShadow)
{
	// モデルセット
	SetModelPass(pFilename);

	// 位置の設定
	m_pos = pos;
	m_rot = rot;

	// オフセット位置を設定
	m_offPos = pos;
	m_offRot = rot;

	// フラグを設定する
	SetMtxShadow(isShadow);

	// 結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CInstanceModel::Uninit(void)
{
	// 無し
}
//=========================================================
// 更新処理
//=========================================================
void CInstanceModel::Update(D3DXMATRIX mtx)
{
	// インデックスが-1なら
	if (m_nModelIdx == -1)
		return;

	// デバイスポインタを取得
	const auto& Rendere = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Rendere->GetDevice();

	// カウント加算
	m_nUpdateCount++;

	if (m_nUpdateCount < MAX_UPDATECOUNT)
	{
		// インスタンシングに登録
		Rendere->AddInstanceObject(m_nModelIdx, this);
		return;
	}

	// 更新カウントを初期化する
	m_nUpdateCount = 0;
	
	// ファイルマネージャー取得
	CInstanceModelManager* pIMgr = CManager::GetInstance()->GetInstanceModelM();
	if (!pIMgr) return;

	// 配列情報
	const auto& fileData = pIMgr->GetList();
	if (m_nModelIdx >= static_cast<int>(fileData.size())) return;

	// 配列取得
	const auto& model = fileData[m_nModelIdx];
	if (!model.pMesh) return;

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_offRot.y, m_rot.x + m_offRot.x, m_rot.z + m_offRot.z);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offPos.x, m_pos.y + m_offPos.y, m_pos.z + m_offPos.z);

	// マトリックスに反映
	m_mtxworld = mtxScale * mtxRot * mtxTrans;

	// 親のペアネント格納用変数
	D3DXMATRIX mtxParent;

	if (m_pParent != nullptr)
	{// 親が存在する
		// ワールドマトリックス取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// 親が存在しない
		// マトリックスを取得
		mtxParent = mtx;
	}

	// 親のマトリックスとかけ合わせる
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxParent);

	// インスタンシングに登録
	Rendere->AddInstanceObject(m_nModelIdx,this);
}
//=========================================================
// 描画処理
//=========================================================
void CInstanceModel::Draw(D3DXMATRIX mtx)
{
	if (!CPauseManager::GetPause())
	{
		return;
	}

	// デバイスポインタを取得
	const auto& Rendere = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Rendere->GetDevice();

	// ファイルマネージャー取得
	CInstanceModelManager* pIMgr = CManager::GetInstance()->GetInstanceModelM();
	if (!pIMgr) return;

	// 配列情報
	const auto& fileData = pIMgr->GetList();
	if (m_nModelIdx >= static_cast<int>(fileData.size())) return;

	// 配列取得
	const auto& model = fileData[m_nModelIdx];
	if (!model.pMesh) return;

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 拡大率を反映
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
		mtxParent = mtx;
	}

	// 親のマトリックスとかけ合わせる
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// 現在のマテリアル
	pDevice->GetMaterial(&matDef);

	// マテリアルが取得できたら
	if (model.pBuffMat)
	{
		// マテリアルデータのポインタ
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();

		// テクスチャ取得
		CTexture* pTex = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < static_cast<int>(model.dwNumMat); nCnt++)
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
//=========================================================
// モデルパス設定
//=========================================================
void CInstanceModel::SetModelPass(const char* pModelName)
{
	// マネージャーから取得
	const auto& InstModelManager = CManager::GetInstance()->GetInstanceModelM();
	if (InstModelManager == nullptr) return;

	// インデックスセット
	m_nModelIdx = InstModelManager->Register(pModelName);
}
//=========================================================
// 親設定
//=========================================================
void CInstanceModel::SetParent(CInstanceModel* pModel)
{
	// 親モデルを設定する
	m_pParent = pModel;
}