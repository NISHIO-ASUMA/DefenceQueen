//=========================================================
// 
// インスタンシングシェーダークラス [ instancing.cpp ]
// Author : Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "instancing.h"

//=========================================================
// コンストラクタ
//=========================================================
CInstancing::CInstancing() : m_pInstanceDevice{},m_pInstancing(nullptr)
{

}
//=========================================================
// デストラクタ
//=========================================================
CInstancing::~CInstancing()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CInstancing::Init(const char* pShaderFile)
{
	// ローカル変数
	LPD3DXBUFFER pErr = nullptr;

	// シェーダーファイル読み込み
	HRESULT hr = D3DXCreateEffectFromFile
	(
		m_pInstanceDevice,		// デバイス
		pShaderFile,			// 読み込み対象ファイル
		nullptr,
		nullptr,
		D3DXSHADER_DEBUG,
		nullptr,
		&m_pInstancing,		// エフェクトポインタ
		&pErr
	);

	// 読み込み失敗時
	if (FAILED(hr))
	{
		if (pErr)
		{
			// エラーメッセージ表示
			MessageBoxA(nullptr,
				(char*)pErr->GetBufferPointer(),
				"Instancing.hlslが読み込めません",
				MB_OK);

			// 解放
			pErr->Release();
		}

		return hr;
	}

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CInstancing::Uninit(void)
{
	// エフェクトポインタの破棄
	if (m_pInstancing)
	{
		m_pInstancing->Release();
		m_pInstancing = nullptr;
	}
}
//=========================================================
// シェーダー開始関数
//=========================================================
void CInstancing::Begin(void)
{
	m_pInstancing->Begin(0,0);
}
//=========================================================
// パス開始関数
//=========================================================
void CInstancing::BeginPass(const int nPass)
{
	m_pInstancing->BeginPass(nPass);
}
//=========================================================
// パス終了関数
//=========================================================
void CInstancing::EndPass(void)
{
	m_pInstancing->EndPass();
}
//=========================================================
// シェーダー終了関数
//=========================================================
void CInstancing::End(void)
{
	m_pInstancing->End();
}
//=========================================================
// インスタンシングパラメーター設定
//=========================================================
void CInstancing::SetInstancingParam(const float &col)
{
	// ポインタが無かったら
	if (!m_pInstancing) return;

	// 行列を取得する
	D3DXMATRIX mtxProj, mtxView;
	m_pInstanceDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);	// プロジェクションマトリックス
	m_pInstanceDevice->GetTransform(D3DTS_VIEW, &mtxView);			// ビューマトリックス

	// シェーダーのテクニック宣言を取得
	D3DXHANDLE hTech = m_pInstancing->GetTechniqueByName("Instancing");
	m_pInstancing->SetTechnique(hTech);

	// シェーダーに書かれているパラメータを設定
	m_pInstancing->SetMatrix("g_mtxprojection", &mtxProj);
	m_pInstancing->SetMatrix("g_mtxview", &mtxView);
	m_pInstancing->SetFloat("g_ObjectCol", col);

	// コミット切り替え
	m_pInstancing->CommitChanges();
}