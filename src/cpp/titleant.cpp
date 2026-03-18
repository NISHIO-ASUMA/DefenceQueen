//=========================================================
//
// タイトルのキャラクター処理 [ titleant.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// クラス定義ヘッダーファイル
//*********************************************************
#include "titleant.h"

//*********************************************************
// インクルードファイル
//*********************************************************
#include "template.h"
#include "boxtospherecollision.h"
#include "worldwallmanager.h"
#include "gamewallmodel.h"
#include "titleobject.h"
#include "spherecollider.h"
#include "motioninstancing.h"

//=========================================================
// コンストラクタ
//=========================================================
CTitleAnt::CTitleAnt(int nPriority) : CInstancingCharactor(nPriority),
m_pCollider(nullptr)
{

}
//=========================================================
// デストラクタ
//=========================================================
CTitleAnt::~CTitleAnt()
{

}
//=========================================================
// 生成処理
//=========================================================
CTitleAnt* CTitleAnt::Create
(
	const D3DXVECTOR3& pos, 
	const D3DXVECTOR3& destpos,
	const D3DXVECTOR3& rot
)
{
	// インスタンス生成
	CTitleAnt * pAnt = new CTitleAnt;
	if (pAnt == nullptr) return nullptr;

	// オブジェクト設定
	pAnt->SetPos(pos);
	pAnt->SetRot(rot);
	pAnt->SetDestPos(destpos);
	pAnt->SetUseStencil(false);

	// 初期化失敗時
	if (pAnt->Init()) return nullptr;

	return pAnt;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CTitleAnt::Init(void)
{
	// 親クラスの初期化
	CInstancingCharactor::Init();

	// モーションセット
	MotionLoad(Config::SCRIPT,MOTION_MAX,false);

	// コライダー生成
	m_pCollider = CSphereCollider::Create(GetPos(), Config::HitRange);
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CTitleAnt::Uninit(void)
{
	// 球形コライダーの破棄
	m_pCollider.reset();

	// 親クラスの終了
	CInstancingCharactor::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CTitleAnt::Update(void)
{
	// 座標取得
	D3DXVECTOR3 pos = GetPos();

	// 目的地に向かって移動する
	D3DXVECTOR3 Dest = GetDestPos() - pos;

	// ベクトルを正規化する
	D3DXVec3Normalize(&Dest, &Dest);

	// 移動速度
	Dest *= Config::MOVE;

	// 向きを算出
	float angleY = atan2(-Dest.x, -Dest.z);
	D3DXVECTOR3 rot = GetRotDest();

	// 正規化する
	rot.y = NormalAngle(angleY);

	// キャラクターにセットする
	SetRotDest(rot);
	SetMove(Dest);

	// モーション変更
	GetMotion()->SetMotion(MOTION_MOVE);

	// 座標の更新
	CInstancingCharactor::UpdatePosition();

	// 更新後の座標
	D3DXVECTOR3 UpdatePos = GetPos();

	// コライダーの座標を更新する
	m_pCollider->SetPos(UpdatePos);

	// タイトルの壁と衝突判定生成
	auto Wall = CTitleObject::GetInstance()->GetWallManager();
	if (Wall == nullptr) return;

	for (int nCnt = 0; nCnt < Wall->GetSize(); nCnt++)
	{
		// 壁単体を取得する
		auto wallobj = Wall->GetWorldWall(nCnt);

		// 当たったら
		if (Collision(wallobj->GetCollider()))
		{
			// 自身を破棄
			Uninit();

			// 処理終了
			return;
		}
	}

	// 親クラスの更新
	CInstancingCharactor::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CTitleAnt::Draw(void)
{
	// 親クラスの描画
	CInstancingCharactor::Draw();
}
//=========================================================
// 当たり判定処理
//=========================================================
bool CTitleAnt::Collision(CBoxCollider* pOther)
{
	// nullなら
	if (m_pCollider == nullptr) return false;

	return CBoxToSphereCollision::Collision(pOther,m_pCollider.get());
}