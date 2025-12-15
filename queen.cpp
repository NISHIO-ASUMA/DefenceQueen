//=========================================================
//
// 防衛対象の処理 [ queen.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "queen.h"
#include "collisionsphere.h"
#include "spherecollider.h"
#include "parameter.h"
#include "statemachine.h"
#include "manager.h"
#include "renderer.h"

//=========================================================
// コンストラクタ
//=========================================================
CQueen::CQueen(int nPriority) : CNoMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pOutLine(nullptr)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CQueen::~CQueen()
{

}
//=========================================================
// 生成処理
//=========================================================
CQueen* CQueen::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成
	CQueen* pQueen = new CQueen;
	if (pQueen == nullptr) return nullptr;

	// オブジェクト設定
	pQueen->SetPos(pos);
	pQueen->SetRot(rot);
	pQueen->SetUseStencil(false);

	// 初期化失敗時
	if (FAILED(pQueen->Init())) return nullptr;

	// 生成されたポインタ
	return pQueen;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CQueen::Init(void)
{
	// 親クラスの初期化
	CNoMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_QUEEN);

	// モーションセット
	MotionLoad("data/MOTION/Queen/Queen_Motion.txt", MOTION_MAX,true);

	// パラメーター生成
	m_pParameter = std::make_unique<CParameter>();
	m_pParameter->SetMaxHp(QueenInfo::Hp);
	m_pParameter->SetHp(QueenInfo::Hp);

	//// ステートマシンを生成
	//m_pStateMachine = std::make_unique<CStateMachine>();

	//// 初期状態をセット
	//// ChangeState(ID_NEUTRAL);

	// コライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), QueenInfo::HitRange);

	// モーション取得
	m_pMotion = CNoMoveCharactor::GetMotion();

	// 拡大する
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

//-------------------------------------------------
	LPD3DXBUFFER pErr = nullptr; // ローカル変数

	// シェーダー読み込み
	HRESULT hr = D3DXCreateEffectFromFile(
		pDevice,						// デバイス
		"data/Outline.hlsl",			// ファイル
		nullptr,
		nullptr,
		D3DXSHADER_DEBUG,
		nullptr,
		&m_pOutLine,			// ポインタ
		&pErr
	);

	// 読み込み失敗時
	if (FAILED(hr))
	{
		if (pErr)
		{
			MessageBoxA(nullptr,
				(char*)pErr->GetBufferPointer(),
				"Outline Effect Error",
				MB_OK);
			pErr->Release();
		}

		return hr;
	}
//-------------------------------
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CQueen::Uninit(void)
{
	// ポインタ破棄
	m_pParameter.reset();

	// ステート終了処理
	// m_pStateMachine.reset();

	// コライダー破棄
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// 親クラスの終了処理
	CNoMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CQueen::Update(void)
{
	// 現在座標を取得
	D3DXVECTOR3 pos = GetPos();

	// コライダーの位置更新
	m_pSphereCollider->SetPos(pos);

	// 親クラスの更新
	CNoMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CQueen::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 親クラスの描画
	CNoMoveCharactor::Draw();

//-----------------------------
// アウトライン適用
//-----------------------------

	// ポインタが無かったら
	if (!m_pOutLine) return;

	// 行列を取得する
	D3DXMATRIX mtxWorld,mtxProj, mtxView;

	mtxWorld = GetWorldMtx();							// ワールドマトリックス
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);  // プロジェクション
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);		// ビューマトリックス

	// かけ合わせる
	D3DXMATRIX mtxViewProj = mtxView * mtxProj;

	// シェーダーにセットする
	m_pOutLine->SetMatrix("g_mtxWorld", &mtxWorld);
	m_pOutLine->SetMatrix("g_mtxViewProj", &mtxViewProj);

	// アウトライン幅
	float outlineWidth = 0.5f;
	m_pOutLine->SetFloat("g_fOutlineWidth", outlineWidth);

	// アウトラインカラー
	D3DXVECTOR4 color(1, 0, 0, 1); // 赤
	m_pOutLine->SetVector("g_Color", &color);

	// テクニック取得
	D3DXHANDLE hTech = m_pOutLine->GetTechniqueByName("OutLine");
	m_pOutLine->SetTechnique(hTech);

	// カリング反転
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	UINT passNum = 0;
	m_pOutLine->Begin(&passNum, 0);

	for (UINT i = 0; i < passNum; ++i)
	{
		// パス開始
		m_pOutLine->BeginPass(i);

		// モデル描画
		CNoMoveCharactor::DrawOnly();

		// パス解除
		m_pOutLine->EndPass();
	}
	
	// 終了
	m_pOutLine->End();

	// カリング戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//=========================================================
// 当たり判定処理
//=========================================================
bool CQueen::Collision(CSphereCollider* pOther)
{
	// 球同士の当たり判定を返す
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}