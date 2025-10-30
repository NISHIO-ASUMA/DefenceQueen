//===============================================
//
// �Q�[����ԊǗ����� [ gamestate.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gamestate.h"
#include "gamesceneobject.h"
#include "fade.h"
#include "result.h"
#include "game.h"
#include "manager.h"

//**********************
// �萔���O���
//**********************
namespace GAMESTATE
{
	constexpr int STATECOUNT = 30; // ��ʐ؂�ւ���܂ł̃J�E���g
};

//===============================
// �R���X�g���N�^
//===============================
CGameState::CGameState() : m_pGame(nullptr),
m_Progress(PROGRESS_NONE),
m_nCount(NULL)
{
	// �l�̃N���A
}
//===============================
// �f�X�g���N�^
//===============================
CGameState::~CGameState()
{
	// ����
}
//===============================
// ��ԊJ�n�֐�
//===============================
void CGameState::OnStart()
{
	// ������Ԃ��Z�b�g����
	m_Progress = PROGRESS_NORMAL;
}
//===============================
// ��ԍX�V�֐�
//===============================
void CGameState::OnUpdate()
{
	// �|�C���^������������
	if (m_pGame == nullptr) return;

	// �I����ԂȂ�X�V���Ȃ�
	if (m_Progress == PROGRESS_END) return;

	// �t�F�[�h�擾
	auto pFade = CManager::GetInstance()->GetFade();
	if (pFade == nullptr) return;

	// �V�[���I�u�W�F�N�g�擾
	auto GameSceneObject = m_pGame->GetGameObject();
	if (GameSceneObject == nullptr) return;

	switch (m_Progress)
	{
	case CGameState::PROGRESS_NONE: // �����Ȃ�
		break;

	case CGameState::PROGRESS_NORMAL: // �i�s�𑱂���
		break;

	case CGameState::PROGRESS_END: // �I����,��ʑJ��

		// �J�E���g�����Z
		m_nCount++;

		if (m_nCount >= GAMESTATE::STATECOUNT)
		{
			// �J�E���^�[��������
			m_nCount = NULL;

			// 1�b�o��
			m_Progress = PROGRESS_NONE; // �������Ă��Ȃ����

			// �t�F�[�h���擾�ł�����
			if (pFade != nullptr)
			{
				// ���U���g�V�[���ɑJ��
				pFade->SetFade(std::make_unique<CResult>());
			}
		}
		break;

	default:
		break;
	}
}
//===============================
// ��ԏI���֐�
//===============================
void CGameState::OnExit()
{
	// �|�C���^��null������
	m_pGame = nullptr;
}