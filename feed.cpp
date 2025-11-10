//===============================================
//
// 出現する餌の処理 [ feed.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// インクルードファイル
//**********************
#include "feed.h"
#include "spherecollider.h"
#include "parameter.h"

//**********************
// 定数宣言
//**********************
namespace FEEDINFO
{
	constexpr int LIFE = 15; // 基底体力値
};

//============================
// コンストラクタ
//============================
CFeed::CFeed(int nPriority) : CObjectX(nPriority),
m_pSphere(nullptr),
m_pParam(nullptr)
{
	// 値のクリア
}
//============================
// デストラクタ
//============================
CFeed::~CFeed()
{

}
//============================
// 生成処理
//============================
CFeed* CFeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName)
{
	// インスタンス生成
	CFeed* pFeed = new CFeed;
	if (pFeed == nullptr) return nullptr;

	// オブジェクト設定
	pFeed->SetPos(pos);
	pFeed->SetRot(rot);
	pFeed->SetScale(scale);
	pFeed->SetFilePass(pModelName);
	pFeed->SetShadow(true);

	// 初期化失敗時
	if (FAILED(pFeed->Init())) 	return nullptr;

	return pFeed;
}
//============================
// 初期化処理
//============================
HRESULT CFeed::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// 球形コライダー生成
	m_pSphere = CSphereCollider::Create(GetPos(), 70.0f);

	// パラメーター設定
	m_pParam = std::make_unique<CParameter>();
	m_pParam->SetHp(FEEDINFO::LIFE);

	return S_OK;
}
//============================
// 終了処理
//============================
void CFeed::Uninit(void)
{
	// 破棄
	if (m_pSphere)
	{
		delete m_pSphere;
		m_pSphere = nullptr;
	}

	m_pParam.reset();

	// 親クラスの終了
	CObjectX::Uninit();
}
//============================
// 更新処理
//============================
void CFeed::Update(void)
{
	// 座標を取得
	D3DXVECTOR3 pos = GetPos();

	// コライダー更新
	m_pSphere->SetPos(pos);

	// 親クラスの更新
	CObjectX::Update();
}
//============================
// 描画処理
//===========================
void CFeed::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//============================
// パラメーター減算処理
//===========================
void CFeed::DecLife(const int nDecValue)
{
	// 引数の分減少
	int nHp = m_pParam->GetHp();
	nHp -= nDecValue;

	if (nHp <= NULL)
	{
		m_pParam->SetHp(NULL);
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