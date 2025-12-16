//=========================================================
//
// 動かないキャラクタークラス処理 [ nomovecharactor.h ]
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
#include "object.h"
#include "model.h"
#include <memory>
#include <vector>

//*********************************************************
// 前方宣言
//*********************************************************
class CShadowS;
class CMotion;

//*********************************************************
// 動かないキャラクタークラスを定義
//*********************************************************
class CNoMoveCharactor : public CObject
{
public:

	CNoMoveCharactor(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CNoMoveCharactor();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetScale(const D3DXVECTOR3& scale = INITSCALE) { m_scale = scale; }
	void SetOldPos(const D3DXVECTOR3& posOld) { m_posOld = posOld; }
	void SetType(TYPE Type) { m_type = Type; }
	void SetUseStencil(bool isUse) { m_isStencilUse = isUse; }
	void SetUseOutLine(const bool isUse = false) { m_isOutLine = isUse; }

	void MotionLoad(const char* pScriptName, int nDestMotions, const bool isShadow);
	void SetCharactor(TYPE type) { m_type = type; }

	D3DXVECTOR3 GetPos(void) const { return m_pos; }
	D3DXVECTOR3 GetOldPos(void) const { return m_posOld; }
	D3DXVECTOR3 GetRot(void) const { return m_rot; }
	D3DXMATRIX GetWorldMtx(void) { return m_mtxworld; }

	/// <summary>
	/// モーションの生ポインタを返す
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CMotion* GetMotion(void) { return m_pMotion.get(); }

	/// <summary>
	/// モデルごとのマトリックス取得
	/// </summary>
	/// <param name="nIdx">取得番号</param>
	/// <returns></returns>
	D3DXMATRIX GetMtxModel(const int& nIdx) { return m_pModel[nIdx]->GetMtxWorld(); }

private:

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_posOld;	// 過去座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_rotDest;  // 目的角
	D3DXVECTOR3 m_scale;	// 拡大率
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス
	TYPE m_type;			// 種類

	std::unique_ptr<CMotion>m_pMotion;	// モーションクラスのユニークポインタ
	std::vector<CModel*>m_pModel;		// モデルクラスの動的配列
	CShadowS* m_pShadowS;				// ステンシルシャドウクラスのポインタ

	bool m_isStencilUse;				// ステンシルを使うかどうか
	bool m_isOutLine;
};