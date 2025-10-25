//=====================================
//
// �r���{�[�h���� [ billboard.h ]
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

//*************************
// �r���{�[�h�N���X���`
//*************************
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Flash(const int nMaxFlashTime,const int Digittime);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetTexture(const char* pTexName);
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetEnableZtest(bool isflags) { m_isTests = isflags; }
	void SetAnim(const int nMaxPattern, const int nMaxAnimCount, float fTexU, float fTexV);
	void SetUV(float fTexU, float fTexU1, float fTexV);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXCOLOR GetCol(void) { return m_col; };
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, const char* pTexName);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_rot;	// �p�x���
	D3DXVECTOR3 m_pos;	// ���W���
	D3DXCOLOR m_col;	// �F���
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X

	int m_nIdxTexture;	// �e�N�X�`���C���f�b�N�X
	int m_FlashCount;	// �_�ŊԊu
	int m_nCountAnim;	// �A�j���\�V�����Ԋu
	int m_nPatterAnim;	// �A�j���\�V�����p�^�[��
	float m_fHeight, m_fWidth;	// ����,����
	bool m_isTests;				// Z�e�X�g���邩�ǂ���
};
