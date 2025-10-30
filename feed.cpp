//===============================================
//
// �o������a�̏��� [ feed.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "feed.h"

//============================
// �R���X�g���N�^
//============================
CFeed::CFeed(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
}
//============================
// �f�X�g���N�^
//============================
CFeed::~CFeed()
{

}
//============================
// ��������
//============================
CFeed* CFeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName)
{
	// �C���X�^���X����
	CFeed* pFeed = new CFeed;
	if (pFeed == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pFeed->SetPos(pos);
	pFeed->SetRot(rot);
	pFeed->SetScale(scale);
	pFeed->SetFilePass(pModelName);
	pFeed->SetShadow(true);

	// ���������s��
	if (FAILED(pFeed->Init())) 	return nullptr;

	return pFeed;
}
//============================
// ����������
//============================
HRESULT CFeed::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	return S_OK;
}
//============================
// �I������
//============================
void CFeed::Uninit(void)
{
	// �e�N���X�̏I��
	CObjectX::Uninit();
}
//============================
// �X�V����
//============================
void CFeed::Update(void)
{
	// �e�N���X�̍X�V
	CObjectX::Uninit();
}
//============================
// �`�揈��
//===========================
void CFeed::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}