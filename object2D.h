//=====================================
//
// 2D�I�u�W�F�N�g���� [ object2D.h ]
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

//****************************
// �I�u�W�F�N�g2D�N���X���`
//****************************
class CObject2D : public CObject
{
public:

	//****************************
	// �A���J�[�|�C���g�^�C�v
	//****************************
	enum ANCHORTYPE
	{
		ANCHORTYPE_NONE,
		ANCHORTYPE_CENTER,
		ANCHORTYPE_LEFTSIDE,
		ANCHORTYPE_RIGHTSIDE,
		ANCHORTYPE_MAX
	};

	//****************************
	// �`��^�C�v
	//****************************
	enum DRAWTYPE
	{
		DRAWTYPE_NONE,
		DRAWTYPE_ANIM,
		DRAWTYPE_MAX,
	};

	CObject2D(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject2D* Create(void);

	void SetUV(float TexU, float TexV);
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetHeight(float fHeight) { m_fWidth = fHeight; }
	void SetFlash(const int nFirstcount, const int nEndcount, const D3DXCOLOR col);
	void SetAnchor(int Type = ANCHORTYPE_CENTER) { m_nAnchorType = Type; }
	void SetDrawType(int nType) { m_nDrawType = nType; }
	void SetCenter(void);
	void SetLeft(void);
	void SetRight(void);
	void SetTexture(const char* pRegisterName);

	D3DXVECTOR3 GetPos(void) const { return m_pos; }	// ���݂̍��W���擾
	D3DXVECTOR3 GetRot(void) const { return m_rot; }	// ���݂̊p�x���擾
	D3DXCOLOR GetCol(void) const { return m_col; }		// ���݂̐F���擾
	float GetWidth(void) const { return m_fWidth; }		// �����擾
	float GetHeight(void) const { return m_fHeight; }	// �����擾
	int GetDrawType(void) const { return m_nDrawType; }

private:

	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // ���_�o�b�t�@�̃|�C���^

	D3DXVECTOR3 m_pos;	// ���W���
	D3DXVECTOR3 m_rot;	// �p�x���
	D3DXCOLOR m_col;	// �F���

	int m_nAnchorType;	// ����W�ݒ�
	int m_nColorCount;	// �_�ŃJ�E���g
	int m_nDrawType;	// �`��^�C�v
	int m_nIdxTexture;	// �e�N�X�`���C���f�b�N�X
	float m_fWidth;		// ����
	float m_fHeight;	// ����
};
