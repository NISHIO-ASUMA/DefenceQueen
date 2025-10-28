//=================================================
//
// ���f���t�@�C���Ǘ��N���X [ xfilemanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "xfilemanager.h"
#include "json.hpp"
#include "manager.h"
#include "texture.h"
#include <fstream>

//**********************
// �g�p���O���
//**********************
using json = nlohmann::json;

//**********************
// �ÓI�ϐ��錾
//**********************
int CXfileManager::m_nNumAll = NULL;

//========================
// �R���X�g���N�^
//========================
CXfileManager::CXfileManager()
{
	// �z��N���A
	m_aFileData.clear();
}
//========================
// �f�X�g���N�^
//========================
CXfileManager::~CXfileManager()
{
	// �S���̔j��
	UnLoad();
}
//========================
// �S���f���ǂݍ���
//========================
HRESULT CXfileManager::Load(void)
{
	// json���[�h
	LoadJson();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �S���f���j��
//========================
void CXfileManager::UnLoad(void)
{
	// ���̔j��
	for (auto iter = m_aFileData.begin(); iter != m_aFileData.end(); iter++)
	{
		// ���b�V���̔j��
		if ((*iter).pMesh != nullptr)
		{
			(*iter).pMesh->Release();
			(*iter).pMesh = nullptr;
		}

		// �}�e���A���|�C���^�̔j��
		if ((*iter).pBuffMat != nullptr)
		{
			(*iter).pBuffMat->Release();
			(*iter).pBuffMat = nullptr;
		}

		// �e�N�X�`���̔j��
		(*iter).pTexture.clear();

		// ���I�t�@�C���p�X�̔j��
		if (!(*iter).FilePath.empty())
		{
			(*iter).FilePath.clear();
			(*iter).FilePath.shrink_to_fit();
		}

		// �}�e���A���f�[�^�̔j��
		if ((*iter).dwNumMat != NULL)
		{
			(*iter).dwNumMat = 0;
		}
	}

	// �z��N���A
	m_aFileData.clear();
}
//========================
// ���f���o�^����
//========================
int CXfileManager::Register(const char* pFileName)
{
	// ���łɓo�^�ς݂Ȃ炻�̃C���f�b�N�X��Ԃ�
	for (int nCnt = 0; nCnt < m_aFileData.size(); nCnt++)
	{
		if (m_aFileData[nCnt].FilePath == pFileName)
			return nCnt;
	}

	// �V�K�o�^
	XFILEDATA newData = {};
	newData.FilePath = pFileName;

	//==============================
	// ���f���ǂݍ���
	//==============================
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice)
		return -1;

	// X�t�@�C�������[�h����
	HRESULT hr = D3DXLoadMeshFromX
	(
		pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&newData.pBuffMat,
		NULL,
		&newData.dwNumMat,
		&newData.pMesh
	);

	// ��O���b�Z�[�W
	if (FAILED(hr))
	{
		std::string msg = "���f���ǂݍ��݂Ɏ��s���܂���: ";
		msg += pFileName;
		MessageBox(GetActiveWindow(), msg.c_str(), "CXfileManager", MB_OK);
		return -1;
	}

	//==============================
	// ���f���T�C�Y�Z�o
	//==============================
	D3DXVECTOR3 Vtxmax = VECTOR3_NULL;
	D3DXVECTOR3 Vtxmin = VECTOR3_NULL;

	int nNumVtx = newData.pMesh->GetNumVertices();

	DWORD sizeFVF = D3DXGetFVFVertexSize(newData.pMesh->GetFVF());
	BYTE* pVtxBuff = nullptr;
	newData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���[�J���|�C���^
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (Vtx.x > Vtxmax.x) Vtxmax.x = Vtx.x;
		if (Vtx.y > Vtxmax.y) Vtxmax.y = Vtx.y;
		if (Vtx.z > Vtxmax.z) Vtxmax.z = Vtx.z;

		if (Vtx.x < Vtxmin.x) Vtxmin.x = Vtx.x;
		if (Vtx.y < Vtxmin.y) Vtxmin.y = Vtx.y;
		if (Vtx.z < Vtxmin.z) Vtxmin.z = Vtx.z;

		pVtxBuff += sizeFVF;
	}

	// �A�����b�N
	newData.pMesh->UnlockVertexBuffer();

	// �T�C�Y
	newData.Size.x = Vtxmax.x - Vtxmin.x;
	newData.Size.y = Vtxmax.y - Vtxmin.y;
	newData.Size.z = Vtxmax.z - Vtxmin.z;

	//==============================
	// �e�N�X�`���o�^
	//==============================
	newData.pTexture.clear();
	newData.pTexture.resize(newData.dwNumMat);

	if (newData.pBuffMat)
	{
		// �}�e���A���f�[�^�̃|�C���^
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)newData.pBuffMat->GetBufferPointer();

		// �e�N�X�`���|�C���^�擾
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < newData.dwNumMat; nCnt++)
		{
			if (pMat[nCnt].pTextureFilename)
			{
				// �e�N�X�`��ID�o�^
				int TexID = pTexture->Register(pMat[nCnt].pTextureFilename);
				newData.pTexture[nCnt] = TexID;
			}
			else
			{
				// �����l���Z�b�g
				newData.pTexture[nCnt] = -1;
			}
		}
	}

	// �z��ɓo�^����
	m_aFileData.push_back(newData);

	// �o�^�����X�V���ĕԂ�
	return m_nNumAll++; 
}
//========================
// json�t�@�C���ǂݍ���
//========================
HRESULT CXfileManager::LoadJson(void)
{
	// �t�@�C���I�[�v��
	std::ifstream openfile("data/JSON/XFile.json");

	// ��O����
	if (!openfile.is_open())
	{
		MessageBox(GetActiveWindow(), "XFile.json ���J���܂���", "xfilemanager", MB_OK);
		return E_FAIL;
	}

	// json�ǂݍ���
	json j;
	openfile >> j;
	openfile.close();

	// ��񂪂Ȃ�������
	if (j.is_null() || j.empty())
	{
		MessageBox(GetActiveWindow(), "XFile.json �Ƀf�[�^������܂���", "xfilemanager", MB_OK);
		return E_FAIL;
	}

	// �z��N���A
	m_aFileData.clear();

	// �����Z�b�g���Ă���
	for (const auto& entry : j)
	{
		// �������Ȃ�������
		if (!entry.contains("XFile") || entry["XFile"].is_null())
			continue;

		// �t�@�C���p�X�擾
		std::string filePath = entry["XFile"].get<std::string>();

		if (filePath.empty())
			continue;

		// ���f���ǂݍ���
		LoadModel(filePath.c_str());

		// �������Z
		m_nNumAll++;
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// ���f���o�^����
//========================
void CXfileManager::LoadModel(const char* pModelName)
{
	// �V�K�o�^
	XFILEDATA newData = {};
	newData.FilePath = pModelName;

	//==============================
	// ���f���ǂݍ���
	//==============================
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice)
		return;

	// ���f���ǂݍ���
	HRESULT hr = D3DXLoadMeshFromX(
		pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&newData.pBuffMat,
		NULL,
		&newData.dwNumMat,
		&newData.pMesh);

	// ��O�ݒ�
	if (FAILED(hr))
	{
		std::string msg = "���f���ǂݍ��݂Ɏ��s���܂���: ";
		msg += pModelName;
		MessageBox(GetActiveWindow(), msg.c_str(), "CXfileManager", MB_OK);
		return;
	}

	//==============================
	// ���f���T�C�Y�Z�o
	//==============================
	D3DXVECTOR3 Vtxmax = VECTOR3_NULL;
	D3DXVECTOR3 Vtxmin = VECTOR3_NULL;

	// ���_���̎擾
	int nNumVtx = newData.pMesh->GetNumVertices();

	DWORD sizeFVF = D3DXGetFVFVertexSize(newData.pMesh->GetFVF());
	BYTE* pVtxBuff = nullptr;
	newData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���[�J���|�C���^
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (Vtx.x > Vtxmax.x) Vtxmax.x = Vtx.x;
		if (Vtx.y > Vtxmax.y) Vtxmax.y = Vtx.y;
		if (Vtx.z > Vtxmax.z) Vtxmax.z = Vtx.z;

		if (Vtx.x < Vtxmin.x) Vtxmin.x = Vtx.x;
		if (Vtx.y < Vtxmin.y) Vtxmin.y = Vtx.y;
		if (Vtx.z < Vtxmin.z) Vtxmin.z = Vtx.z;

		pVtxBuff += sizeFVF;
	}

	// �A�����b�N
	newData.pMesh->UnlockVertexBuffer();

	// �T�C�Y
	newData.Size.x = Vtxmax.x - Vtxmin.x;
	newData.Size.y = Vtxmax.y - Vtxmin.y;
	newData.Size.z = Vtxmax.z - Vtxmin.z;

	//==============================
	// �e�N�X�`���o�^
	//==============================
	newData.pTexture.clear();
	newData.pTexture.resize(newData.dwNumMat);

	if (newData.pBuffMat)
	{
		// �}�e���A���|�C���^
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)newData.pBuffMat->GetBufferPointer();

		// �e�N�X�`���N���X�|�C���^�擾
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < newData.dwNumMat; nCnt++)
		{
			// null�`�F�b�N
			if (pMat[nCnt].pTextureFilename)
			{
				// �e�N�X�`��ID�Z�b�g
				int texID = pTexture->Register(pMat[nCnt].pTextureFilename);

				// �z��ɓo�^
				newData.pTexture[nCnt] = texID;
			}
			else
			{
				// -1�ŏ�����
				newData.pTexture[nCnt] = -1;
			}
		}
	}

	// �o�^����
	m_aFileData.push_back(newData);
}