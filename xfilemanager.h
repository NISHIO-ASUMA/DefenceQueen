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

	/// <summary>
	/// X�t�@�C���̓o�^������
	/// </summary>
	/// <param name="pFileName">�o�^���郂�f����</param>
	/// <returns></returns>
	int Register(const char* pFileName);

	/// <summary>
	/// �z��ԍ����w�肵�ď����擾
	/// </summary>
	/// <param name="nIdx">�擾����I�u�W�F�N�g�C���f�b�N�X</param>
	/// <returns>�C���f�b�N�X�ԍ��ɉ������f�[�^</returns>
	XFILEDATA GetInfo(const int nIdx) { return m_aFileData[nIdx]; }

	/// <summary>
	/// ���I�z��̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns>�z��|�C���^</returns>
	std::vector<XFILEDATA>& GetList(void) { return m_aFileData; }

private:

	HRESULT LoadJson(void);					// jsonfile�ǂݍ��݊֐�
	void LoadModel(const char* pModelName); // ���f���o�^�֐�

	std::vector<XFILEDATA>m_aFileData;	// ���f���f�[�^�Ǘ��z��
	static int m_nNumAll; // ���f���̑���
};

