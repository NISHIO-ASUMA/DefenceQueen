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
	~CSceneManagement();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};