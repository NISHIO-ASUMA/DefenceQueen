//=========================================================
//
// チュートリアルUI処理 [ tutorialui.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// クラス定義ヘッダーファイル
//*********************************************************
#include "tutorialui.h"

//*********************************************************
// インクルードファイル
//*********************************************************
#include "manager.h"

//*********************************************************
// 定数名前空間
//*********************************************************
namespace TutorialUi
{
	const D3DXVECTOR3 DestPos = { 1080.0f,110.0f,0.0f }; // 目的座標
};

//=========================================================
// コンストラクタ
//=========================================================
CTutorialUi::CTutorialUi(int nPriority) : CObject2D(nPriority),
m_isAlpha(false),
m_isActive(false),
m_isCheck(false),
m_fAlpha(1.0f)
{

}
//=========================================================
// デストラクタ
//=========================================================
CTutorialUi::~CTutorialUi()
{

}
//=========================================================
// 生成処理
//=========================================================
CTutorialUi* CTutorialUi::Create
(
	const D3DXVECTOR3& pos,
	const float& fWidth,
	const float& fHeight,
	const char* pFileName
)
{
	// インスタンス生成
	CTutorialUi* pTutoUi = new CTutorialUi;
	if (pTutoUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTutoUi->Init())) return nullptr;

	// オブジェクト2Dの基本設定
	pTutoUi->SetPos(pos);
	pTutoUi->SetSize(fWidth, fHeight);
	pTutoUi->SetTexture(pFileName);

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
	if (!m_isActive) return;

	// フェードアウト中
	if (m_isAlpha)
	{
		m_fAlpha -= Config::DECALPHA;
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

		if (m_fAlpha <= 0.0f)
		{
			m_fAlpha = 0.0f;
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
		}
	}

	// 座標取得
	auto pos = GetPos();

	// x座標を比較し目的座標へ移動
	if (pos.x > TutorialUi::DestPos.x)
	{
		pos.x -= Config::MOVE;

		if (pos.x <= TutorialUi::DestPos.x)
		{
			pos.x = TutorialUi::DestPos.x;
			SetPos(pos);
			m_isCheck = true;
			return;
		}
	}

	// 座標を設定
	SetPos(pos);

	// オブジェクト2Dの更新処理
	CObject2D::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CTutorialUi::Draw(void)
{
	if (!m_isActive) return;

	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}