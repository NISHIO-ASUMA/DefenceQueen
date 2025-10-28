//===========================================================================================
//
// 各シーンごとで出現するObjectManagerクラスを一括管理する処理 [ sceneobjectmanagement.h ]
// Author: Asuma Nishio
//
//===========================================================================================

//**********************
// インクルードガード
//**********************
#pragma once

//*************************************************
// オブジェクトマネージャーを管理するクラスを定義
//*************************************************
class CSceneObjectManagement
{
public:

	CSceneObjectManagement();
	~CSceneObjectManagement();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};