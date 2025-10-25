//=============================================
//
// �Q�[�W�֌W�̃N���X���� [ gage.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gauge.h"
#include "template.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CGauge::CGauge(int nPriority) : CObject2D(nPriority)
{
	// ����
}
//===============================
// �f�X�g���N�^
//===============================
CGauge::~CGauge()
{
	// ����
}
//===============================
// ��������
//===============================
CGauge* CGauge::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CGauge* pGage = new CGauge;
	if (pGage == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pGage->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pGage->SetPos(pos);
	pGage->SetSize(fWidth, fHeight);

	// �|�C���^��Ԃ�
	return pGage;
}
//===============================
// ����������
//===============================
HRESULT CGauge::Init(void)
{
	// �e�N���X�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CGauge::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//===============================
// �X�V����
//===============================
void CGauge::Update(void)
{
	// �e�N���X�̍X�V
	CObject2D::Update();
}
//===============================
// �`�揈��
//===============================
void CGauge::Draw(void)
{
	// �e�N���X�̕`��
	CObject2D::Draw();
}
//==========================================
// int�^�p�����[�^�[�̃Q�[�W�ݒ菈���֐�
//==========================================
void CGauge::SetLengthParamInt(const int nMax, const int nCurrent, const float fMaxWidth)
{
	// �ő�HP��0�ȉ��̎�
	if (nMax <= 0) return;

	// �^����ꂽ�����̒l�̊������v�Z
	float fRate = static_cast<float>(nCurrent) / static_cast<float>(nMax);
	fRate = Clump(fRate, 0.0f, 1.0f); 	// �N�����v����

	// �Q�[�W�̒����ɃZ�b�g����
	SetSize(fMaxWidth * fRate, GetHeight());
}
//==========================================
// float�^�p�����[�^�[�̃Q�[�W�ݒ菈���֐�
//==========================================
void CGauge::SetLengthParamFloat(const float fMax, const float fCurrent, const float fMaxWidth)
{
	// 0.0f�ȉ��Ȃ�
	if (fMax <= 0.0f) return;

	// �^����ꂽ�����̒l�̊������v�Z
	float fRate = fCurrent / fMax;
	fRate = Clump(fRate, 0.0f, 1.0f); 	// �N�����v����

	// �Q�[�W�̒����ɃZ�b�g����
	SetSize(fMaxWidth * fRate, GetHeight());
}