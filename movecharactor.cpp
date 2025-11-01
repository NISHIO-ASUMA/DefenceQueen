//==================================================
//
// 動くキャラクタークラス処理 [ movecharactor.cpp ]
// Author: Asuma Nishio
//
//==================================================

//************************
// インクルードファイル
//************************
#include "movecharactor.h"
#include "model.h"
#include "shadowS.h"
#include "manager.h"

//======================================
// コンストラクタ
//======================================
CMoveCharactor::CMoveCharactor(int nPriority) : CObject(nPriority),
m_pos(VECTOR3_NULL),
m_posOld(VECTOR3_NULL),
m_move(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_rotDest(VECTOR3_NULL),
m_scale(INITSCALE),
m_type(TYPE_NONE),
m_pModel{},
m_pMotion{},
m_pShadowS{},
m_fMoveValue(NULL)
{
	// 値のクリア
	D3DXMatrixIdentity(&m_mtxworld);
}
//======================================
// デストラクタ
//======================================
CMoveCharactor::~CMoveCharactor()
{

}
//======================================
// 初期化処理
//======================================
HRESULT CMoveCharactor::Init(void)
{
	// 変数の初期化
	m_pModel.clear();

	// モデル生成
	m_pShadowS = CShadowS::Create(m_pos, m_rot);

	return S_OK;
}
//======================================
// 終了処理
//======================================
void CMoveCharactor::Uninit(void)
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
//======================================
// 更新処理
//======================================
void CMoveCharactor::Update(void)
{
	//// 位置保存
	//m_posOld = m_pos;

	//// 座標を更新する
	//m_pos += m_move;

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.75f;
	m_move.z += (0.0f - m_move.z) * 0.75f;

	// 角度補完
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{// 左回転
		// 角度
		m_rot.y = m_rot.y + D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{// 右回転
		// 角度
		m_rot.y = m_rot.y - D3DX_PI * 2.0f;
	}

	// 現在の角度
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.25f;

	// ステンシルシャドウの更新
	if (m_pShadowS)
	{
		// オブジェクト設定
		m_pShadowS->SetPos(m_pos);
		m_pShadowS->SetRot(m_rot);
	}

	// モーションの更新処理
	m_pMotion->Update(m_pModel,m_pModel.size());
}
//======================================
// 描画処理
//======================================
void CMoveCharactor::Draw(void)
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
//======================================
// 位置情報の更新
//======================================
void CMoveCharactor::UpdatePosition(void)
{
	// 位置の更新
	m_posOld = m_pos;
	m_pos += m_move;
}
//======================================
// モーションロード処理
//======================================
void CMoveCharactor::MotionLoad(const char* pScriptName, int nDestMotions)
{
	// ポインタ生成
	m_pMotion = CMotion::Load(pScriptName, m_pModel, nDestMotions);
}