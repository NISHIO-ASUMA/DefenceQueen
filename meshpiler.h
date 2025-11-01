//==================================
//
// �����b�V������ [ meshpiler.h ]
// Author: Asuma Nishio
//
//==================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//***************************
// ���󃁃b�V���N���X���`
//***************************
class CMeshPiler : public CObject
{
public:

	CMeshPiler(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshPiler();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* CollisionPos);

	void SetTexture(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CMeshPiler* Create(D3DXVECTOR3 pos);

private:

	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X

	int m_nTexIdx;		// �e�N�X�`���C���f�b�N�X
	int m_nNumPrimitive;	// �v���~�e�B�u��
	int m_nNumIdx;			// �C���f�b�N�X��
	int m_nNumAllVtx;		// �S�̒��_��
	int m_nNumDigitX, m_nNumDigitZ;		// ������
	int m_nLife;		// ����
	float m_fMoveSpeed; // �ړ����x
	float m_fNowHeight;	// ���ݍ���

	int m_nLifeFrame;		// �������ԁi�t���[�����j
	int m_nActiveDelay;		// �����蔻�肪�L���ɂȂ�܂ł̒x���t���[����
};