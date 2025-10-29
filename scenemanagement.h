//=============================================================================
//
// 各シーンごとに使うManagerクラスを一括管理する処理 [ scenemanagement.h ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**************************
// インクルードファイル宣言
//**************************
#include <memory>

//**********************
// 前方宣言
//**********************
class CSceneManageBase;
class CTitleManager;
class CGameManager;
class CTutorialManager;
class CResultManager;
class CRankingManager;

//**********************************************
// 各シーンのマネージャーを管理するクラスを定義
//**********************************************
class CSceneManagement
{
public:

	//***********************
	// 使用シーンの種類
	//***********************
	enum TYPE
	{
		TYPE_NONE,
		TYPE_TITLE,
		TYPE_TUTORIAL,
		TYPE_GAME,
		TYPE_RESULT,
		TYPE_RANKING,
		TYPE_MAX
	};

	CSceneManagement();
	~CSceneManagement();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// 更新するクラスを切り替える処理
	/// </summary>
	/// <param name="NewType">変更先の種類</param>
	void ChangeScene(TYPE NewType);

	CSceneManageBase* GetManagerBase(void) { return m_pCurrentManager.get(); }

private:
	TYPE m_CurrentScene;								 // 現在の使用シーン
	std::unique_ptr<CSceneManageBase> m_pCurrentManager; // 現在のマネージャークラス
};