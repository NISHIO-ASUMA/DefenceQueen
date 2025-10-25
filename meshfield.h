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
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRaiusZ(float fRadius) { m_fRadiusZ = fRadius; }
	void SetRaiusX(float fRadius) { m_fRadius = fRadius; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetRadiusX(void) { return m_fRadius; }
	float GetRadiusZ(void) { return m_fRadiusZ; }

	static CMeshField* Create(D3DXVECTOR3 pos, float fRadiusX, float fRadiusZ, int nNumX, int nNumZ);

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_fRadius;		// X�����̔��a
	float m_fRadiusZ;		// Z�����̔��a

	int m_nNumPrimitive;	// �v���~�e�B�u��
	int m_nNumIdx;			// �C���f�b�N�X��
	int m_nNumAllVtx;		// �S�̒��_��
	int m_nTexIdx;			// �e�N�X�`���C���f�b�N�X
	int m_nNumX;			// X���_
	int m_nNumZ;			// Z���_

};