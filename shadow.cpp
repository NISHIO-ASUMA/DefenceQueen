//====================================
//
// 影処理 [ shadow.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "shadow.h"
#include "manager.h"

//**********************
// 名前空間
//**********************
namespace SHADOWINFO
{
	constexpr float SHADOW_SIZE = 30.0f; // 影の大きさ
}

//=================================
// オーバーロードコンストラクタ
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	// 値のクリア
}
//=================================
// デストラクタ
//=================================
CShadow::~CShadow()
{
	// 無し
}
//==================================
// 生成処理
//==================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成
	CShadow* pShadow = new CShadow;

	// nullptrだったら
	if (pShadow == nullptr) return nullptr;

	// オブジェクト設定
	pShadow->SetPos(pos);
	pShadow->SetRot(rot);
	pShadow->SetSize(SHADOWINFO::SHADOW_SIZE, SHADOWINFO::SHADOW_SIZE);
	pShadow->SetTexture("shadow000.jpg");

	// 初期化失敗時
	if (FAILED(pShadow->Init()))
	{
		// 処理を返す
		return nullptr;
	}

	// 影のポインタを返す
	return pShadow;
}
//=================================
// 影の初期化処理
//=================================
HRESULT CShadow::Init(void)
{
	// 親クラスの初期化
	CObject3D::Init();

	return S_OK;
}
//=================================
// 影の終了処理
//=================================
void CShadow::Uninit(void)
{
	// 親クラスの終了処理
	CObject3D::Uninit();
}
//=================================
// 影の更新処理
//=================================
void CShadow::Update(void)
{
	// 無し
}
//=================================
// 影の描画処理
//=================================
void CShadow::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 親クラスの描画
	CObject3D::Draw();

	// 減算合成を戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
