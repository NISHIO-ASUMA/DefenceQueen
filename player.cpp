//=========================================
//
// プレイヤー処理 [ player.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "player.h"
#include "manager.h"
#include "texture.h"
#include "particle.h"
#include "shadow.h"
#include "meshimpact.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "parameter.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstate.h"
#include "effect.h"
#include "game.h"
#include "effectsmoke.h"
#include "sound.h"
#include "statemachine.h"
#include "boxcollider.h"
#include "collisionbox.h"
#include "motion.h"

//**********************
// 名前空間
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 4.5f;		 // 1フレームの移動量
	constexpr float NorRot = D3DX_PI * 2.0f; // 正規化値
};

//**********************
// 静的メンバ変数宣言
//**********************
bool CPlayer::m_isDeath = false;  // 死亡フラグ

//===============================
// オーバーロードコンストラクタ
//===============================
CPlayer::CPlayer(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CPlayer::~CPlayer()
{
	// 無し
}
//===============================
// プレイヤー生成処理
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife, const char* pFilename)
{
	// プレイヤーのインスタンス生成
	CPlayer* pPlayer = new CPlayer;
	if (pPlayer == nullptr) return nullptr;

	// オブジェクト設定
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	// ポインタ生成
	pPlayer->m_pParameter = std::make_unique<CParameter>();

	// nullチェック
	if (pPlayer->m_pParameter != nullptr)
	{
		// 体力パラメーターを設定
		pPlayer->m_pParameter->SetHp(nLife);
		pPlayer->m_pParameter->SetMaxHp(nLife);
	}
	
	// プレイヤー初期化処理
	if (FAILED(pPlayer->Init()))
	{
		// nullptrを返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}
//===============================
// プレイヤー初期化処理
//===============================
HRESULT CPlayer::Init(void)
{
	// キャラクタ―の初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_PLAYER);

	// モーションセット
	MotionLoad("data/MOTION/Player/Player100motion.txt", MOTION_MAX);

	// ステートマシンを生成
	m_pStateMachine = std::make_unique<CStateMachine>();

	// 初期状態をセット
	ChangeState(new CPlayerStateNeutral,CPlayerStateBase::ID_NEUTRAL); 

	// コライダー生成
	m_pBoxCollider = CBoxCollider::Create(GetPos(), GetOldPos(), D3DXVECTOR3(50.0f,50.0f,50.0f));

	// モーション取得
	m_pMotion = CMoveCharactor::GetMotion();

	// 結果を返す
	return S_OK;
}
//===============================
// プレイヤー終了処理
//===============================
void CPlayer::Uninit(void)
{
	// パラメータ終了処理
	m_pParameter.reset();

	// ステート終了処理
	m_pStateMachine.reset();

	// コライダー破棄
	if (m_pBoxCollider)
	{
		delete m_pBoxCollider;
		m_pBoxCollider = nullptr;
	}

	// キャラクターの破棄
	CMoveCharactor::Uninit();
}
//============================================================
// プレイヤー更新処理
//============================================================
void CPlayer::Update(void)
{
	// 死んでるなら処理しない
	if (m_isDeath) return;

	// 座標取得
	D3DXVECTOR3 pos = GetPos();

	// 入力デバイスのポインタ取得
	CInputKeyboard* pInput = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// nullptrじゃないとき
	if (m_pStateMachine != nullptr)
	{
		// ステート更新
		m_pStateMachine->Update();
	}

	// 移動処理
	MoveKey(pInput,pJoyPad);
	MovePad(pJoyPad);

	// コライダーの位置更新
	m_pBoxCollider->SetPos(pos);

	// 座標セット
	SetPos(pos);

	// ブロックとの当たり判定
	CollisionBlock(&pos);

	// キャラクターの更新処理
	CMoveCharactor::Update();
}
//===============================
// プレイヤー描画処理
//===============================
void CPlayer::Draw(void)
{
	// キャラクターの描画処理
	CMoveCharactor::Draw();

	// デバッグ表示
	CDebugproc::Print("モーションタイプ [ %d ]", m_pMotion->GetMotionType());
	CDebugproc::Draw(0, 100);
}
//=========================================
// キー入力移動関数
//=========================================
void CPlayer::MoveKey(CInputKeyboard* pInput,CJoyPad * pPad)
{
	// パッドがあったら
	if (pPad->GetLeftStick()) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// 取得関係
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 rotDest = GetRotDest();

	if (pInput->GetPress(DIK_A) || pPad->GetPress(CJoyPad::JOYKEY_LEFT))
	{// Aキー
		if (pInput->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
		{// 左斜め上

			move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);

			// モーション変更
			m_pMotion->SetMotion(MOTION_MOVE);

		}
		else if (pInput->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// 右斜め下

			move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);

			// モーション変更
			m_pMotion->SetMotion(MOTION_MOVE);
		}
		else
		{// 単体
			move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);

			// モーション変更
			m_pMotion->SetMotion(MOTION_MOVE);
		}

		// 角度の正規化
		if (rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			rot.y -= PLAYERINFO::NorRot;
		}
	}
	else if (pInput->GetPress(DIK_D) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
	{// Dキーを押した

		if (pInput->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
		{// Wキーを押した
			move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);

			// モーション変更
			m_pMotion->SetMotion(MOTION_MOVE);

		}
		else if (pInput->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// Sキーを押した
			move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);

			// モーション変更
			m_pMotion->SetMotion(MOTION_MOVE);
		}
		else
		{// Dキーのみ押した
			move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);

			// モーション変更
			m_pMotion->SetMotion(MOTION_MOVE);
		}

		// 角度の正規化
		if (rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			rot.y -= PLAYERINFO::NorRot;
		}
	}
	else if (pInput->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
	{// Wキーを押した

		move.x += sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		move.z += cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		rotDest.y = pCamera->GetRot().y - D3DX_PI;

		// モーション変更
		m_pMotion->SetMotion(MOTION_MOVE);
	
		// 角度を正規化
		if (rot.y < -D3DX_PI)
		{// D3DX_PIより小さくなったら
			rot.y += PLAYERINFO::NorRot;
		}

	}
	else if (pInput->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
	{// Sキーを押した

		move.x -= sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		move.z -= cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		rotDest.y = pCamera->GetRot().y;

		// モーション変更
		m_pMotion->SetMotion(MOTION_MOVE);

		// 角度の正規化
		if (rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			rot.y -= PLAYERINFO::NorRot;
		}
	}
	else
	{
		if (m_pMotion->GetMotionType() == MOTION_MOVE)
		{
			//　モーション切り替え
			m_pMotion->SetMotion(MOTION_NEUTRAL, true, 10, false);
		}
	}

	if (rotDest.y - rot.y > D3DX_PI)
	{// 左回転
		// 角度
		rot.y = rot.y + PLAYERINFO::NorRot;
	}
	else if (rot.y - rotDest.y > D3DX_PI)
	{// 右回転
		// 角度
		rot.y = rot.y - PLAYERINFO::NorRot;
	}

	// 現在の角度
	rot.y += (rotDest.y - rot.y) * 0.25f;

	// キャラクターに適用する
	SetRot(rot);
	SetRotDest(rotDest);
	SetMove(move);
}
//=========================================
// ジョイパッド入力移動関数
//=========================================
void CPlayer::MovePad(CJoyPad* pPad)
{
	// パッド取得
	XINPUT_STATE* pStick;
	pStick = pPad->GetStickAngle();

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// キャラクター情報の取得
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rotDest = GetRotDest();

	// フラグ
	bool isMoving = false;

	// 取得できたら
	if (pPad->GetLeftStick())
	{
		// 左スティックの角度
		float LStickAngleY = pStick->Gamepad.sThumbLY;
		float LStickAngleX = pStick->Gamepad.sThumbLX;

		// デッドゾーンを設定
		float DeadZone = 32767.0f * 0.25f;
		float fMag = sqrtf((LStickAngleX * LStickAngleX) + (LStickAngleY * LStickAngleY));

		if (fMag > DeadZone)
		{
			// 正規化
			float normalizeX = (LStickAngleX / fMag);
			float normalizeY = (LStickAngleY / fMag);

			// 移動量
			float MoveX = normalizeX * cosf(-pCamera->GetRot().y) - normalizeY * sinf(-pCamera->GetRot().y);
			float MoveZ = normalizeX * sinf(-pCamera->GetRot().y) + normalizeY * cosf(-pCamera->GetRot().y);

			// プレイヤーの移動量を設定
			move.x += MoveX * PLAYERINFO::MOVE;
			move.z += MoveZ * PLAYERINFO::MOVE;
			rotDest.y = atan2f(-MoveX, -MoveZ);
			isMoving = true;
		}
	}

	if (isMoving)
	{
		if (m_pMotion->GetMotionType() != MOTION_MOVE)
		{
			m_pMotion->SetMotion(MOTION_MOVE);
		}
	}

	// 適用
	SetMove(move);
	SetRotDest(rotDest);
}

//=========================================
// ブロックとの当たり判定
//=========================================
bool CPlayer::CollisionBlock(D3DXVECTOR3* pos)
{
	// 当たらないとき
	return false;
}

//=========================================
// ステート変更
//=========================================
void CPlayer::ChangeState(CPlayerStateBase* pNewState,int id)
{
	// 自分自身を代入
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}
//===============================
// キー押下時の入力取得
//===============================
bool CPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// いずれかの移動キー入力
	return (pKeyInput->GetPress(DIK_A) || pKeyInput->GetPress(DIK_D));
}
//===============================
// キー押下時の入力取得
//===============================
bool CPlayer::isMovePadButton(CJoyPad* pPad)
{
	// いずれかの移動キー入力
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
