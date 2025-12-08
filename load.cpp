//=========================================================
//
// 各種ロード処理クラス [ load.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "load.h"
#include <fstream>
#include <iostream>
#include <algorithm>

//=========================================================
// コンストラクタ
//=========================================================
CLoad::CLoad()
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CLoad::~CLoad()
{
	// 無し
}
//=========================================================
// 一つのバイナリ数値データを読み込む
//=========================================================
int CLoad::LoadInt(const char* loadfilename)
{
	// 格納用変数
	int nReturnScore = 0;

	// ファイルを開く
	std::ifstream Openfile(loadfilename, std::ios::binary);

	if (!Openfile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "エラー発生", "ファイルが見つかりません!( 関数 : LoadInt )", MB_OK);
		return -1;
	}

	// 読み取ったスコアを入れる
	Openfile.read(reinterpret_cast<char*>(&nReturnScore), sizeof(int));

	// 読み込み失敗チェック
	if (Openfile.fail())
	{
		MessageBox(GetActiveWindow(),
			"エラー発生",
			"データの読み込みに失敗しました!( 関数 : LoadInt )",
			MB_OK);

		return -1;
	}

	// ファイルを閉じる
	Openfile.close();

	// 格納スコアを返す
	return nReturnScore;
}
//=================================================================
// 一つのバイナリ数値データを書き出す
//=================================================================
void CLoad::SaveInt(const char* savefilename, const int OutputData)
{
	// 書き出すファイルを開く
	std::ofstream Openfile(savefilename, std::ios::binary);
	if (!Openfile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "書き出し失敗", "ファイルが見つかりません( SaveInt )", MB_OK);
		return;
	}

	// 数値を書き出す
	Openfile.write(reinterpret_cast<const char*>(&OutputData), sizeof(int));

	// ファイルを閉じる
	Openfile.close();
}
//=============================================================
// 配列のバイナリデータを書き出す
//=============================================================
void CLoad::SaveIntToArray(const char* savefilename, const std::vector<int>& ArrayData)
{
	// 書き出すファイルを開く
	std::ofstream Openfile(savefilename, std::ios::binary);
	if (!Openfile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "書き出し失敗", "ファイルが見つかりません( SaveIntToArray )", MB_OK);
		return;
	}

	// ソート用に一時保存
	std::vector<int>SortData = ArrayData;

	// 降順にソート
	std::sort(SortData.begin(), SortData.end(), std::greater<int>());

	// 要素数を書き出す
	int nNumData = static_cast<int>(ArrayData.size());
	Openfile.write((const char*)(&nNumData), sizeof(int));

	// 配列データをバイナリ形式で書き出す
	Openfile.write((const char*)(ArrayData.data()), sizeof(int) * nNumData);
	
	// ファイルを閉じる
	Openfile.close();
}