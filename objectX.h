//=====================================
//
// X�t�@�C������ [ objectX.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//******************************
// �I�u�W�F�N�gX�N���X���`
//******************************
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void); 

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMtxWorld(D3DXMATRIX mtxworld) { m_mtxWorld = mtxworld; }
	void SetFilePass(const char* pFilePass);
	void SetModelIdx(const int nIdx) { m_nIdxModel = nIdx; }

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

	int GetModelIdx(void) const { return m_nIdxModel; }

	static CObjectX* Create(int nIdx, D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	int m_nIdxModel; // ���f���C���f�b�N�X
};