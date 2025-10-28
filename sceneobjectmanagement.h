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
	virtual ~CSceneObjectManagement();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:

};