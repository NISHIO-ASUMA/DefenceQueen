//=========================================================
//
// リザルトに表示するスコアの処理 [ resultscore.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "resultscore.h"
#include "manager.h"
#include "load.h"
#include "number.h"
#include "easing.h"
#include <fstream>
#include <algorithm>

//=========================================================
// コンストラクタ
//=========================================================
CResultScore::CResultScore(int nPriority) : CObject(nPriority),
m_pLoad(nullptr),
m_pNumber{},
m_pos(VECTOR3_NULL),
m_fHeight(NULL),
m_fWidth(NULL),
m_nCurrentScore(NULL),
m_nDuration(NULL),
m_nLoadScore(NULL),
m_nStartScore(NULL),
m_nTargetScore(NULL),
m_nTimer(NULL),
m_isUse(false)
{

}
//=========================================================
// デストラクタ
//=========================================================
CResultScore::~CResultScore()
{

}
//=========================================================
// 生成処理
//=========================================================
CResultScore* CResultScore::Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight)
{
	// インスタンス生成
	CResultScore* pscore = new CResultScore;
	if (pscore == nullptr) return nullptr;

	// オブジェクト設定
	pscore->m_pos = pos;
	pscore->m_fWidth = fWidth;
	pscore->m_fHeight = fHeight;

	// 初期化失敗時
	if (FAILED(pscore->Init())) return nullptr;

	return pscore;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CResultScore::Init(void)
{
	// 横幅計算
	float fTexPos = m_fWidth / Config::NUM_SCORE;

	// 桁数分
	for (int nCnt = 0; nCnt < Config::NUM_SCORE; nCnt++)
	{
		// インスタンス生成
		m_pNumber[nCnt] = new CNumber;

		// 初期化処理
		m_pNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);

		// ナンバー変数のサイズ
		m_pNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// 座標設定
		m_pNumber[nCnt]->SetPos(m_pos);

		// テクスチャセット
		m_pNumber[nCnt]->SetTexture("number003.png");
	}

	// ポインタ生成
	m_pLoad = std::make_unique<CLoad>();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CResultScore::Uninit(void)
{
	// 破棄する前に書き出し実行
	Save();

	// ポインタの破棄
	for (auto number : m_pNumber)
	{
		// nullチェック
		if (number != nullptr)
		{
			number->Uninit();
			delete number;
			number = nullptr;
		}
	}

	// ユニークポインタの破棄
	m_pLoad.reset();

	// 自身の破棄
	CObject::Release();
}
//=========================================================
// 更新処理
//=========================================================
void CResultScore::Update(void)
{
	// アニメーション更新
	UpdateAnimScore();
}
//=========================================================
// 描画処理
//=========================================================
void CResultScore::Draw(void)
{
	// ナンバーの描画
	for (auto number : m_pNumber)
	{
		number->Draw();
	}
}
//=========================================================
// データ書き出し処理
//=========================================================
void CResultScore::Save(void)
{
	// nullだったら
	if (!m_pLoad) return;

	// 元データのファイル名
	const char* filename = "data/SCORE/Ranking.bin";

	//==============================
	// 既存ランキング(5件)を読む
	//==============================
	std::array<int, Config::WRITE_SCORE> scores = { NULL };

	{
		std::ifstream file(filename, std::ios::binary);

		if (file)
		{
			// 5件読み込み
			file.read((char*)scores.data(),sizeof(int) * Config::WRITE_SCORE);
		}
	}

	//==============================
	// 今回のスコアを追加
	//==============================
	scores[Config::WRITE_SCORE - 1] = m_nLoadScore;

	//==============================
	// 降順ソート
	//==============================
	std::sort(scores.begin(), scores.end(), std::greater<int>());

	//==============================
	// 保存
	//==============================
	m_pLoad->SaveIntToFixedArray(filename, scores);
}
//=========================================================
// アニメーション更新関数
//=========================================================
void CResultScore::UpdateAnimScore(void)
{
	// まだアニメ中
	if (m_nTimer < m_nDuration)
	{
		// イージング適用
		float t = CEasing::SetEase(m_nTimer, m_nDuration);
		float fRate = CEasing::EaseOutCubic(t);

		// 現在スコアをイージングさせる
		m_nCurrentScore = m_nStartScore + (int)((m_nLoadScore - m_nStartScore) * fRate);

		// 加算
		m_nTimer++;
	}
	else
	{
		// 現在スコアに設定
		m_nCurrentScore = m_nLoadScore;
	}

	// 桁数更新
	int nScore = m_nCurrentScore;

	// 八桁分
	for (int nCntScore = 0; nCntScore < Config::NUM_SCORE; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % Config::NUM_DIGIT;
		nScore /= Config::NUM_DIGIT;

		// ナンバーの更新
		m_pNumber[nCntScore]->Update();

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
}
//=========================================================
// スコアの0をカウント
//=========================================================
int CResultScore::ScoreCounter(const int nScore)
{
	int nNum = nScore;		//スコアの0の部分をカウント
	int nKeepNum = 0;		//スコアの桁数

	while (nNum != 0)		//割り切れなくなるまで繰り返す(0まで)
	{
		nNum /= 10;			//nNumを10で割っていく
		nKeepNum++;			//桁数を加算
	}
	if (nScore == 0)
	{
		//1桁目に0が入っているとき
		nKeepNum = 1;
	}

	return nKeepNum;		//スコアの桁数を返す
}
//=========================================================
// アニメーションするスコアをセットする関数
//=========================================================
void CResultScore::SetAnimScore(const int nDestScore)
{
	m_nStartScore = 0;			// 初期値
	m_nLoadScore = nDestScore;  // 目的のスコア
	m_nCurrentScore = 0;		// 現在の値

	m_nTimer = 0;				// カウントタイマー
	m_nDuration = Config::MAX_ANIMTIME; // 3秒掛けて目的の値に
}