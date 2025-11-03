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
	pSelect->m_fHitRange = fRadius;

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

	// コライダー座標の更新
	m_pSphere->SetPos(pos);

	// 当たり判定
	
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
// 当たり判定処理
//============================
bool CSelectPoint::Collision(CSphereCollider* other)
{
	// 球同士の当たり判定
	return CCollisionSphere::Collision(m_pSphere,other);
}