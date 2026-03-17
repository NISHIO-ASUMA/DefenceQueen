//===================================================================
//
// 分断キーのチュートリアルui状態処理 [ tutorialstatesepalation.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義インクルードファイル
//*******************************************************************
#include "tutorialstatesepalation.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "manager.h"
#include "input.h"

//===================================================================
// 判別結果を返す
//===================================================================
bool CTutorialStateSepalation::OnCheck(void)
{
	auto key = CManager::GetInstance()->GetInputKeyboard();
	auto pad = CManager::GetInstance()->GetJoyPad();

	bool isKeyResult = key->GetPress(DIK_SPACE);
	bool isPadResult = pad->GetPress(pad->JOYKEY_X);

	// キー入力とパッド入力の結果を返す
	return isKeyResult || isPadResult;
}
