//=============================================================================
//
// シーンベースクラス [ scenemanagebase.h ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// インクルードガード
//**********************
#pragma once

//************************
// 管理ベースクラスを定義
//************************
class CSceneManageBase
{
public:

	CSceneManageBase() {};
	virtual ~CSceneManageBase() {}
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

