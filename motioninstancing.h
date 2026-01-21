//=========================================================
//
// インスタンシング用モーション処理 [ motioninstancing.h ]
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
#include "model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "instancemotionmanager.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CMotionManager;
class CInstanceModel;

//*********************************************************
// インスタンシングするモデルのモーションクラスを定義
//*********************************************************
class CMotionInstancing
{
public:

	//*******************************
	// 結果を保持する構造体
	//*******************************
	struct MOTION_RESULT
	{
		std::vector<D3DXVECTOR3> pos; // 座標
		std::vector<D3DXVECTOR3> rot; // 角度

		// 配列のサイズを決定する関数
		void Resize(int nDataSize)
		{
			pos.resize(nDataSize);
			rot.resize(nDataSize);
		}
	};

	CMotionInstancing();
	~CMotionInstancing();

	void Update(std::vector<CInstanceModel*> pModel);
	void UpdateCurrentMotion(CInstanceMotionManager* pMption, CInstanceModel** ppModel, int nModelCount, const CInstanceMotionManager::MOTIONFILE& info);
	void UpdateBlend(CInstanceMotionManager* pMption, CInstanceModel** ppModel, int nModelCount, const CInstanceMotionManager::MOTIONFILE& info);
	void Debug(void);
	bool CheckFrame(int nStartMotion, int nEndMotion, int nMotionType);

	void SetMotion(int motiontype);
	void SetMotion(int nMotionType, bool isBlend, int nBlendFrame);
	inline void SetResetFrame(int nFrame) { m_nCounterMotion = nFrame; }

	inline int GetMotionType(void) { return m_motiontype; }
	inline bool GetFinishMotion(void) { return m_isFinishMotion; }

	/// <summary>
	/// インデックス登録処理
	/// </summary>
	/// <param name="pMotionName">モーションスクリプト名</param>
	/// <param name="pModel">モデルクラスの動的配列</param>
	/// <param name="nDestMotions">モーション数</param>
	/// <param name="isShadow">マトリックスシャドウを使うかどうか</param>
	void RegisterPath(const char* pMotionName, std::vector<CInstanceModel*>& pModel, int nDestMotions, const bool isShadow);

	/// <summary>
	/// モーション読み込み関数
	/// </summary>
	/// <param name="pFilename">モーションスクリプト名</param>
	/// <param name="pModel">モデルクラスの動的配列</param>
	/// <param name="nDestMotions">モーション数</param>
	/// <param name="isShadow">マトリックスシャドウを使うかどうか</param>
	/// <returns></returns>
	static std::unique_ptr<CMotionInstancing>Load(const char* pFilename, std::vector<CInstanceModel*>& pModel, int nDestMotions, const bool isShadow = false);

private:

	int m_nNumModels;		// モデル総数
	int m_nNumKey;			// キーの総数
	int m_nKey;				// 現在のキーNo
	int m_nCounterMotion;	// モーションのカウンター
	int m_nNextKey;			// 次のキー
	int m_motiontype;		// モーションタイプ
	int m_nMotionIdx;		// モーションファイル番号

	int m_motiontypeBlend;	// ブレンドの種類
	int m_nFrameBlend;		// ブレンドのフレーム数
	int m_nCounterBlend;	// ブレンドカウンター
	int m_nKeyBlend;		// ブレンドモーションの現在のキー
	int m_nNextKeyBlend;	// ブレンドモーションの次のキー
	int m_nNumAllFrame;		// キーごとのフレーム数
	int m_nAllFrameCount;	// 全体フレーム数

	bool m_isBlendMotion;	// ブレンドがあるかどうか
	bool m_isFinishMotion;	// モーションが終わったかどうか
	bool m_isFirstMotion;	// モーションが始まったフラグ
	bool m_isLoopMotion;	// ループするかどうか

	static constexpr int NEUTRAL = 0; // ニュートラル番号

	MOTION_RESULT m_ResultData; // モーション計算結果
	bool m_isDirty; // 再計算が必要か

	struct MOTION_CACHE_FRAME
	{
		std::vector<D3DXVECTOR3> pos;
		std::vector<D3DXVECTOR3> rot;
	};

	struct MOTION_CACHE
	{
		int motionType;
		int key;
		int counter;
		bool isBlend;

		MOTION_CACHE_FRAME frame;
	};

	MOTION_CACHE m_cache = {};
	bool m_cacheDirty = true;

	void MathMotionFrame(const CInstanceMotionManager::MOTIONFILE& info, CInstanceMotionManager* pManager);
	void UpdateFrameOnce(const CInstanceMotionManager::MOTIONFILE& info, CInstanceMotionManager* pManager);
	void ApplyCache(std::vector<CInstanceModel*>& pModel, const CInstanceMotionManager::MOTIONFILE& info);

	void CalcCurrent(CInstanceMotionManager* pManager,int nModelCount,const CInstanceMotionManager::MOTIONFILE& info);
	void CalcBlend(CInstanceMotionManager* pManager,int nModelCount, const CInstanceMotionManager::MOTIONFILE& info);

	/// <summary>
	/// 座標補完の計算関数
	/// </summary>
	/// <param name="nowKey">現在キー</param>
	/// <param name="nextKey">次のキ―</param>
	/// <param name="fDis">補完係数</param>
	/// <returns></returns>
	inline D3DXVECTOR3 LerpPosVec3
	(
		const CInstanceMotionManager::KEY& nowKey,
		const CInstanceMotionManager::KEY& nextKey,
		float fDis
	);

	/// <summary>
	/// 回転補完の計算関数
	/// </summary>
	/// <param name="nowKey">現在キー</param>
	/// <param name="nextKey">次のキ</param>
	/// <param name="fDis">補完係数</param>
	/// <returns></returns>
	inline D3DXVECTOR3 LerpRotVec3
	(
		const CInstanceMotionManager::KEY& nowKey,
		const CInstanceMotionManager::KEY& nextKey,
		float fDis
	);

};