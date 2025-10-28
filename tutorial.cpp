//=====================================
//
// �`���[�g���A������ [ tutorial.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "tutorial.h"
#include "tutorialmanager.h"
#include "manager.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include <memory>

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL), m_pTutoManager(nullptr)
{
	// �l�̃N���A
}
//===============================
// �f�X�g���N�^
//===============================
CTutorial::~CTutorial()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CTutorial::Init(void)
{
	// �}�l�[�W���[�̃C���X�^���X����
	m_pTutoManager = std::make_unique<CTutorialManager>();
	if (m_pTutoManager != nullptr) m_pTutoManager->Init();

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->Play(CSound::SOUND_LABEL_TUTORIALBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CTutorial::Uninit(void)
{
	// �j��
	m_pTutoManager.reset();
}
//===============================
// �X�V����
//===============================
void CTutorial::Update(void)
{
	// �|�C���^�����݂���Ȃ�
	if (m_pTutoManager != nullptr)
	{
		// �}�l�[�W���[�̍X�V����
		m_pTutoManager->Update();
	}

	// �L�[���͂őJ��
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->SetFade(std::make_unique <CGame>());
	}
}
//===============================
// �`�揈��
//===============================
void CTutorial::Draw(void)
{
	// ����
}