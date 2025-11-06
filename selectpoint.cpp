//=====================================
//
// 選択ポイント処理 [ selectpoint.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "selectpoint.h"
#include "collisionsphere.h"
#include "spherecollider.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "camera.h"

//**********************
// 定数宣言
//**********************
namespace SELECTOR
{
	constexpr float SPEED = 15.0f; // 移動速度
};

//============================
// コンストラクタ
//============================
CSelectPoint::CSelectPoint(int nPriority) : CObject3D(nPriority),
m_fHitRange(NULL),
m_pSphere(nullptr)
{

}
//============================
// デストラクタ
//============================
CSelectPoint::~CSelectPoint()
{

}
//============================
// 生成処理
//============================
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

	return pSelect;
}
//============================
// 初期化処理
//============================
HRESULT CSelectPoint::Init(void)
{
	// 親クラスの初期化
	CObject3D::Init();

	// コライダー生成
	m_pSphere = CSphereCollider::Create(GetPos(), m_fHitRange);

	return S_OK;
}
//============================
// 終了処理
//============================
void CSelectPoint::Uninit(void)
{
	// コライダーの破棄
	if (m_pSphere)
	{
		delete m_pSphere;
		m_pSphere = nullptr;
	}

	// 親クラスの終了処理
	CObject3D::Uninit();
}
//============================
// 更新処理
//============================
void CSelectPoint::Update(void)
{
	// 現在の座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 移動関数
	Moving(pos);
	MovePad(pos);

	// コライダー座標の更新
	m_pSphere->SetPos(pos);

	// 当たり判定を対象オブジェクトから取得

	// 当たったらコライダー座標の更新
	
	// 親クラスの更新処理
	CObject3D::Update();
}
//============================
// 描画処理
//============================
void CSelectPoint::Draw(void)
{
	// 親クラスの描画
	CObject3D::Draw();

	// デバッグフォント
	CDebugproc::Print("ポインター座標 : [ %.2f,%.2f,%.2f ]", GetPos().x, GetPos().y, GetPos().z);
	CDebugproc::Draw(0, 160);
}
//============================
// ポインター移動処理
//============================
void CSelectPoint::Moving(D3DXVECTOR3 pos)
{
	// 入力デバイス取得
	CJoyPad* pPad = CManager::GetInstance()->GetJoyPad();
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();

	// パッドがあったら
	if (pPad->GetLeftStick()) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// 取得関係
	D3DXVECTOR3 rot = GetRot();

	if (pKey->GetPress(DIK_A) || pPad->GetPress(CJoyPad::JOYKEY_LEFT))
	{// Aキー

		if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
		{// 左斜め上

			pos.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
			pos.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// 右斜め下

			pos.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
			pos.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else
		{// 単体
			pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
			pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
		}
	}
	else if (pKey->GetPress(DIK_D) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
	{// Dキーを押した

		if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
		{// Wキーを押した
			pos.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
			pos.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// Sキーを押した
			pos.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
			pos.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SELECTOR::SPEED;
		}
		else
		{// Dキーのみ押した
			pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
			pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * SELECTOR::SPEED;
		}
	}
	else if (pKey->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
	{// Wキーを押した

		pos.x += sinf(pCamera->GetRot().y) * SELECTOR::SPEED;
		pos.z += cosf(pCamera->GetRot().y) * SELECTOR::SPEED;

	}
	else if (pKey->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
	{// Sキーを押した

		pos.x -= sinf(pCamera->GetRot().y) * SELECTOR::SPEED;
		pos.z -= cosf(pCamera->GetRot().y) * SELECTOR::SPEED;
	}

	// 座標適用
	SetPos(pos);
}
//============================
// ポインター移動処理
//============================
void CSelectPoint::MovePad(D3DXVECTOR3 pos)
{
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
			pos.x += MoveX * SELECTOR::SPEED;
			pos.z += MoveZ * SELECTOR::SPEED;
		}
	}

	// 適用する
	SetPos(pos);
}

//============================
// 当たり判定処理
//============================
bool CSelectPoint::Collision(CSphereCollider* other)
{
	// 球同士の当たり判定
	return CCollisionSphere::Collision(m_pSphere,other);
}