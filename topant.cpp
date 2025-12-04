//=========================================================
//
// 各スポナーの仲間に指示を出すアリのクラス [ topant.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "topant.h"

//=========================================================
// コンストラクタ
//=========================================================
CTopAnt::CTopAnt(int nPriority) : CMoveCharactor(nPriority)
{
	
}
//=========================================================
// デストラクタ
//=========================================================
CTopAnt::~CTopAnt()
{

}
//=========================================================
// 生成処理
//=========================================================
CTopAnt* CTopAnt::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// インスタンス生成
	CTopAnt* pTop = new CTopAnt;
	if (pTop == nullptr) return nullptr;

	// オブジェクト設定
	pTop->SetPos(pos);
	pTop->SetRot(rot);
	pTop->SetUseStencil(false);

	// 初期化失敗時
	if FAILED(pTop->Init()) return nullptr;

	return pTop;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTopAnt::Init(void)
{
	// 親クラスの初期化
	CMoveCharactor::Init();

	// モーションロード
	MotionLoad("data/MOTION/Enemy/Enemy_Motion.txt", 2, true);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTopAnt::Uninit(void)
{
	// 親クラスの終了処理
	CMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CTopAnt::Update(void)
{
	// 親クラスの更新
	CMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CTopAnt::Draw(void)
{
	// 親クラスの描画
	CMoveCharactor::Draw();
}
//=========================================================
// キー入力移動
//=========================================================
void CTopAnt::Moving(void)
{
#if 0
	// 移動量を取得
	D3DXVECTOR3 move = GetMove();

	// 入力デバイス取得
	CJoyPad* pPad = CManager::GetInstance()->GetJoyPad();
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();

	// パッドのスティック入力があったら
	if (pPad->GetLeftStick()) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	if (pKey->GetPress(DIK_A) || pPad->GetPress(CJoyPad::JOYKEY_LEFT))
	{// Aキー

		if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
		{// 左斜め上

			move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
			move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// 右斜め下

			move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
			move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else
		{// 単体
			move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
			move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
		}
	}
	else if (pKey->GetPress(DIK_D) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
	{// Dキーを押した

		if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
		{// Wキーを押した
			move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
			move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// Sキーを押した
			move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
			move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else
		{// Dキーのみ押した
			move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
			move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
		}
	}
	else if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
	{// Wキーを押した

		move.x += sinf(pCamera->GetRot().y) * SELECTOR::SPEED;
		move.z += cosf(pCamera->GetRot().y) * SELECTOR::SPEED;
	}
	else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
	{// Sキーを押した

		move.x -= sinf(pCamera->GetRot().y) * SELECTOR::SPEED;
		move.z -= cosf(pCamera->GetRot().y) * SELECTOR::SPEED;
	}

	// 適用
	SetMove(move);

#endif
}
//=========================================================
// パッド入力移動
//=========================================================
void CTopAnt::MovePad(void)
{

}
