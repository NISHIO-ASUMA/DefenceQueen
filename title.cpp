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
	// �l�̃N���A
	m_pTitleManager = nullptr;
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
	m_pTitleManager = std::make_unique<CTitleManager>();
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
	// �j��
	m_pTitleManager.reset();
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
}
//=====================================
// �`�揈��
//=====================================
void CTitle::Draw(void)
{
	// ����
}
