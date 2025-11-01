//=====================================
//
// �������� [ number.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �i���o�[�N���X���`
//**********************
class CNumber
{
public:

	CNumber();
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, float fwidth, float fheight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(const char * pTexName);
	void SetSize(float fWidth, float fHeight);
	void SetDigit(int nDigit);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos;}
	void SetCol(D3DXCOLOR col);
	void SetFlash(const int nStartFrame, const int nEndFrame, D3DXCOLOR col);

	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

private:

	static constexpr float DIGIT_VALUE = 0.1f; // �e�N�X�`������������

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;				// ���W���
	D3DXCOLOR m_col;				// �F���
	float m_fWidth, m_fHeight;		// ����,����
	float m_TexU, m_TexU1,m_TexV;	// �e�N�X�`�����W
	int n_nColorCount;				// �F�ύX�J�E���g
	int m_nIdxTexture;				// �e�N�X�`���C���f�b�N�X
};