//=========================================================
//
// 各ポイントごとのスポーン処理 [ arrayspawner.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "arrayspawner.h"
#include "array.h"
#include "arraymanager.h"
#include "topant.h"

//=========================================================
// コンストラクタ
//=========================================================
CArraySpawner::CArraySpawner() :
	m_SpawnBasePos(VECTOR3_NULL),
	m_nStockArrays(NULL), 
	m_AssignedArrays{},
	m_pTopAnts(nullptr)
{

}
//=========================================================
// デストラクタ
//=========================================================
CArraySpawner::~CArraySpawner()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CArraySpawner::Init(CArrayManager* pManager)
{
	// 使える要素をもらう
	m_AssignedArrays = pManager->Allocate(m_nStockArrays);

	// トップのアリを生成
	m_pTopAnts = CTopAnt::Create(m_SpawnBasePos + D3DXVECTOR3(0.0f, 0.0f, 50.0f), VECTOR3_NULL);

	// 隊列の追従関係変数
	CArray* pPrev = nullptr;

	// セットされた数だけアクティブにする
	for (int nCnt = 0; nCnt < m_nStockArrays; nCnt++)
	{
		// 変数格納
		m_AssignedArrays.push_back(CArray::Create(m_SpawnBasePos, VECTOR3_NULL, 10));

		CArray* pArray = m_AssignedArrays[nCnt];

		// 設定関連
		pArray->SetPos(m_SpawnBasePos);
		pArray->SetActive(true);

		if (nCnt == 0)
		{
			// トップアリを追従
			pArray->SetFollowTargetTop(m_pTopAnts);
		}
		else
		{
			// 1つ前のアリを追従
			pArray->SetPrevAnt(pPrev);
		}

		// 次の「前のアリ」用に保存
		pPrev = pArray;
	}
	

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CArraySpawner::Uninit(void)
{

}
//=========================================================
// 更新処理
//=========================================================
void CArraySpawner::Update(void)
{

}
//=========================================================
// 描画処理
//=========================================================
void CArraySpawner::Draw(void)
{

}
//=========================================================
// 移動先設定関数
//=========================================================
void CArraySpawner::OrderMove(int nNum, const D3DXVECTOR3& destPos)
{
	// カウント
	int nSend = 0;

	for (int nCnt = 0; nCnt < static_cast<int>(m_AssignedArrays.size()); nCnt++)
	{
		// 最大なら
		if (nSend >= nNum) break;

		// 配列取得
		auto pArray = m_AssignedArrays[nCnt];
		if (!pArray) continue;

		// 使われてない物はスキップ
		if (!pArray->GetActive()) continue;
		if (pArray->GetMove())  continue;

		// ランダム配置
		D3DXVECTOR3 randomaiz = RandomSetPos(destPos, 75.0f, nNum, nCnt);

		// 移動フラグをセット
		pArray->SetIsMove(true);

		// 向かう目的地をセット
		pArray->SetDestPos(randomaiz);

		nSend++;
	}
}
//=========================================================
// 格納数設定処理
//=========================================================
void CArraySpawner::SetMaxArray(const int& nMaxArray)
{
	// 最大数をセットする
	if (nMaxArray > Config::MAX_STOCK)
	{
		m_nStockArrays = Config::MAX_STOCK;
	}
	else
	{
		m_nStockArrays = nMaxArray;
	}
}
//=========================================================
// 配置
//=========================================================
D3DXVECTOR3 CArraySpawner::RandomSetPos(const D3DXVECTOR3& pos, float fRadius, int nMoveActiveNum, int nIdx)
{
	// 以下なら
	if (nMoveActiveNum <= 0) return pos;

	// 角度を均等に割る
	float fAngle = (2.0f * D3DX_PI) * (static_cast<float>(nIdx) / nMoveActiveNum);

	// 基準値座標を設定する
	D3DXVECTOR3 OffSet = VECTOR3_NULL;
	OffSet.x = cosf(fAngle) * fRadius;
	OffSet.z = sinf(fAngle) * fRadius;
	OffSet.y = 0.0f;

	return pos + OffSet;
}

//=========================================================
// 生成関数
//=========================================================
CArraySpawner* CArraySpawner::Create(const D3DXVECTOR3 pos, const int nMaxArray, CArrayManager* pManager)
{
	// インスタンス生成
	CArraySpawner* pSpawner = new CArraySpawner;
	if (pSpawner == nullptr) return nullptr;

	// 値のセット
	pSpawner->SetMaxArray(nMaxArray);
	pSpawner->SetPos(pos);

	// 初期化失敗時
	if (FAILED(pSpawner->Init(pManager))) return nullptr;

	return pSpawner;
}