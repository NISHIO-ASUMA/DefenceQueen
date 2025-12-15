//=========================================================
//
// 出現する餌一個に関する処理 [ feed.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "feed.h"
#include "spherecollider.h"
#include "collisionsphere.h"
#include "parameter.h"
#include "gamemanager.h"
#include "selectpoint.h"
#include "gamesceneobject.h"
#include "manager.h"
#include "xfilemanager.h"
#include "feedmanager.h"
#include "worker.h"

//*********************************************************
// 定数宣言
//*********************************************************
namespace FEEDINFO
{
	constexpr int LIFE = 25; // 基底体力値
};

//=========================================================
// コンストラクタ
//=========================================================
CFeed::CFeed(int nPriority) : CObjectX(nPriority),
m_pSphere(nullptr),
m_pParam(nullptr),
m_fRadius(NULL),
m_isDeath(false)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CFeed::~CFeed()
{

}
//=========================================================
// 生成処理
//=========================================================
CFeed* CFeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName, const float fRadius)
{
	// インスタンス生成
	CFeed* pFeed = new CFeed;
	if (pFeed == nullptr) return nullptr;

	// オブジェクト設定
	pFeed->SetPos(pos);
	pFeed->SetRot(rot);
	pFeed->SetScale(scale);
	pFeed->SetFilePass(pModelName);
	pFeed->SetRadius(fRadius);

	// 初期化失敗時
	if (FAILED(pFeed->Init())) 	return nullptr;

	return pFeed;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CFeed::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// 球形コライダー生成
	m_pSphere = CSphereCollider::Create(GetPos(), m_fRadius);

	// パラメーター設定
	m_pParam = std::make_unique<CParameter>();
	m_pParam->SetHp(FEEDINFO::LIFE);

	// 影をoffにする
	SetShadow(false);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CFeed::Uninit(void)
{
	// 破棄
	if (m_pSphere)
	{
		delete m_pSphere;
		m_pSphere = nullptr;
	}

	// 破棄
	m_pParam.reset();

	// 親クラスの終了
	CObjectX::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CFeed::Update(void)
{
	// 座標を取得
	D3DXVECTOR3 pos = GetPos();

	// コライダー更新
	m_pSphere->SetPos(pos);

	// 親クラスの更新
	CObjectX::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CFeed::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//=========================================================
// パラメーター減算処理
//=========================================================
void CFeed::DecLife(const int& nDecValue)
{
	// 引数の分減少
	int nHp = m_pParam->GetHp();
	nHp -= nDecValue;

	if (nHp <= NULL)
	{
		// 体力を0にする
		m_pParam->SetHp(NULL);

		// イベント起動
		m_event();

		// 要素の削除
		CGameSceneObject::GetInstance()->GetFeedManager()->Erase(this);

		// 自身の破棄
		Uninit();

		return;
	}
	else
	{
		// 現在の体力にセット
		m_pParam->SetHp(nHp);
		return;
	}
}
//=========================================================
// 当たり判定処理
//=========================================================
bool CFeed::Collision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphere,other);
}