//=========================================================
//
// モデル処理 [ model.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once 

//*********************************************************
// モデルクラスの定義
//*********************************************************
class CModel
{
public:

	//**********************
	// パーツのタイプ列挙型
	//**********************
	enum PARTTYPE
	{
		PARTTYPE_NONE, // 何も種類を設定しない時
		PARTTYPE_HEAD, // 頭
		PARTTYPE_CHEST, // 体
		PARTTYPE_LEFT_HAND, // 左腕
		PARTTYPE_RIGHT_HAND,// 右腕
		PARTTYPE_LEFT_LEG, //左足
		PARTTYPE_RIGHT_LEG,// 右足
		PARTTYPE_WEAPON,// 武器
		PARTTYPE_MAX
	};

	CModel();
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename,const bool isShadow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawMtxShadow(void);
	void DrawAtOnce(UINT SubSet);
	void SetModelPass(const char* pModelName);

	void SetParent(CModel* pModel);
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetScale(const D3DXVECTOR3& scale = INITSCALE) { m_scale = scale; }
	void OffSetPos(const D3DXVECTOR3& offpos) { m_offPos = offpos; }
	void OffSetRot(const D3DXVECTOR3& offrot) { m_offRot = offrot; }
	void SetPartType(PARTTYPE nDestPartType) { m_parttype = nDestPartType; }
	void SetMtxShadow(bool isShadow) { m_isShadow = isShadow; }

	D3DXMATRIX GetMtxWorld(void) { return m_mtxworld; }
	PARTTYPE GetPartType(void) const { return m_parttype; }

	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename,const bool isShadow);

private:

	D3DXVECTOR3 m_pos, m_rot,m_offPos,m_offRot,m_scale; // 座標,角度,大きさ
	D3DXMATRIX m_mtxworld;	  // ワールドマトリックス
	CModel* m_pParent;		  // 親モデル
	PARTTYPE m_parttype;	// モデルの種類

	int* m_pTexture;		// テクスチャポインタ
	bool m_isShadow;		// 影を設定するかどうか
	int m_nModelIdx;		// モデルインデックス
};