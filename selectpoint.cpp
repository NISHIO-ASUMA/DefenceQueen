//=========================================================
//
// 選択ポイント処理 [ selectpoint.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "selectpoint.h"
#include "collisionsphere.h"
#include "spherecollider.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "boxcollider.h"
#include "collisionbox.h"
#include "gamemanager.h"
#include "gamesceneobject.h"
#include "blockmanager.h"
#include "feedmanager.h"
#include "feed.h"
#include "blackboard.h"
#include "behaviortree.h"
#include "node.h"

//*********************************************************
// 定数宣言
//*********************************************************
namespace SELECTOR
{
	constexpr float SPEED = 15.0f; // 移動速度
};

//=========================================================
// コンストラクタ
//=========================================================
CSelectPoint::CSelectPoint(int nPriority) : CMove3DObject(nPriority),
m_fHitRange(NULL),
m_pSphere(nullptr),
m_pBox(nullptr),
m_isHit(false)
{

}
//=========================================================
// デストラクタ
//=========================================================
CSelectPoint::~CSelectPoint()
{

}
//=========================================================
// 生成処理
//=========================================================
CSelectPoint* CSelectPoint::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth,const float fHeight,const float fRadius)
{
	// インスタンス生成
	CSelectPoint* pSelect = new CSelectPoint;
	if (pSelect == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pSelect->Init())) return nullptr;

	// オブジェクト設定
	pSelect->SetPos(pos);
	pSelect->SetRot(rot);
	pSelect->SetSize(fWidth, fHeight);
	pSelect->SetTexture("Circle.png");
	pSelect->SetfRange(fRadius);

	// コライダー生成
	pSelect->m_pSphere = CSphereCollider::Create(pos, fRadius);
	pSelect->m_pBox = CBoxCollider::Create(pos, pos, D3DXVECTOR3(fRadius, fRadius, fRadius));

	return pSelect;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CSelectPoint::Init(void)
{
	// 親クラスの初期化
	CMove3DObject::Init();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CSelectPoint::Uninit(void)
{
	// スフィアコライダーの破棄
	if (m_pSphere)
	{
		delete m_pSphere;
		m_pSphere = nullptr;
	}

	// ボックスコライダーの破棄
	if (m_pBox)
	{
		delete m_pBox;
		m_pBox = nullptr;
	}

	// 親クラスの終了処理
	CMove3DObject::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CSelectPoint::Update(void)
{
	// 座標を取得
	D3DXVECTOR3 oldPos = GetOldPos();

	// キー入力での移動関数
	Moving();
	MovePad();

	// オブジェクトの座標更新
	CMove3DObject::UpdatePosition();

	// 更新された座標を取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// 球形コライダー座標の更新
	m_pSphere->SetPos(UpdatePos);

	// 矩形コライダーの位置更新
	if (m_pBox)
	{
		m_pBox->SetPos(UpdatePos);
		m_pBox->SetPosOld(oldPos);
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
		if (CollisionBox(pOtherCollider, &UpdatePos))
		{
			// 当たった点の座標セット
			SetPos(UpdatePos);

			// 矩形コライダー座標更新
			m_pBox->SetPos(UpdatePos);
		}
	}

	// ポインタ取得
	CFeedManager* pManager = CGameSceneObject::GetInstance()->GetFeedManager();

	for (int nCnt = 0; nCnt < pManager->GetSize(); nCnt++)
	{
		if (Collision(pManager->GetFeed(nCnt)->GetCollider()))
		{
			// ヒット時の処理
			SetIsHit(true);
			SetCol(COLOR_RED);
			break;
		}
		else
		{
			// 未ヒット時の処理
			SetIsHit(false);
			SetCol(COLOR_WHITE);
		}
	}

	// 移動量の減衰
	CMove3DObject::DecayMove(0.75f);

	// 親クラスの更新処理
	CMove3DObject::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CSelectPoint::Draw(void)
{
	// 親クラスの描画
	CMove3DObject::Draw();

	// デバッグ情報
	CDebugproc::Print("選択ポインター座標 : [ %.2f,%.2f,%.2f ] \n当たったかどうか [ %d ]", GetPos().x, GetPos().y, GetPos().z,GetIsHit());
	CDebugproc::Draw(0, 160);
}
//=========================================================
// ポインター移動処理
//=========================================================
void CSelectPoint::Moving(void)
{
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
}
//===============================================================
// パッド入力のポインター移動処理
//===============================================================
void CSelectPoint::MovePad(void)
{
	// 移動量を取得
	D3DXVECTOR3 move = GetMove();

	// 入力デバイス取得
	CJoyPad* pPad = CManager::GetInstance()->GetJoyPad();
	XINPUT_STATE* pStick = pPad->GetStickAngle();

	// 入力受け取り失敗時
	if (!pPad->GetLeftStick()) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

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
			move.x += MoveX * SELECTOR::SPEED;
			move.z += MoveZ * SELECTOR::SPEED;
		}
	}

	// 適用
	SetMove(move);
}

//=========================================================
// 球の当たり判定処理
//=========================================================
bool CSelectPoint::Collision(CSphereCollider* other)
{
	// 球同士の当たり判定
	return CCollisionSphere::Collision(m_pSphere,other);
}
//=========================================================
// 矩形の当たり判定処理
//=========================================================
bool CSelectPoint::CollisionBox(CBoxCollider* pothere, D3DXVECTOR3* pOutPos)
{
	return CCollisionBox::Collision(m_pBox,pothere,pOutPos);
}