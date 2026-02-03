//=========================================================
//
// 数字パネルを表示するビルボード処理 [ numberpanel.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "numberpanel.h"
#include "texture.h"
#include "manager.h"

//=========================================================
// コンストラクタ
//=========================================================
CNumberPanel::CNumberPanel(int nPriority) : CBillboard(nPriority),m_nType(NULL)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CNumberPanel::~CNumberPanel()
{
	// 無し
}
//=========================================================
// 生成処理
//=========================================================
CNumberPanel* CNumberPanel::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nType)
{
	// インスタンス生成
	CNumberPanel* pPanel = new CNumberPanel;
	if (pPanel == nullptr) return nullptr;

	// オブジェクト設定
	pPanel->SetPos(pos);
	pPanel->SetRot(rot);
	pPanel->SetSize(Config::WIDTH, Config::HEIGHT);
	pPanel->SetType(nType);
	pPanel->SetTexture();

	// 初期化失敗時
	if (FAILED(pPanel->Init())) return nullptr;

	return pPanel;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CNumberPanel::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CNumberPanel::Uninit(void)
{
	// 親クラスの終了
	CBillboard::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CNumberPanel::Update(void)
{
	// 親クラスの更新
	CBillboard::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CNumberPanel::Draw(void)
{
	// 親クラスの描画
	CBillboard::Draw();
}
//=========================================================
// テクスチャ処理
//=========================================================
void CNumberPanel::SetTexture(void)
{
	// テクスチャクラスポインタ取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	if (pTexture == nullptr) return;

	// テクスチャパス格納
	const char* pTexName = {};

	// 種類によってテクスチャ設定変更
	switch (m_nType)
	{
	case TYPE_LITTLE: // 最小数
		pTexName = "number_little.png";
		break;

	case TYPE_MIDDLE: // 中間数
		pTexName = "number_middle.png";
		break;

	case TYPE_LARGE:  // 最大数
		pTexName = "number_large.png";
		break;

	default:
		pTexName = nullptr;
		break;
	}

	if (pTexName)
	{
		// テクスチャに割り当てる
		CBillboard::SetTexture(pTexName);
	}
	else
	{
		// テクスチャを付けない
		pTexName = nullptr;
		CBillboard::SetTexture(pTexName);
	}
}