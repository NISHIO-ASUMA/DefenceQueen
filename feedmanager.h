//===============================================
//
// 複数の餌を管理する処理 [ feedmanager.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <vector>

//**********************
// 前方宣言
//**********************
class CFeed;

//***************************
// 餌を管理するクラスを定義
//***************************
class CFeedManager
{
public:

	CFeedManager();
	~CFeedManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};