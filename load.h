//=================================================
//
// 各種ロード処理クラス [ load.h ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <vector>

//*************************
// ロード処理クラスを定義
//*************************
class CLoad
{
public:
	CLoad();
	~CLoad();

	void LoadInt(const char * loadfilename);
	void LoadIntToArray(const char* loadfilename);
	void SaveInt(const char* savefilename, const int OutputData);
	void SaveIntToArray(const char* savefilename, const std::vector<int>& ArrayData);

	static CLoad* Create(void);

private:
};

