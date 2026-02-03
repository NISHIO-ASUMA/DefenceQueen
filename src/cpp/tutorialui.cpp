//=========================================================
//
// チュートリアルUI処理 [ tutorialui.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "tutorialui.h"
#include "manager.h"

//=========================================================
// コンストラクタ
//=========================================================
CTutorialUi::CTutorialUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_fAlpha = 1.0f;
}
//=========================================================
// デストラクタ
//=========================================================
CTutorialUi::~CTutorialUi()
{
	// 破棄
	CObject2D::Uninit();
}
//=========================================================
// 生成処理
//=========================================================
CTutorialUi* CTutorialUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * pFileName,int nState)
{
	// インスタンス生成
	CTutorialUi* pTutoUi = new CTutorialUi;

	// インスタンス生成失敗時
	if (pTutoUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTutoUi->Init()))
	{
		return nullptr;
	}

	// オブジェクト2Dの基本設定
	pTutoUi->SetPos(pos);
	pTutoUi->SetSize(fWidth, fHeight);
	pTutoUi->SetTexture(pFileName);
	pTutoUi->SetState(nState);

	// 生成されたポインタを返す
	return pTutoUi;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTutorialUi::Init(void)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	// 頂点生成タイプを設定
	SetAnchor(CObject2D::ANCHORTYPE_CENTER);

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTutorialUi::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CTutorialUi::Update(void)
{
	// オブジェクト2Dの更新処理
	CObject2D::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CTutorialUi::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}
