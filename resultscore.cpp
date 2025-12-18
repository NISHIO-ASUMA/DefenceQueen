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
#include <fstream>
#include "manager.h"
#include "load.h"
#include "number.h"
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
m_nScore(NULL)
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

	// 数値読み込み処理
	CResultScore::Load();

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
	// スコア格納
	int nScore = m_nScore;

	// 8桁分
	for (int nCntScore = 0; nCntScore < Config::NUM_SCORE; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % Config::NUM_DIGIT;
		nScore /= Config::NUM_DIGIT;

		// ナンバー更新
		m_pNumber[nCntScore]->Update();

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
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
// データ読み込み処理
//=========================================================
void CResultScore::Load(void)
{
	// nullなら
	if (!m_pLoad) return;

	// バイナリファイル読み込み開始
	m_nScore = m_pLoad->LoadInt("data/SCORE/GameScore.bin");
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
	scores[Config::WRITE_SCORE - 1] = m_nScore;

	//==============================
	// 降順ソート
	//==============================
	std::sort(scores.begin(), scores.end(), std::greater<int>());

	//==============================
	// 保存
	//==============================
	m_pLoad->SaveIntToFixedArray(filename, scores);
}