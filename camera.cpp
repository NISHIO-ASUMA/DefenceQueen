//====================================
//
// カメラ処理 [ camera.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "gamemanager.h"
#include "template.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//**********************
// 定数宣言
//**********************
namespace CAMERAINFO
{
	constexpr float MAX_VIEWUP = 3.0f;			// カメラの角度制限値
	constexpr float MAX_VIEWDOWN = 0.1f;		// カメラの角度制限値
	constexpr float NorRot = D3DX_PI * 2.0f;	// 正規化値
	constexpr float CAMERABACKPOS = 450.0f;		// 後方カメラ
	constexpr float SHAKEVALUE = 12.0f;			// 振動の値
	constexpr float DIGITVALUE = 1.5f;		// 割る値
	constexpr int RANDOMBASE = 2;			// ランダム基準値
}

//=================================
// コンストラクタ
//=================================
CCamera::CCamera()
{
	// 値のクリア
	m_pCamera.mtxprojection = {};
	m_pCamera.mtxView = {};
	m_pCamera.posR = VECTOR3_NULL;
	m_pCamera.posV = VECTOR3_NULL;
	m_pCamera.rot = VECTOR3_NULL;
	m_pCamera.vecU = VECTOR3_NULL;
	m_pCamera.posRDest = VECTOR3_NULL;
	m_pCamera.fDistance = NULL;
	m_pCamera.nMode = MODE_NONE;
	m_pCamera.nUseKey = NULL;
	m_pCamera.nCntAnim = NULL;

	// イベント用
	m_event.isActive = false;
	m_event.endFrame = NULL;
	m_event.frame = NULL;
	m_event.startPosR = VECTOR3_NULL;
	m_event.startPosV = VECTOR3_NULL;
	m_event.targetPosR = VECTOR3_NULL;
	m_event.targetPosV = VECTOR3_NULL;

	// アニメーション用
	m_pCamera.m_AnimData.isLoop = false;
	m_pCamera.m_AnimData.nNumKey = 20;

	// キー構造体変数のクリア
	for (int nCnt = 0; nCnt < NUMKEY; nCnt++)
	{
		m_pCamera.m_AnimData.KeyInfo[nCnt].fDistance = 780.0f;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotZ = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].nAnimFrame = 40;
	}

	m_isAnimTime = false;
	m_nAnimNowKey = NULL;
	m_nFileIdx = NULL;
	m_nAnimShakeFlame = NULL;
	m_isCreate = false;
	m_isShake = false;
	m_nShakeTime = NULL;
	m_isLoad = false;
}
//=================================
// デストラクタ
//=================================
CCamera::~CCamera()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CCamera::Init(void)
{
	// 初期値を設定する
	m_pCamera.posV = D3DXVECTOR3(0.0f, 1200.0f, 0.0f);			// カメラの位置
	m_pCamera.posR = VECTOR3_NULL;								// カメラの見ている位置
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);				// 上方向ベクトル
	m_pCamera.rot = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);	// 角度

	// 距離を計算
	float fRotx = m_pCamera.posV.x - m_pCamera.posR.x;
	float fRoty = m_pCamera.posV.y - m_pCamera.posR.y;
	float fRotz = m_pCamera.posV.z - m_pCamera.posR.z;

	// 視点から注視点までの距離
	m_pCamera.fDistance = sqrtf((fRotx * fRotx) + (fRoty * fRoty) + (fRotz * fRotz));

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CCamera::Uninit(void)
{
	// 無し
}
//=================================
// 更新処理
//=================================
void CCamera::Update(void)
{
	// 振動有効時
	if (m_isShake)
	{
		// 振動更新
		UpdateShake();
	}
	
	// 角度の正規化
	if (m_pCamera.rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_pCamera.rot.y -= CAMERAINFO::NorRot;
	}

	// 角度の正規化
	if (m_pCamera.rot.y < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
}
//=================================
// カメラをセット
//=================================
void CCamera::SetCamera(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_pCamera.mtxView,
		&m_pCamera.posV,
		&m_pCamera.posR,
		&m_pCamera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera.mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera.mtxprojection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_pCamera.mtxprojection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera.mtxprojection);

	// フォントセット
	CDebugproc::Print("Camera : PosV [ %.2f, %.2f, %.2f ]\n", m_pCamera.posV.x, m_pCamera.posV.y, m_pCamera.posV.z);

	// 描画開始
	CDebugproc::Draw(0, 20);

	CDebugproc::Print("Camera : PosR [ %.2f, %.2f, %.2f ]\n", m_pCamera.posR.x, m_pCamera.posR.y, m_pCamera.posR.z);
	CDebugproc::Draw(0, 40);

	CDebugproc::Print("Camera : Rot [ %.2f, %.2f, %.2f ]\n", m_pCamera.rot.x, m_pCamera.rot.y, m_pCamera.rot.z);
	CDebugproc::Draw(0, 80);
}
//======================================
// マウス操作の視点移動
//======================================
void CCamera::MouseView(CInputMouse * pMouse)
{
	// 左クリック
	if (pMouse->GetPress(CInputMouse::MOUSE_LEFT))
	{
		// マウスの移動量取得
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		// 現在の角度を計算
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// 回転量を更新
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// 回転量を制限
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// カメラの視点の情報
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// 右クリック
	else if (pMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// 回転量を更新
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// 回転量を制限
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// カメラ座標を更新
		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.y = m_pCamera.posV.y + cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}

	// 正規化
	if (m_pCamera.rot.y < -D3DX_PI)
	{
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.y > D3DX_PI)
	{
		m_pCamera.rot.y += -CAMERAINFO::NorRot;
	}
	if (m_pCamera.rot.x < -D3DX_PI)
	{
		m_pCamera.rot.x += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.x > D3DX_PI)
	{
		m_pCamera.rot.x += -CAMERAINFO::NorRot;
	}
}
//=============================
// 振動更新関数
//=============================
void CCamera::UpdateShake(void)
{
	// シェイク適用
	if (m_isShake && (!m_event.isActive))
	{
		if (m_nShakeTime > 0)
		{
			// ランダムオフセット
			float fOffset = static_cast<float>(rand() % 80) - 40.0f;

			// 視点だけを揺らす
			m_pCamera.posR.x += fOffset;
			m_pCamera.posR.y += fOffset;
			m_pCamera.posR.z += fOffset;

			m_nShakeTime--;

			if (m_nShakeTime <= 0)
			{
				m_isShake = false;
				m_nShakeTime = 0;
			}
		}
		else
		{
			m_isShake = false;
		}
	}
}