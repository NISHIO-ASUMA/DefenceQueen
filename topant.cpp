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
#include "boxcollider.h"
#include "collisionbox.h"
#include "gamesceneobject.h"
#include "blockmanager.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "player.h"
#include "meshcylinder.h"

//=========================================================
// コンストラクタ
//=========================================================
CTopAnt::CTopAnt(int nPriority) : CMoveCharactor(nPriority),m_pColliderBox(nullptr),m_isActive(false)
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
	MotionLoad("data/MOTION/Enemy/Enemy_Motion.txt", MOTION_MAX, true);

	// コライダー生成
	m_pColliderBox = CBoxCollider::Create(GetPos(), GetOldPos(), D3DXVECTOR3(40.0f, 40.0f, 40.0f));

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTopAnt::Uninit(void)
{
	// コライダー破棄
	if (m_pColliderBox)
	{
		delete m_pColliderBox;
		m_pColliderBox = nullptr;
	}

	// 親クラスの終了処理
	CMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CTopAnt::Update(void)
{
	// 座標取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 oldPos = GetOldPos();

	// 入力デバイス取得
	CJoyPad* pPad = CManager::GetInstance()->GetJoyPad();
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();

	// キー入力での移動関数
	if (m_isActive)
	{
		Moving(pPad, pKey);
		MovePad(pPad);

		// メッシュ取得
		auto mesh = CGameSceneObject::GetInstance()->GetPlayer()->GetMeshCylinder();
		if (mesh == nullptr) return;

		// 座標を合わせる
		mesh->SetPos(pos);
	}

	// オブジェクトの座標更新
	CMoveCharactor::UpdatePosition();

	// 更新された座標を取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// 矩形コライダーの位置更新
	if (m_pColliderBox)
	{
		m_pColliderBox->SetPos(UpdatePos);
		m_pColliderBox->SetPosOld(oldPos);
	}

	// 配置されているブロックを取得
	auto Block = CGameSceneObject::GetInstance()->GetBlockManager();
	if (Block == nullptr) return;

	// ブロックオブジェクトとの当たり判定
	for (int nBlock = 0; nBlock < Block->GetAll(); nBlock++)
	{
		// コライダー取得
		CBoxCollider* pOtherCollider = Block->GetBlock(nBlock)->GetCollider();
		if (pOtherCollider == nullptr) continue;

		// 矩形で当たる
		if (Collision(pOtherCollider, &UpdatePos))
		{
			// 当たった点の座標セット
			SetPos(UpdatePos);

			// 矩形コライダー座標更新
			m_pColliderBox->SetPos(UpdatePos);
		}
	}

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

	// デバッグ情報
	// CDebugproc::Print("");

}
//=========================================================
// 矩形の当たり判定処理
//=========================================================
bool CTopAnt::Collision(CBoxCollider * pOther,D3DXVECTOR3 * pOutPos)
{
	return CCollisionBox::Collision(m_pColliderBox,pOther,pOutPos);
}
//=========================================================
// キー入力移動
//=========================================================
void CTopAnt::Moving(CJoyPad * pPad,CInputKeyboard * pKey)
{
	// 移動量を取得
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 rotdest = GetRotDest();

	// パッドのスティック入力があったら
	if (pPad->GetLeftStick()) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// 移動フラグ
	bool isMove = false;

	if (pKey->GetPress(DIK_A) || pPad->GetPress(CJoyPad::JOYKEY_LEFT))
	{// Aキー

		if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
		{// 左斜め上

			move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * Config::SPEED;
			move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * Config::SPEED;
			rotdest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);
			isMove = true;
		}
		else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// 右斜め下

			move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * Config::SPEED;
			move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * Config::SPEED;
			rotdest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);
			isMove = true;

		}
		else
		{// 単体
			move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * Config::SPEED;
			move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * Config::SPEED;
			rotdest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);
			isMove = true;
		}

		// 角度の正規化
		if (rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			rot.y -= Config::NorRot;
		}
	}
	else if (pKey->GetPress(DIK_D) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
	{// Dキーを押した

		if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
		{// Wキーを押した
			move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * Config::SPEED;
			move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * Config::SPEED;
			rotdest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);
			isMove = true;
		}
		else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// Sキーを押した
			move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * Config::SPEED;
			move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * Config::SPEED;
			rotdest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);
			isMove = true;
		}
		else
		{// Dキーのみ押した
			move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * Config::SPEED;
			move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * Config::SPEED;
			rotdest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);
			isMove = true;
		}

		// 角度の正規化
		if (rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			rot.y -= Config::NorRot;
		}
	}
	else if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
	{// Wキーを押した

		move.x += sinf(pCamera->GetRot().y) * Config::SPEED;
		move.z += cosf(pCamera->GetRot().y) * Config::SPEED;
		rotdest.y = pCamera->GetRot().y - D3DX_PI;
		isMove = true;

		// 角度を正規化
		if (rot.y < -D3DX_PI)
		{// D3DX_PIより小さくなったら
			rot.y += Config::NorRot;
		}

	}
	else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
	{// Sキーを押した

		move.x -= sinf(pCamera->GetRot().y) * Config::SPEED;
		move.z -= cosf(pCamera->GetRot().y) * Config::SPEED;
		rotdest.y = pCamera->GetRot().y;
		isMove = true;

		// 角度の正規化
		if (rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			rot.y -= Config::NorRot;
		}
	}

	if (isMove)
	{
		// MOVEじゃなかったら切り替え
		if (GetMotion()->GetMotionType() != MOVE)
		{
			GetMotion()->SetMotion(MOVE);
		}
	}
	else
	{
		// NEUTRALに遷移する
		if (GetMotion()->GetMotionType() == MOVE)
		{
			//　タイプ切り替え
			GetMotion()->SetMotion(NEUTRAL, true, 10);
		}
	}

	if (rotdest.y - rot.y > D3DX_PI)
	{// 左回転
		// 角度
		rot.y = rot.y + Config::NorRot;
	}
	else if (rot.y - rotdest.y > D3DX_PI)
	{// 右回転
		// 角度
		rot.y = rot.y - Config::NorRot;
	}

	// 現在の角度
	rot.y += (rotdest.y - rot.y) * 0.25f;

	// キャラクターに適用する
	SetRot(rot);
	SetRotDest(rotdest);
	SetMove(move);

 }
//=========================================================
// パッド入力移動
//=========================================================
void CTopAnt::MovePad(CJoyPad * pPad)
{
	// 移動量を取得
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rotdest = GetRotDest();

	// 入力デバイス取得
	XINPUT_STATE* pStick = pPad->GetStickAngle();

	// 入力受け取り失敗時
	if (!pPad->GetLeftStick()) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// フラグ
	bool isMoving = false;
	static bool wasStick = false;

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

			// 移動量を計算する
			float MoveX = normalizeX * cosf(-pCamera->GetRot().y) - normalizeY * sinf(-pCamera->GetRot().y);
			float MoveZ = normalizeX * sinf(-pCamera->GetRot().y) + normalizeY * cosf(-pCamera->GetRot().y);

			// 移動量を設定
			move.x += MoveX * Config::SPEED;
			move.z += MoveZ * Config::SPEED;
			rotdest.y = atan2f(-MoveX, -MoveZ);
			isMoving = true;
		}
	}

	if (isMoving)
	{
		// MOVEじゃなかったら
		if (GetMotion()->GetMotionType() != MOVE)
		{
			// モーション変更
			GetMotion()->SetMotion(MOVE);
		}
	}
	else if (!isMoving && wasStick)
	{
		// 離した瞬間の判定
		if (GetMotion()->GetMotionType() == MOVE)
			GetMotion()->SetMotion(NEUTRAL, true, 10);
	}

	// フラグを変更する
	wasStick = isMoving;

	// 適用
	SetMove(move);
	SetRotDest(rotdest);
}