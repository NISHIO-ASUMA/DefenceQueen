//=======================================
//
// �u���b�N�Ǘ����� [ blockmanager.cpp ]
// Author: Asuma Nishio
//
//=======================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "blockmanager.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

//**********************
// �g�p���O���
//**********************
using json = nlohmann::json;

//**********************
// �ÓI�����o�ϐ��錾
//**********************
std::vector<CBlock*>CBlockManager::m_pBlocks = {}; // �z��

//===================================
// �R���X�g���N�^
//===================================
CBlockManager::CBlockManager()
{

}
//===================================
// �f�X�g���N�^
//===================================
CBlockManager::~CBlockManager()
{
	Uninit();
}
//===================================
// �u���b�N�����֐�
//===================================
CBlock* CBlockManager::CreateManager(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName)
{
	// �C���X�^���X����
	CBlock* pNewBlock = CBlock::Create(pos, rot, scale, pModelName);

	if (pNewBlock)
	{
		// �z��ɒǉ�
		m_pBlocks.push_back(pNewBlock);
	}

	return pNewBlock;
}
//===================================
// ����������
//===================================
HRESULT CBlockManager::Init(void)
{
	// �z��̃N���A
	m_pBlocks.clear();

	// �t�@�C���ǂݍ���
	Load();

	return S_OK;
}
//===================================
// �I������
//===================================
void CBlockManager::Uninit(void)
{
	// �z��̃N���A
	m_pBlocks.clear();
}
//===================================
// �X�V����
//===================================
void CBlockManager::Update(void)
{
	// ����
}
//===================================
// json�ǂݍ���
//===================================
HRESULT CBlockManager::Load()
{
	// �J���t�@�C��
	std::ifstream file("data/JSON/Map.json");

	// �J����������
	if (!file.is_open())
	{
		// ��O
		MessageBox(GetActiveWindow(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);

		// �I��
		return E_FAIL;
	}

	json j;
	file >> j;

	// �t�@�C�������
	file.close();

	// �����̃u���b�N������
	for (auto block : m_pBlocks)
	{
		if (block != nullptr)
		{
			// �u���b�N�̏I������
			block->Uninit();
		}
	}

	// ���I�z�����ɂ���
	m_pBlocks.clear();

	// SetObjects�̔z�����
	for (const auto& b : j["SetObjects"])
	{
		std::string filepath = b["filepath"];
		int idx = b["idx"];

		D3DXVECTOR3 pos(
			b["pos"][0],
			b["pos"][1],
			b["pos"][2]
		);
		D3DXVECTOR3 rot(
			b["rot"][0],
			b["rot"][1],
			b["rot"][2]
		);

		D3DXVECTOR3 size(
			b["scale"][0],
			b["scale"][1],
			b["scale"][2]
		);

		// �u���b�N����
		CBlock* block = CreateManager(pos, rot, size, filepath.c_str());
	}

	return S_OK;
}
