//===================================================================
//
// 移動キーのチュートリアルui状態処理 [ tutorialstatemove.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義ヘッダーファイル
//*******************************************************************
#include "tutorialstatemove.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "manager.h"
#include "input.h"

//===================================================================
// 判別結果を返す
//===================================================================
bool CTutorialStateMove::OnCheck(void)
{
	auto key = CManager::GetInstance()->GetInputKeyboard();
	auto pad = CManager::GetInstance()->GetJoyPad();

	bool isKeyResult = key->GetPress(DIK_W) || key->GetPress(DIK_A) || key->GetPress(DIK_S) || key->GetPress(DIK_D);
	bool isPadResult = pad->GetLeftStick();

	// キー入力とパッドの入力結果を返す
	return	isKeyResult || isPadResult;
}