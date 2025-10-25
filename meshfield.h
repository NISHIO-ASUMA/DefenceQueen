//============================================
//
// ���b�V���t�B�[���h���� [ meshfield.h ]
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

//**********************************
// ���b�V���t�B�[���h�N���X���`
//**********************************
class CMeshField : public CObject
{
public:
	CMeshField(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshField();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CMeshField* Create(D3DXVECTOR3 pos, float fRadius);

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_fRadius;		// ���a

	int m_nNumPrimitive;	// �v���~�e�B�u��
	int m_nNumIdx;			// �C���f�b�N�X��
	int m_nNumAllVtx;		// �S�̒��_��
	int m_nTexIdx;			// �e�N�X�`���C���f�b�N�X
};