//=========================================================
//
// 吸い込みギミック処理 [ gimmicksuction.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "gimmicksuction.h"
#include "gamesceneobject.h"
#include "selectpoint.h"
#include "template.h"

//=========================================================
// コンストラクタ
//=========================================================
CGimmickSuction::CGimmickSuction(int nPriority) : CObjectX(nPriority),m_nActiveTime(NULL)
{

}
//=========================================================
// デストラクタ
//=========================================================
CGimmickSuction::~CGimmickSuction()
{

}
//=========================================================
// 生成処理
//=========================================================
CGimmickSuction* CGimmickSuction::Create(
	const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pModelName, const int nActiveTime,const float fRadius)
{
	// インスタンス生成
	CGimmickSuction* pGimmick = new CGimmickSuction;
	if (pGimmick == nullptr) return nullptr;

	// オブジェクト設定
	pGimmick->SetPos(pos);
	pGimmick->SetRot(rot);
	pGimmick->SetFilePass(pModelName);
	pGimmick->SetTime(nActiveTime);
	pGimmick->SetRadius(fRadius);

	// 初期化失敗時
	if (FAILED(pGimmick->Init())) return nullptr;

	return pGimmick;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGimmickSuction::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGimmickSuction::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CGimmickSuction::Update(void)
{
	// 取得
	D3DXVECTOR3 pos = GetPos();
	float fRadius = GetRadius();

	// 対象物を取得
	auto select = CGameSceneObject::GetInstance()->GetPoint();
	auto selectpos = select->GetPos();

	D3DXVECTOR3 vec = pos - selectpos; // 吸い寄せ
	float dist = D3DXVec3Length(&vec);

	if (dist < fRadius)
	{
		// 正規化（方向）
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &vec);

		// 一定の吸引力
		const float suctionPower = 5.0f;  // 一定の吸引速度
		D3DXVECTOR3 suctionMove = dir * suctionPower;

		select->SetMove(suctionMove);
	}

	// 時間を減らす
	if (m_nActiveTime >= NULL)
	{
		m_nActiveTime--;
	}
	else
	{
		Uninit();
		return;
	}

	// 角度加算
	auto rot = GetRot();
	rot.y += 0.3f;
	rot.y = NormalAngle(rot.y);
	SetRot(rot);

	// 親クラスの更新
	CObjectX::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CGimmickSuction::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}