//=============================================================================
//
// �e�V�[�����ƂɎg��Manager�N���X���ꊇ�Ǘ����鏈�� [ scenemanagement.cpp ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "scenemanagement.h"
#include "scenemanagebase.h"
#include "gamemanager.h"
#include "titlemanager.h"
#include "resultmanager.h"
#include "tutorialmanager.h"
#include "rankingmanager.h"

//==================================
// �R���X�g���N�^
//==================================
CSceneManagement::CSceneManagement() : m_pCurrentManager(nullptr),m_CurrentScene(TYPE_TITLE)
{
	// �l�̃N���A
}
//==================================
// �f�X�g���N�^
//==================================
CSceneManagement::~CSceneManagement()
{
	// �I������
	Uninit();
}
//==================================
// ����������
//==================================
HRESULT CSceneManagement::Init(void)
{
	return S_OK;
}
//==================================
// �I������
//==================================
void CSceneManagement::Uninit(void)
{
	if (m_pCurrentManager)
	{
		m_pCurrentManager->Uninit();
		m_pCurrentManager.reset();
	}
}
//==================================
// �X�V����
//==================================
void CSceneManagement::Update(void)
{
	// ���݂̃V�[���ɉ������X�V
	if (m_pCurrentManager)
		m_pCurrentManager->Update();
}
//==================================
// �`�揈��
//==================================
void CSceneManagement::Draw(void)
{
	// �`��
	if (m_pCurrentManager)
		m_pCurrentManager->Draw();
}
//==================================
// �e�V�[���ɐ؂�ւ�����
//==================================
void CSceneManagement::ChangeScene(TYPE NewType)
{
	// �e�V�[���̏I������
	if (m_pCurrentManager)
	{
		m_pCurrentManager->Uninit();
		m_pCurrentManager.reset();
	}

	switch (NewType)
	{
	case TYPE_TITLE:
		m_pCurrentManager = std::make_unique<CTitleManager>();
		break;

	case TYPE_TUTORIAL:
		m_pCurrentManager = std::make_unique<CTutorialManager>();
		break;

	case TYPE_GAME:
		m_pCurrentManager = std::make_unique<CGameManager>();
		break;

	case TYPE_RESULT:
		m_pCurrentManager = std::make_unique<CResultManager>();
		break;

	case TYPE_RANKING:
		m_pCurrentManager = std::make_unique<CRankingManager>();
		break;
	}

	// �V�����}�l�[�W���[��������
	if (m_pCurrentManager)
	{
		m_pCurrentManager->Init();
		m_CurrentScene = NewType;
	}
}