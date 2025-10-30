//=====================================
//
// ���C���Q�[������ [ game.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "game.h"
#include "manager.h"
#include "debugproc.h"
#include "gamemanager.h"
#include "gamesceneobject.h"
#include "gamestate.h"
#include "input.h"

//**************************
// �ÓI�����o�ϐ��錾
//**************************
CPauseManager* CGame::m_pPausemanager = nullptr; // �|�[�Y�}�l�[�W���[�̃|�C���^

//==================================
// �R���X�g���N�^
//==================================
CGame::CGame() : CScene(CScene::MODE_GAME), m_pGameManager(nullptr)
{
	// �l�̃N���A
}
//==================================
// �f�X�g���N�^
//==================================
CGame::~CGame()
{
	// ����
}
//==================================
// ����������
//==================================
HRESULT CGame::Init(void)
{
	// �|�[�Y�}�l�[�W���[����
	m_pPausemanager = new CPauseManager;
	if (m_pPausemanager == nullptr) return E_FAIL;

	// �|�[�Y�}�l�[�W���[����������
	m_pPausemanager->Init();

	// �Q�[���}�l�[�W���[
	CGameManager::GetInstance()->Init();

	// �Q�[���I�u�W�F�N�g����
	m_pGameObject = std::make_unique<CGameSceneObject>();
	if (m_pGameObject == nullptr) return E_FAIL;

	// �Q�[���I�u�W�F�N�g����������
	m_pGameObject->Init();

	// �X�e�[�g����
	m_pState = new CGameState;
	if (m_pState == nullptr) return E_FAIL;

	// �J�n
	m_pState->SetGame(this);
	m_pState->OnStart();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==================================
// �I������
//==================================
void CGame::Uninit(void)
{
	CGameManager::GetInstance()->Uninit();

	// null�`�F�b�N
	if (m_pPausemanager != nullptr)
	{
		// �I������
		m_pPausemanager->Uninit();

		// �|�C���^�̔j��
		delete m_pPausemanager;

		// nullptr�ɂ���
		m_pPausemanager = nullptr;
	}

	// �j��
	// m_pGameManager.reset();

	// �j��
	m_pGameObject.reset();

	// null�`�F�b�N
	if (m_pState)
	{
		// �I������
		m_pState->OnExit();

		// �|�C���^�j��
		delete m_pState;

		// null������
		m_pState = nullptr;
	}
}
//==================================
// �X�V����
//==================================
void CGame::Update(void)
{	
	// �Q�[���i�s�Ǘ��̍X�V����
	m_pState->OnUpdate();

	// ��Ԏ擾
	auto State = m_pState->GetProgress();
	if (State == m_pState->PROGRESS_END) return;

	// �|�[�Y�̃L�[���͔���
	m_pPausemanager->SetEnablePause();
	
	// �|�[�Y�̍X�V����
	m_pPausemanager->Update();
	
	// false�̎��ɍX�V
	if (!m_pPausemanager->GetPause())
	{
		// �Q�[���}�l�[�W���[�X�V
		CGameManager::GetInstance()->Update();

		// �Q�[���I�u�W�F�N�g�X�V
		m_pGameObject->Update();
	}

#ifdef _DEBUG

	// ����
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_0))
	{
		// ��ԕύX
		m_pState->SetProgress(CGameState::PROGRESS_END);
	}

#endif // _DEBUG

}
//==================================
// �`�揈��
//==================================
void CGame::Draw(void)
{
	// ����
}