//=============================================
//
// ���b�V���V�����_�[���� [ meshcylinder.h ]
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
// ���b�V���V�����_�[�N���X���`
//**********************************
class CMeshCylinder : public CObject
{
public:

	CMeshCylinder(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshCylinder();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetRadius(void) const { return m_fRadius; }

	static CMeshCylinder* Create(D3DXVECTOR3 pos, float fRadius);

private:
	static constexpr int DIGIT_X = 30;		// X�����̕�����
	static constexpr int DIGIT_Z = 1;		// Z�����ւ̕�����

	int m_nTexIdx;		// �e�N�X�`���C���f�b�N�X
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_vtxPos[DIGIT_X]; // ����p���W

	int m_nNumPrimitive;	// �v���~�e�B�u��
	int m_nNumIdx;			// �C���f�b�N�X��
	int m_nNumAllVtx;		// �S�̒��_��
	int m_nNumDigitX, m_nNumDigitZ;		// ������
	float m_fRadius;		// ���a
};