//=========================================================
//
// モーションファイル管理クラス [ motionmanager.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include <string>
#include <vector>
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CMotion;
class CModel;

//*********************************************************
// 管理クラスを定義
//*********************************************************
class CMotionManager
{
public:

	//*********************************
	// モーションファイルデータ構造体
	//*********************************
	struct MOTIONFILE
	{
		std::string FilePath;	// ファイル名
		std::unique_ptr<CMotion>pMotion; // モーションクラスのユニークポインタ
	};

	CMotionManager();
	~CMotionManager();

	HRESULT Load(void);
	void UnLoad(void);

	/// <summary>
	/// モーションファイルを登録する
	/// </summary>
	/// <param name="pMotionName">登録したいファイル名</param>
	/// <returns></returns>
	int Register(const char* pMotionName,std::vector<CModel*>& pModel, const int nNumMotion,const bool isShadow);

	/// <summary>
	/// 配列番号を指定して情報を取得
	/// </summary>
	/// <param name="nIdx">取得したいインデックス</param>
	CMotion* GetMotion(const int nIdx) { return m_File[nIdx].pMotion.get(); }

	MOTIONFILE &GetInfo(const int nIdx) { return m_File[nIdx]; }

private:

	// モーション読み込み関数
	std::unique_ptr<CMotion> LoadMotionFile(const char* pScript, std::vector<CModel*>& pModel, const int nNumMotion, const bool isShadow);

	// 動的配列
	std::vector<MOTIONFILE>m_File;
};