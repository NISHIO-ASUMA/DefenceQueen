//====================================
//
// 3D�I�u�W�F�N�g���� [ object3D.h ]
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

//*******************************
// �I�u�W�F�N�g3D�N���X���`
//*******************************
class CObject3D : public CObject
{ 
public:

	CObject3D(int nPriority = static_cast<int>(CObject::PRIORITY::BASENUMBER));
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col;}
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetTexture(const char * pTexName);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXCOLOR GetCol(void) { return m_col; }
	float GetWidth(void) { return m_fWidth; }
	float Getheight(void) { return m_fHeight; }

	float GetHeight(D3DXVECTOR3 pos);

	static CObject3D* Create(D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_rot;	// �p�x���
	D3DXVECTOR3 m_pos;	// ���W���
	D3DXCOLOR m_col;	// �F���

	int m_nIdxTexture;						// �e�N�X�`���C���f�b�N�X
	float m_fWidth;		// ����
	float m_fHeight;	// ����
};