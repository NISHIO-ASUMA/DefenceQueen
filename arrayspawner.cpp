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
#include "debugproc.h"

//=========================================================
// コンストラクタ
//=========================================================
CArraySpawner::CArraySpawner() :
	m_SpawnBasePos(VECTOR3_NULL),
	m_nStockArrays(NULL), 
	m_AssignedArrays{},
	m_ReturnAntList{},
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
	// Managerから渡された最大配列のうちのストック数分だけ持つ
	m_AssignedArrays = pManager->Allocate(m_nStockArrays);

	// トップのアリを生成
	m_pTopAnts = CTopAnt::Create(m_SpawnBasePos + D3DXVECTOR3(0.0f, 0.0f, 50.0f), VECTOR3_NULL);

	// 隊列の追従関係変数
	CArray* pPrev = nullptr;

	// セットされた数だけアクティブにする
	for (int nCnt = 0; nCnt < m_nStockArrays; nCnt++)
	{
		// ローカルポインタ
		CArray* pArray = m_AssignedArrays[nCnt];

		// 設定関連
		pArray->SetPos(m_SpawnBasePos);
		pArray->SetActive(true);

		if (nCnt == 0)
		{
			// 先頭は無し
			pArray->SetPrevAnt(nullptr);
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
		if (!pArray->GetIsAtBase()) continue;
		if (pArray->GetMove())  continue;
		if (pArray->GetisStop()) continue;

		// 移動フラグをセット
		pArray->SetIsMove(true);

		// 基地から出た判定にする
		pArray->SetAtBase(false);

		// 向かう目的地をセット
		pArray->SetDestPos(destPos);

		pArray->SetPrevAnt(nullptr);

		nSend++;
	}
}
//=========================================================
// 基地にもどる命令をする関数
//=========================================================
void CArraySpawner::OrderReturn(int nNum, const D3DXVECTOR3& returnpos)
{
	// カウント
	int nSend = 0;

	// 今動いているアリだけを抽出する配列を見る
	std::vector<CArray*> movingList;
	movingList.reserve(m_AssignedArrays.size());

	for (auto pArray : m_AssignedArrays)
	{
		if (!pArray) continue;
		if (!pArray->GetActive()) continue;

		if (pArray->GetMove())// 今動いているアリだけ
		{
			// 移動させたい配列に追加していく
			movingList.push_back(pArray);
		}
	}

	// 後ろからnNum個だけreturnさせる
	int count = 0;

	// 現在移動しているアリの中から抽出する
	// 最大数から減算するfor
	for (int i = (int)movingList.size() - 1; i >= 0; i--)
	{
		// 最大なら
		if (nSend >= nNum) break;

		// リスト取得
		auto pArray = movingList[i];
		if (!pArray) continue;

		// 基地にもどるフラグをセット
		pArray->SetReturnSpawn(true);
		pArray->SetIsMove(false);
		pArray->SetPrevAnt(nullptr);

		// 向かう目的地をセット
		pArray->SetDestPos(returnpos);

		// 送る数を加算
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

//=========================================================
// 配列のトップの仲間アリを返す
//=========================================================
CArray* CArraySpawner::GetTopArray() const
{
	return m_AssignedArrays[0]; // 先頭の配列
}
//=========================================================
// 動いているアリの最後尾を返す
//=========================================================
CArray* CArraySpawner::GetLastActiveAnt(void)
{
	// 最後尾配列から回す
	for (int nAnt = m_nStockArrays -1;nAnt >= 0;nAnt--)
	{
		if (!m_AssignedArrays[nAnt]->GetActive()) continue;
		if (!m_AssignedArrays[nAnt]->GetMove()) continue;

		// 移動かつアクティブなら
		if (m_AssignedArrays[nAnt]->GetActive() && m_AssignedArrays[nAnt]->GetMove())
		{
			// そのアリの番号を取得
			return m_AssignedArrays[nAnt];
		}
	}

	// 一匹のアリもついていない
	return nullptr;
}
//=========================================================
// 配列つなぎなおし
//=========================================================
void CArraySpawner::FollwoChain(void)
{
}
//=========================================================
// インデックスを取得する
//=========================================================
int CArraySpawner::GetArrayIndex(CArray* pArray)
{
	// アリの格納配列で回す
	for (int nCnt = 0; nCnt < m_AssignedArrays.size(); nCnt++)
	{
		// 一致したら
		if (m_AssignedArrays[nCnt] == pArray) return nCnt;
	}

	return -1;
}
//=========================================================
// 配列の中からインデックスを指定して取得
//=========================================================
CArray* CArraySpawner::GetArray(int index)
{
	if (index < 0 || index >= m_AssignedArrays.size()) return nullptr;
	return m_AssignedArrays[index];
}