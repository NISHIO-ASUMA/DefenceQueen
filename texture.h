//=====================================
//
// �e�N�X�`������ [ texture.h ]
// Author: Asuma Nishio
// 
//=====================================

//*****************************
// �C���N���[�h�K�[�h
//*****************************
#pragma once

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include <string>

//*****************************
// �e�N�X�`���Ǘ��N���X���`
//*****************************
class CTexture
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTexture();
	~CTexture();

	// �����o�֐�
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:

	HRESULT LoadJson(void);

	//*************************
	// �e�N�X�`���f�[�^�\����
	//*************************
	struct TEXDATA
	{
		std::string TexName; // �e�N�X�`����
		LPDIRECT3DTEXTURE9 TexData; // �e�N�X�`���|�C���^
	};

	static constexpr int NUM_TEXTURE = 128;	// �ő�e�N�X�`����

	TEXDATA m_pTextureData[NUM_TEXTURE]; // �e�N�X�`���Ǘ��z��
	static int m_nNumAll;				 // �e�N�X�`���J�E���g�ϐ�
};
