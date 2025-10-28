//=====================================
//
// �u���b�N���� [ block.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "block.h"
#include "boxcollider.h"
#include "collisionbox.h"
#include "xfilemanager.h"
#include "manager.h"

//=====================================
// �R���X�g���N�^
//=====================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_pCollider(nullptr)
{
	// �l�̃N���A
}
//=====================================
// �f�X�g���N�^
//=====================================
CBlock::~CBlock()
{
	// ����
}
//=====================================
// ��������
//=====================================
CBlock* CBlock::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale, const char* pModelName)
{
	// �C���X�^���X����
	CBlock* pBlock = new CBlock;
	if (pBlock == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(scale);
	pBlock->SetFilePass(pModelName);

	// ���������s��
	if (FAILED(pBlock->Init())) return nullptr;

	return pBlock;
}
//=====================================
// ����������
//=====================================
HRESULT CBlock::Init(void)
{
	// �e�N���X�̏���������
	CObjectX::Init();

	// X�t�@�C���I�u�W�F�N�g�擾
	CXfileManager* pXManager = CManager::GetInstance()->GetXManager();
	if (pXManager == nullptr) return E_FAIL;

	// �C���f�b�N�X�ԍ����擾
	int nModelIdx = GetModelIdx();

	// ���f���̃T�C�Y�擾
	D3DXVECTOR3 Size = pXManager->GetInfo(nModelIdx).Size;

	// �R���C�_�[����
	m_pCollider = CBoxCollider::Create(GetPos(), GetPos(), Size);

	return S_OK;
}
//=====================================
// �I������
//=====================================
void CBlock::Uninit(void)
{
	// null�`�F�b�N
	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}

	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//=====================================
// �X�V����
//=====================================
void CBlock::Update(void)
{
	// �R���C�_�[���W�̍X�V
	m_pCollider->SetPos(GetPos());
}
//=====================================
// �`�揈��
//=====================================
void CBlock::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}
//=====================================
// �����蔻��
//=====================================
bool CBlock::Collision(CBoxCollider* pOther, D3DXVECTOR3* OutPos)
{
	// ��`�̓����蔻���Ԃ�
	return CCollisionBox::Collision(m_pCollider, pOther, OutPos);
}