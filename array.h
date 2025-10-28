//===================================================
//
// プレイヤーの仲間処理 [ array.h ]
// Author: Asuma Nishio
//
//===================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "movecharactor.h"
#include <memory>

//**********************
// 前方宣言
//**********************
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CMotion;

//********************************
// プレイヤーの仲間クラスを定義
//********************************
class CArray : public CMoveCharactor
{
public:
	CArray(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CArray();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

};