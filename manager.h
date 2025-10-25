//====================================
//
// マネージャー処理 [ manager.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**************************  
// 前方宣言
//**************************
class CInputKeyboard;
class CJoyPad;
class CInputMouse;
class CSound;
class CTexture;
class CCamera;
class CLight;
class CFade;
class CXfileManager;
class CScene;

//**************************  
// インクルードファイル
//**************************
#include <memory>
#include "scene.h"
#include "renderer.h"

//**************************
// マネージャークラス宣言
//**************************
class CManager
{
public:

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CRenderer* GetRenderer(void) { return m_pRenderer.get(); }
	CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard.get(); }
	CJoyPad* GetJoyPad(void) { return m_pJoyPad.get(); }
	CSound* GetSound(void) { return m_pSound.get(); }
	CInputMouse* GetMouse(void) { return m_pInputMouse.get(); }
	CTexture* GetTexture(void) { return m_pTexture.get(); }
	CCamera* GetCamera(void) { return m_pCamera.get(); }
	CLight* GetLight(void) { return m_pLight.get(); }
	CFade* GetFade(void) { return m_pFade.get(); }
	CXfileManager* GetXManager(void) { return m_pXfileManager.get(); }

	// シーン関連
	CScene* GetSceneRaw(void) { return m_pScene.get(); }	// 生ポインタを返す
	void SetScene(std::unique_ptr<CScene> pNewScene);	// unique_ptrで受け取る
	CScene::MODE GetScene(void);

	// インスタンス取得
	static CManager* GetInstance(void)
	{
		static CManager pManeger;
		return &pManeger;
	};

private:

	CManager();
	~CManager();

	std::unique_ptr<CRenderer>m_pRenderer;			// レンダラークラスのポインタ
	std::unique_ptr<CInputKeyboard>m_pInputKeyboard;// キーボードクラスのポインタ
	std::unique_ptr<CJoyPad>m_pJoyPad;				// ジョイパッドクラスのポインタ
	std::unique_ptr<CSound>m_pSound;				// サウンドオブジェクトのポインタ
	std::unique_ptr<CInputMouse>m_pInputMouse;		// マウスクラスのポインタ
	std::unique_ptr<CTexture>m_pTexture;			// テクスチャクラスのポインタ
	std::unique_ptr<CCamera>m_pCamera;				// カメラクラスのポインタ
	std::unique_ptr<CLight>m_pLight;				// ライトクラスのポインタ	
	std::unique_ptr<CScene>m_pScene;;				// シーン管理クラスのポインタ
	std::unique_ptr<CFade>m_pFade;					// フェードクラスのポインタ
	std::unique_ptr<CXfileManager>m_pXfileManager;	// Xファイルマネージャークラス
};