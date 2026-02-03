//=========================================================
//
// ポップアップナンバー表示処理 [ popupnumber.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "popupnumber.h"

//=========================================================
// コンストラクタ
//=========================================================
CPopUpNumber::CPopUpNumber(int nPriority) : CBillboard(nPriority),m_nLife(NULL)
{

}
//=========================================================
// デストラクタ
//=========================================================
CPopUpNumber::~CPopUpNumber()
{

}
//=========================================================
// 生成処理
//=========================================================
CPopUpNumber* CPopUpNumber::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fWidth, const float fHeight, const int nLife)
{
	// インスタンス生成
	CPopUpNumber* pPop = new CPopUpNumber;
	if (pPop == nullptr) return nullptr;

	// オブジェクト設定
	pPop->SetPos(pos);
	pPop->SetRot(rot);
	pPop->SetSize(fWidth, fHeight);
	pPop->SetTexture("Popnumber.png");
	pPop->SetLife(nLife);

	// 初期化失敗時
	if (pPop->Init()) return nullptr;

	return pPop;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CPopUpNumber::Init(void)
{
	// 親クラスの初期化処理
	CBillboard::Init();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CPopUpNumber::Uninit(void)
{
	// 体力値を減算
	m_nLife--;

	// 寿命が尽きたら
	if (m_nLife <= NULL)
	{
		// 終了処理
		Uninit();
		return;
	}

	// 親クラスの終了処理
	CBillboard::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CPopUpNumber::Update(void)
{
	// 親クラスの更新処理
	CBillboard::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CPopUpNumber::Draw(void)
{
	// 親クラスの描画処理
	CBillboard::Draw();
}