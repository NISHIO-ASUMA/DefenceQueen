//=================================================
//
// ���f���t�@�C���Ǘ��N���X [ xfilemanager.h ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <string>
#include <vector>

//**********************
// �Ǘ��N���X���`
//**********************
class CXfileManager
{
public:
	//*************************
	// X�t�@�C���f�[�^�\����
	//*************************
	struct XFILEDATA
	{
		D3DXVECTOR3 Size;		// ���f���̃T�C�Y
		LPD3DXMESH pMesh;		// ���b�V���̃|�C���^
		LPD3DXBUFFER pBuffMat;	// �}�e���A���̃|�C���^
		DWORD dwNumMat;			// �}�e���A����
		std::vector<int>pTexture; // �e�N�X�`���̓��I�|�C���^
		std::string FilePath;	// �t�@�C����
	};

	CXfileManager();
	~CXfileManager();

	HRESULT Load(void);
	void UnLoad(void);
	void LoadModel(const char* pModelName);
	int Register(const char* pFileName);

	XFILEDATA GetInfo(const int nIdx) { return m_aFileData[nIdx]; } // �z��ԍ��擾
	std::vector<XFILEDATA>& GetList(void) { return m_aFileData; } // �I�u�W�F�N�g�{��

private:

	HRESULT LoadJson(void); // json�ǂݍ���

	// ���I�z��
	std::vector<XFILEDATA>m_aFileData;	// ���f���Ǘ��z��
	static int m_nNumAll; // ���f���̑���
};

