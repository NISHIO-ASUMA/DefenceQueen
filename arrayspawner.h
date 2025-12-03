//=========================================================
//
// 各ポイントごとのスポーン処理 [ arrayspawner.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// 前方宣言
//*********************************************************
class CArray;

//*********************************************************
// 一個のスポナーに対する処理のクラスを定義
//*********************************************************
class CArraySpawner
{	
public:

	CArraySpawner();
	~CArraySpawner();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3& pos) { m_SpawnBasePos = pos; }

	static CArraySpawner* Create(const D3DXVECTOR3 pos);

private:

	//****************************************
	// 定数構造体宣言
	//****************************************
	struct Config
	{
		static constexpr int MAX_STOCK = 50; // 最大保持数
	};

	D3DXVECTOR3 m_SpawnBasePos; // スポーンのベース座標
};

