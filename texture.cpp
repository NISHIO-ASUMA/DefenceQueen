//=====================================
//
// �e�N�X�`������ [ texture.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "texture.h"
#include "manager.h"
#include "json.hpp"
#include <fstream>

//**********************
// �g�p���O���
//**********************
using json = nlohmann::json;

//**********************
// �ÓI�����o�ϐ�
//**********************
int CTexture::m_nNumAll = NULL;	// �����Ǘ�

//===============================
// �R���X�g���N�^
//===============================
CTexture::CTexture()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_pTextureData[nCnt].TexName.clear();
		m_pTextureData[nCnt].TexData = nullptr;
	}
}
//===============================
// �f�X�g���N�^
//===============================
CTexture::~CTexture()
{
	// ���ׂĂ̔j��
	UnLoad();
}
//===============================
// �e�N�X�`���ǂݍ���
//===============================
HRESULT CTexture::Load(void)
{
	// json�K�p
	LoadJson();

	return S_OK;
}
//===============================
// �e�N�X�`���j��
//===============================
void CTexture::UnLoad(void)
{
	// ���ׂẴe�N�X�`���̔j��
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTextureData[nCnt].TexData)
		{
			m_pTextureData[nCnt].TexData->Release();
			m_pTextureData[nCnt].TexData = nullptr;
		}

		// �z��̃N���A
		m_pTextureData[nCnt].TexName.clear();
	}

	// ����������
	m_nNumAll = 0;
}
//===============================
// �e�N�X�`���ԍ���o�^����
//===============================
int CTexture::Register(const char* pFileName)
{
	// ���łɓo�^�ς݂Ȃ炻�̔ԍ���Ԃ�
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (m_pTextureData[nCnt].TexName == pFileName)
			return nCnt;
	}

	// �Ȃ������ꍇ,�V�K�o�^
	if (m_nNumAll < NUM_TEXTURE)
	{
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		// �e�N�X�`���̍쐬�ɐ���������
		if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice, pFileName, &m_pTextureData[m_nNumAll].TexData)))
		{
			// �z��ɕۑ�
			m_pTextureData[m_nNumAll].TexName = pFileName;

			// ���Z�C���f�b�N�X��Ԃ�
			return m_nNumAll++;
		}
	}

	return -1;
}
//===============================
// �e�N�X�`���ԍ��擾
//===============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	// ��O����
	if (nIdx < NULL || nIdx >= NUM_TEXTURE) return nullptr;

	// �e�N�X�`���ԍ����擾
	return m_pTextureData[nIdx].TexData;
}
//===============================
// json�t�@�C���ǂݍ���
//===============================
HRESULT CTexture::LoadJson(void)
{
	// JSON�t�@�C�����J��
	std::ifstream ifs("data/JSON/Texture.json");

	// �t�@�C�����J���Ȃ�������
	if (!ifs.is_open())
	{
		MessageBox(GetActiveWindow(), "json�t�@�C�����J���܂���", "�G���[", MB_OK);

		return E_FAIL;
	}

	// JSON�ǂݍ���
	json j;
	ifs >> j;

	// �����񂪂��邩�`�F�b�N
	if (j.is_null() || j.empty())
	{
		MessageBox(GetActiveWindow(), "�e�N�X�`���t�@�C��������܂���", "�G���[", MB_OK);

		return E_FAIL;
	}

	// �l�̏�����
	m_nNumAll = 0;

	// �e�N�X�`���ǂݍ���œo�^������
	for (const auto& tex : j)
	{
		// "Texture"�L�[�����݂��Ȃ� �܂��� null�Ȃ�X�L�b�v
		if (!tex.contains("Texture") || tex["Texture"].is_null())
			continue;

		// �t�@�C�����i�[
		std::string file = tex["Texture"].get<std::string>();

		// �ő�l�𒴂��Ă����� �܂��� �t�@�C�������Ȃ�������
		if (file.empty() || m_nNumAll >= NUM_TEXTURE)
			continue;

		// �e�N�X�`������z��̃f�[�^�Ɋi�[
		m_pTextureData[m_nNumAll].TexName = file;

		// ���������Z
		m_nNumAll++;
	}

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// null�Ȃ�
	if (!pDevice)
		return E_FAIL;

	// �o�^���ꂽ�t�@�C����ǂݍ���
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		// �e�N�X�`�������ۂɐ���
		HRESULT hr = D3DXCreateTextureFromFile(
			pDevice,
			m_pTextureData[nCnt].TexName.c_str(),
			&m_pTextureData[nCnt].TexData);

		// �쐬���s��
		if (FAILED(hr))
		{
			// null�ɂ���
			m_pTextureData[nCnt].TexData = nullptr;
		}
	}

	return S_OK;
}