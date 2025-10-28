//=================================================
//
// 動くキャラクタークラス処理 [ movecharactor.h ]
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
#include "object.h"
#include <memory>
#include <vector>

//**********************
// 前方宣言
//**********************
class CShadowS;
class CModel;
class CMotion;

//*********************************
// 動くキャラクタークラスを定義
//*********************************
class CMoveCharactor : public CObject
{
public:
	//****************************
	// キャラクターの種類定義
	//****************************
	enum TYPE
	{
		TYPE_NONE,
		TYPE_PLAYER,
		TYPE_BUDDY,
		TYPE_ENEMY,
		TYPE_MAX
	};

	CMoveCharactor(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CMoveCharactor();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetOldPos(const D3DXVECTOR3 posOld) { m_posOld = posOld; }

	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetRotDest(const D3DXVECTOR3 rotdest) { m_rotDest = rotdest; }

	void SetScale(const D3DXVECTOR3 scale = INITSCALE) { m_scale = scale; }
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void SetMoveValue(const float fValue) { m_fMoveValue = fValue; }
	void SetType(TYPE Type) { m_type = Type; }
	void MotionLoad(const char* pScriptName,int nDestMotions);
	void SetCharactor(TYPE type) { m_type = type; }

	D3DXVECTOR3 GetPos(void) const { return m_pos; }
	D3DXVECTOR3 GetOldPos(void) const { return m_posOld; }
	D3DXVECTOR3 GetRot(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	D3DXVECTOR3 GetRotDest(void) const { return m_rotDest; }

	/// <summary>
	/// モーションのポインタを返す
	/// </summary>
	/// <param name=""></param>
	/// <returns>
	CMotion* GetMotion(void) { return m_pMotion.get(); }

private:
	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_posOld;	// 過去座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_rotDest;  // 目的角
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_scale;	// 拡大率
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス
	TYPE m_type;			// 種類

	std::unique_ptr<CMotion>m_pMotion;	// モーションクラスのユニークポインタ
	std::vector<CModel*>m_pModel;		// モデルクラスの動的配列
	CShadowS* m_pShadowS;				// ステンシルシャドウクラスのポインタ

	float m_fMoveValue;		// 移動加算値
};