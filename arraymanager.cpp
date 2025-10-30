//===============================================
//
// ���ԃN���X�S�̂̊Ǘ����� [ arraymanager.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "arraymanager.h"
#include "array.h"
#include "manager.h"
#include "input.h"
#include "template.h"
#include "debugproc.h"

//**********************
// �萔�錾���
//**********************
namespace ARRAYINFO
{
	constexpr int LIFE = 10; // �̗͒l
	constexpr int ALLARRAYS = 100; // �ő�g�p��
};

//===========================
// �R���X�g���N�^
//============================
CArrayManager::CArrayManager() : m_pArrays{}, m_nActiveAll(NULL)
{

}
//===========================
// �f�X�g���N�^
//============================
CArrayManager::~CArrayManager()
{
	Uninit();
}
//===========================
// ����������
//============================
HRESULT CArrayManager::Init(const int nActives)
{
	// �z�񏉊���
	m_pArrays.clear();

	// �T�C�Y�m��
	m_pArrays.reserve(ARRAYINFO::ALLARRAYS);

	// ���炩���ߍő吔��������
	for (int nCnt = 0;nCnt < m_pArrays.size();nCnt++)
	{
		// �C���X�^���X����
		auto pArray = CArray::Create(VECTOR3_NULL,VECTOR3_NULL,ARRAYINFO::LIFE);
		m_pArrays.push_back(pArray);
	}

	// �T�C�Y�͈͓̔��`�F�b�N
	int nUse = Clump(nActives, 0, static_cast<int>(m_pArrays.size()));

	for (int nActive = 0; nActive < nUse; nActive++)
	{
		// �v�f����
		auto pArray = m_pArrays[nActive];

		// �L����Ԃɂ���
		pArray->SetActive(true);

		// �A�N�e�B�u�������Z
		m_nActiveAll++;
	}

	return S_OK;
}
//===========================
// �I������
//============================
void CArrayManager::Uninit(void)
{
	// �j��
	m_pArrays.clear();
}
//===========================
// �X�V����
//============================
void CArrayManager::Update(void)
{
#ifdef _DEBUG

	// �L�[�擾
	auto* pInputKey = CManager::GetInstance()->GetInputKeyboard();

	// �L�[���͂ő����m�F
	if (pInputKey->GetTrigger(DIK_N))
	{// ����������
		m_nActiveAll = Clump(m_nActiveAll + 1, 0, static_cast<int>(m_pArrays.size()));
	}
	else if (pInputKey->GetTrigger(DIK_M))
	{// ����������
		m_nActiveAll = Clump(m_nActiveAll - 1, 0, static_cast<int>(m_pArrays.size()));
	}

#endif // _DEBUG
}
//===========================
// �`�揈��
//============================
void CArrayManager::Draw(void)
{
	// �f�o�b�O�\��
	CDebugproc::Print("���݂̃A�N�e�B�u�� : [ %d ] ", m_nActiveAll);
	CDebugproc::Draw(0, 120);
}
//===========================
// �o���Ǘ�����
//============================
void CArrayManager::Spawn(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,const int nNumSpawn)
{
	// �o������͈͓��ɐ���
	int nSpawnCount = Clump(nNumSpawn, 0, static_cast<int>(m_pArrays.size()));

	// �X�|�[������J�E���g
	int nSpawned = 0;

	for (auto& pArray : m_pArrays)
	{
		// false�̕���T��
		if (!pArray->GetActive())
		{
			// �Đݒ菈��
			pArray->Reset(pos, rot, nLife);

			// �J�E���g���Z
			nSpawned++;

			// �w�萔�o��������I��
			if (nSpawned >= nSpawnCount) break;
		}
	}

	// �o���ł��Ȃ������ꍇ�̃��O
#ifdef _DEBUG
	if (nSpawned < nSpawnCount)
	{
		OutputDebugStringA("�o���ł��܂���ł���");
	}
#endif
}
