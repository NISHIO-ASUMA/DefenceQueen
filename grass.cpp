//=====================================
//
// 草のビルボード処理 [ grass.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "grass.h"
#include "manager.h"

//=================================
// コンストラクタ
//=================================
CGrass::CGrass(int nPriority) : CObject3D(nPriority),
m_fRadius(NULL),
m_nNumAll(NULL),
m_pSphere(nullptr)
{

}
//=================================
// デストラクタ
//=================================
CGrass::~CGrass()
{

}
//=================================
// 生成処理
//=================================
CGrass* CGrass::Create(const D3DXVECTOR3 pos, int numgrass, float fradius)
{
	// インスタンス生成
	CGrass* pGrass = new CGrass;
	if (pGrass == nullptr) return nullptr;

	if (FAILED(pGrass->Init())) return nullptr;

	// オブジェクト設定
	pGrass->SetPos(pos);
	pGrass->SetSize(60.0f,40.0f);
	pGrass->SetTexture("grass000.png");
	pGrass->SetRot(VECTOR3_NULL);

	return pGrass;
}
//=================================
// 初期化処理
//=================================
HRESULT CGrass::Init(void)
{
	// 親クラスの初期化
	CObject3D::Init();

	return S_OK;
}
//=================================
// 終了処理
//=================================
void CGrass::Uninit(void)
{
	// 終了処理
	CObject3D::Uninit();
}
//=================================
// 更新処理
//=================================
void CGrass::Update(void)
{
	// 更新処理
	CObject3D::Update();
}
//=================================
// 描画処理
//=================================
void CGrass::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 描画処理
	CObject3D::Draw();
}