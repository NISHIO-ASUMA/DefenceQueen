//===================================================================
//
// 餌命令キーのチュートリアルui状態処理 [ tutorialstatefeedorder.cpp ]
// Author: Asuma Nishio
//
//===================================================================

//*******************************************************************
// クラス定義インクルードファイル
//*******************************************************************
#include "tutorialstatefeedorder.h"

//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "manager.h"
#include "input.h"

//===================================================================
// 判別結果を返す
//===================================================================
bool CTutorialStateFeedOrder::OnCheck(void)
{
	auto key = CManager::GetInstance()->GetInputKeyboard();
	auto pad = CManager::GetInstance()->GetJoyPad();

	bool isKeyResult = key->GetTrigger(DIK_RETURN);
	bool isPadResult = pad->GetTrigger(pad->JOYKEY_A);

	// キー入力とパッド入力の結果を返す
	return isKeyResult || isPadResult;
}