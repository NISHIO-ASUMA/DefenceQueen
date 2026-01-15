//=========================================================
//
// チュートリアルの仲間アリの処理クラス [ tutoarrayant.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "tutoarrayant.h"
#include "spherecollider.h"
#include "collisionsphere.h"

//=========================================================
// コンストラクタ
//=========================================================
CTutoArrayAnt::CTutoArrayAnt(int nPriority) : CMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_DestPos(VECTOR3_NULL)
{
}
//=========================================================
// デストラクタ
//=========================================================
CTutoArrayAnt::~CTutoArrayAnt()
{

}
//=========================================================
// 生成処理
//=========================================================
CTutoArrayAnt* CTutoArrayAnt::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// インスタンス生成
	CTutoArrayAnt* pTutoAnt = new CTutoArrayAnt;
	if (pTutoAnt == nullptr) return nullptr;

	// オブジェクト設定
	pTutoAnt->SetPos(pos);
	pTutoAnt->SetRot(rot);
	pTutoAnt->SetUseStencil(false);
	pTutoAnt->SetUseOutLine(false);

	// 初期化失敗時
	if (FAILED(pTutoAnt->Init())) return nullptr;

	return pTutoAnt;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTutoArrayAnt::Init(void)
{
	// 親クラスの初期化
	CMoveCharactor::Init();

	// オブジェクトの種類をセット
	SetObjType(CObject::TYPE_ARRAY);

	// モーションセット
	MotionLoad("data/MOTION/Array/Array_Motion.txt", MOTION_MAX, true);

	// スフィアコライダー生成
	m_pSphereCollider = CSphereCollider::Create(GetPos(), Config::MAX_RADIUS);

	//// ノードセット
	// NodeSetting();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTutoArrayAnt::Uninit(void)
{
	// コライダーポインタの破棄
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// 親クラスの終了処理
	CMoveCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CTutoArrayAnt::Update(void)
{
	// 現在座標の取得
	auto Pos = GetPos();

	// 座標のみ更新
	CMoveCharactor::UpdatePosition();

	// 更新座標取得
	auto UpdatePos = GetPos();

	// コライダー座標の更新
	m_pSphereCollider->SetPos(UpdatePos);

	// 親クラス全体の更新処理
	CMoveCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CTutoArrayAnt::Draw(void)
{
	// 親クラスの描画処理
	CMoveCharactor::Draw();
}
//=========================================================
// 球形の当たり判定
//=========================================================
bool CTutoArrayAnt::Collision(CSphereCollider* other)
{
	// 球形クラスの判定関数を返す
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}