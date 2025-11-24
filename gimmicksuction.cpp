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

	// 吸い込みを発生させる ( 対象は仲間オブジェクト )
	
	// 時間を減らす
	if (m_nActiveTime <= NULL)
	{
		m_nActiveTime--;
	}
	else
	{
		Uninit();
		return;
	}

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