//=====================================
//
// UI���� [ ui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "easing.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CUi::CUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_isFlash = false;
	m_nFlashFrame = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CUi::~CUi()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CUi::Init(void)
{
	// �I�u�W�F�N�g�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CUi::Uninit(void)
{
	// �I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}
//===============================
// �X�V����
//===============================
void CUi::Update(void)
{
	// �_�ŗL����
	if (m_isFlash)
	{
		// �_�ŏ���
		SetFlash(NULL, m_nFlashFrame, COLOR_WHITE);
	}

	// �e�N���X�X�V
	CObject2D::Update();
}
//===============================
// �`�揈��
//===============================
void CUi::Draw(void)
{
	// �I�u�W�F�N�g�̕`��
	CObject2D::Draw();
}
//===============================
// ��������
//===============================
CUi* CUi::Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight, const char* Filename, bool isUse)
{
	// �C���X�^���X����
	CUi* pUi = new CUi;

	// null�Ȃ�
	if (pUi == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pUi->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pUi->SetPos(pos);
	pUi->SetSize(fWidth, fHeight);
	pUi->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pUi->SetTexture(Filename);
	pUi->m_nFlashFrame = nFlashFrame;
	pUi->m_isFlash = isUse;

	// �������ꂽ�|�C���^��Ԃ�
	return pUi;
}