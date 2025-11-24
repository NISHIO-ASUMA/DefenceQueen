//=========================================================
//
// 動かないキャラクタークラス処理 [ nomovecharactor.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "nomovecharactor.h"
#include "motion.h"
#include "model.h"
#include "shadowS.h"
#include "manager.h"
#include "blackboard.h"

//=========================================================
// コンストラクタ
//=========================================================
CNoMoveCharactor::CNoMoveCharactor(int nPriority) : CObject(nPriority),
m_pos(VECTOR3_NULL),
m_posOld(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_rotDest(VECTOR3_NULL),
m_scale(INITSCALE),
m_type(TYPE_NONE),
m_pModel{},
m_pMotion{},
m_pShadowS{}
{
	// 値のクリア
	D3DXMatrixIdentity(&m_mtxworld);
}
//=========================================================
// デストラクタ
//=========================================================
CNoMoveCharactor::~CNoMoveCharactor()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CNoMoveCharactor::Init(void)
{
	// 変数の初期化
	m_pModel.clear();

	// モデル生成
	m_pShadowS = CShadowS::Create(m_pos, m_rot);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CNoMoveCharactor::Uninit(void)
{
	// 動的確保分のモデルの破棄
	for (auto iter = m_pModel.begin(); iter != m_pModel.end(); iter++)
	{
		// nullチェック
		if ((*iter) != nullptr)
		{
			// 終了処理
			(*iter)->Uninit();

			// ポインタの破棄
			delete (*iter);

			// null初期化
			(*iter) = nullptr;
		}
	}

	// 配列のクリア
	m_pModel.clear();

	// ポインタ破棄
	m_pMotion.reset();

	// 自身の破棄
	CObject::Release();
}
//=========================================================
// 更新処理
//=========================================================
void CNoMoveCharactor::Update(void)
{
	// ステンシルシャドウ更新
	if (m_pShadowS)
	{
		// オブジェクト設定
		m_pShadowS->SetPos(m_pos);
		m_pShadowS->SetRot(m_rot);
	}

	// モーションの更新処理
	m_pMotion->Update(m_pModel, m_pModel.size());
}
//=========================================================
// 描画処理
//=========================================================
void CNoMoveCharactor::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxScal, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// モデルの描画
	for (auto& model : m_pModel)
	{
		model->Draw();
	}
}
//=========================================================
// モーション読み込み
//=========================================================
void CNoMoveCharactor::MotionLoad(const char* pScriptName, int nDestMotions)
{
	// ポインタ生成
	m_pMotion = CMotion::Load(pScriptName, m_pModel, nDestMotions);
}