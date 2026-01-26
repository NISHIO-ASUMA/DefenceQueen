//=========================================================
//
// チュートリアルのオブジェクト管理 [ tutorialobject.h ]
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
#include <memory>

//*********************************************************
// 前方宣言
//*********************************************************
class CBlockManager;

//*********************************************************
// チュートリアルで使うオブジェクトを管理するクラスを定義
//*********************************************************
class CTutorialObject
{
public:

	~CTutorialObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	inline CBlockManager* GetBlockManager(void) const { return m_pBlockManager.get(); }

	static CTutorialObject* GetInstance(void);

private:

	CTutorialObject(); // コンストラクタ

	static CTutorialObject* m_pInstance; // シングルトン変数

	std::unique_ptr<CBlockManager>m_pBlockManager; // ブロック管理
};

