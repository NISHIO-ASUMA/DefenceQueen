//=========================================================
// 
// UI処理 [ ui.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "easing.h"

//=========================================================
// オーバーロードコンストラクタ
//=========================================================
CUi::CUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_isFlash = false;
	m_nFlashFrame = NULL;
}
//=========================================================
// デストラクタ
//=========================================================
CUi::~CUi()
{
	// 無し
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CUi::Init(void)
{
	// オブジェクトの初期化
	CObject2D::Init();

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CUi::Uninit(void)
{
	// オブジェクトの終了
	CObject2D::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CUi::Update(void)
{
	// 点滅有効時
	if (m_isFlash)
	{
		// 点滅処理
		SetFlash(NULL, m_nFlashFrame, COLOR_WHITE);
	}

	// 親クラス更新
	CObject2D::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CUi::Draw(void)
{
	// オブジェクトの描画
	CObject2D::Draw();
}
//=========================================================
// 生成処理
//=========================================================
CUi* CUi::Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight, const char* Filename, bool isUse)
{
	// インスタンス生成
	CUi* pUi = new CUi;
	if (pUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pUi->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	pUi->SetPos(pos);
	pUi->SetSize(fWidth, fHeight);
	pUi->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pUi->SetTexture(Filename);
	pUi->m_nFlashFrame = nFlashFrame;
	pUi->m_isFlash = isUse;

	// 生成されたポインタを返す
	return pUi;
}