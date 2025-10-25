//=============================================
//
// ���b�V���C���p�N�g���� [ meshimpact.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************
// �Ռ��g�̃N���X��`
//**********************
class CMeshImpact : public CObject
{
public:
	CMeshImpact(int nPriority = static_cast<int>(CObject::PRIORITY::IMPACT));
	~CMeshImpact();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* pPos);

	void SetCol(D3DXCOLOR col) { m_col = col; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CMeshImpact* Create(D3DXVECTOR3 pos, int nLife, float fRadius, float fInRadius,float fSpeed);

private:
	D3DXVECTOR3 m_pos;	// ���W
	D3DXVECTOR3 m_rot;  // �p�x
	D3DXCOLOR m_col;	// �F
	D3DXMATRIX m_mtxWorld; // ���[���h�}�g���b�N�X
	LPDIRECT3DINDEXBUFFER9 m_pIdx;	// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx; // ���_�o�b�t�@

	float m_fInRadius;		// ���a
	float m_fOutRadius;		// �O�a
	int m_nLife;			// ����
	float m_DecAlpha;		// ���l����
	float m_fSpeed;			// �g�呬�x
};