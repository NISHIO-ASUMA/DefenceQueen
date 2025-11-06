//=====================================
//
// マネージャー処理 [ manager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "manager.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "ranking.h"
#include "object.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "collision.h"
#include "fade.h"
#include "xfilemanager.h"

//===========================
// コンストラクタ
//===========================
CManager::CManager() :
m_pCamera(nullptr),
m_pFade(nullptr),
m_pInputKeyboard(nullptr),
m_pInputMouse(nullptr),
m_pJoyPad(nullptr),
m_pLight(nullptr),
m_pRenderer(nullptr),
m_pScene(nullptr),
m_pSound(nullptr),
m_pTexture(nullptr),
m_pXfileManager(nullptr)
{
	// 値のクリア
}
//===========================
// デストラクタ
//===========================
CManager::~CManager()
{
	
}
//===========================
// マネージャーの初期化処理
//===========================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// キーボードオブジェクトの生成処理
	m_pInputKeyboard = std::make_unique<CInputKeyboard>();

	// 初期化に失敗したら
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// ジョイパッドオブジェクトの生成処理
	m_pJoyPad = std::make_unique<CJoyPad>();

	// 初期化に失敗したら
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// マウスオブジェクトの生成処理
	m_pInputMouse = std::make_unique<CInputMouse>();

	// 初期化に失敗したら
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// サウンドの生成処理
	m_pSound = std::make_unique<CSound>();

	if (FAILED(m_pSound->Init(hWnd)))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// カメラの生成処理
	m_pCamera = std::make_unique<CCamera>();

	// 初期化に失敗したら
	if (FAILED(m_pCamera->Init()))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// レンダラーの生成処理
	m_pRenderer = std::make_unique <CRenderer>();

	// 初期化に失敗したら
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// ライト生成
	m_pLight = std::make_unique <CLight>();

	// 初期化に失敗したら
	if (FAILED(m_pLight->Init()))
	{
		// E_FAILを返す
		return E_FAIL;
	}

	// テクスチャ生成
	m_pTexture = std::make_unique <CTexture>();
	m_pTexture->Load();

	// Xファイルオブジェクトマネージャー生成
	m_pXfileManager = std::make_unique <CXfileManager>();
	m_pXfileManager->Load();

	// フェード生成
	m_pFade = std::make_unique <CFade>();

	// 初期化失敗時
	if (FAILED(m_pFade->Init()))
	{
		// -1を返す
		return E_FAIL;
	}

#ifdef _DEBUG
	// デバッグ用シーンセット
	m_pFade->SetFade(std::make_unique<CGame>());
#else
	// シーンセット
	m_pFade->SetFade(std::make_unique<CTitle>());
#endif // _DEBUG

	return S_OK;
}
//===========================
// マネージャーの終了処理
//===========================
void CManager::Uninit(void)
{
	// キーボードインスタンスの破棄
	m_pInputKeyboard.reset();

	// ゲームパッドインスタンスの破棄
	m_pJoyPad.reset();

	// マウスインスタンスの破棄
	m_pInputMouse.reset();

	// サウンドインスタンスの破棄
	m_pSound.reset();

	// カメラインスタンスの破棄
	m_pCamera.reset();

	// ライトインスタンスの破棄
	m_pLight.reset();

	// テクスチャインスタンスの破棄
	m_pTexture.reset();

	// モデルインスタンスの破棄
	m_pXfileManager.reset();

	// シーンの破棄
	if (m_pScene)
	{
		m_pScene->Uninit();
		m_pScene.reset();
	}

	// フェードの破棄
	if (m_pFade)
	{
		m_pFade->Uninit();
		m_pFade.reset();
	}

	// レンダラーの破棄
	if (m_pRenderer)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();
		m_pRenderer.reset();
	}
}
//===========================
// マネージャーの更新処理
//===========================
void CManager::Update()
{
	// キーボードの更新処理
	if (m_pInputKeyboard) m_pInputKeyboard->Update();

	// ジョイパッドの更新処理
	if (m_pJoyPad) m_pJoyPad->Update();

	// マウスの更新処理
	if (m_pInputMouse) m_pInputMouse->Update();

	// ジョイパッド振動の更新処理
	m_pJoyPad->UpdateVibration();

	// カメラ更新
	if (m_pCamera) m_pCamera->Update();

	// フェードの更新
	if (m_pFade) m_pFade->Update();

	// シーンの更新
	if (m_pScene) m_pScene->Update();

	// レンダラーの更新処理
	if (m_pRenderer) m_pRenderer->Update();
}
//===========================
// マネージャーの描画処理
//===========================
void CManager::Draw(void)
{
	// レンダラーの描画処理
	if (m_pRenderer) m_pRenderer->Draw();
}
//===========================
// シーンのセット
//===========================
void CManager::SetScene(std::unique_ptr<CScene> pNewScene)
{
	// nullptrじゃない
	if (m_pScene != nullptr)
	{
		// 終了処理
		m_pScene->Uninit();

		// nullじゃない
		if (m_pSound)
		{
			// サウンドの停止
			m_pSound->StopSound();
		}

		// 全オブジェクト破棄
		CObject::ReleaseAll();

		// 古いシーンを破棄
		m_pScene.reset();
	}

	// もしシーンが無かったら
	if (pNewScene)
	{
		// シーンの初期化
		if (FAILED(pNewScene->Init()))
		{
			// 失敗時
			MessageBox(GetActiveWindow(), "シーン初期化失敗", "例外スロー", MB_OK);
			pNewScene.reset();
			return;
		}

		// 所有権をマネージャに移動
		m_pScene = std::move(pNewScene);
	}
}
//===========================
// 現在シーン取得
//===========================
CScene::MODE CManager::GetScene(void)
{
	// nullptrじゃない
	if (m_pScene)
		return m_pScene->GetScene(); // 現在シーン
	else
		return CScene::MODE_NONE;	 // 何もないシーン
}