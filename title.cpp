//====================================
//
// �^�C�g������ [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
#include "titlemanager.h"
#include "input.h"

//=====================================
// �R���X�g���N�^
//=====================================
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{
	//����
}
//=====================================
// �f�X�g���N�^
//=====================================
CTitle::~CTitle()
{
	// ����
}
//=====================================
// ����������
//=====================================
HRESULT CTitle::Init(void)
{
	// �C���X�^���X����
	m_pTitleManager = new CTitleManager();

	// �������s��
	if (m_pTitleManager == nullptr) return E_FAIL;

	// �}�l�[�W���[�̏���������
	m_pTitleManager->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CTitle::Uninit(void)
{
	// null�`�F�b�N
	if (m_pTitleManager != nullptr)
	{
		// �I������
		m_pTitleManager->Uninit();

		// �j��
		delete m_pTitleManager;

		// nullptr����
		m_pTitleManager = nullptr;
	}
}
//=====================================
// �X�V����
//=====================================
void CTitle::Update(void)
{
	// null����Ȃ�������
	if (m_pTitleManager != nullptr)
	{
		// �}�l�[�W���[�̍X�V����
		m_pTitleManager->Update();
	}

	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// �R���g���[���[�擾
	if (CManager::GetInstance()->GetJoyPad()->GetTrigger(pJoyPad->JOYKEY_BACK))
	{
		PostQuitMessage(0);
		return;
	}
}
//=====================================
// �`�揈��
//=====================================
void CTitle::Draw(void)
{
	// ����
}
