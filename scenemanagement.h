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

//*************************************
// マネージャーを管理するクラスを定義
//*************************************
class CSceneManagement
{
public:

	CSceneManagement();
	virtual ~CSceneManagement();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:

};