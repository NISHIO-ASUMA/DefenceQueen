//============================================
//
// ��ԊǗ����� [ statemachine.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "statemachine.h"
#include "state.h"

//==================================
// �R���X�g���N�^
//==================================
CStateMachine::CStateMachine() : m_pNowState(nullptr)
{
	// �l�̃N���A
}
//==================================
// �f�X�g���N�^
//==================================
CStateMachine::~CStateMachine()
{
	OnExit();
}
//==================================
// �X�V����
//==================================
void CStateMachine::Update(void)
{
	// nullptr����Ȃ�������
	if (m_pNowState != nullptr)
	{
		// �X�V�J�n
		m_pNowState->OnUpdate();
	}
}
//==================================
// �ύX����
//==================================
void CStateMachine::ChangeState(CStateBase* pNewState)
{
	// �|�C���^�����݂���Ƃ�
	if (m_pNowState != nullptr && pNewState != nullptr)
	{
		// ID �������Ȃ�
		if (m_pNowState->GetID() == pNewState->GetID())
		{
			delete pNewState;

			// �����ŏ�����Ԃ�
			return;
		}
	}

	// ���łɃX�e�[�g���Z�b�g����Ă���I������
	if (m_pNowState != nullptr)
	{
		// �I��
		m_pNowState->OnExit();

		// �|�C���^�̔j��
		delete m_pNowState;

		// nullptr�ɏ���������
		m_pNowState = nullptr;
	}

	// �V�����X�e�[�g���Z�b�g����
	m_pNowState = pNewState;

	// �V�����X�e�[�g���J�n����
	m_pNowState->OnStart();
}
//==================================
// �I������
//==================================
void CStateMachine::OnExit()
{
	// ���łɃX�e�[�g���Z�b�g����Ă���I������
	if (m_pNowState != nullptr)
	{
		// �j��
		delete m_pNowState;

		// null������
		m_pNowState = nullptr;
	}
}
//==================================
// ���ݏ�Ԃ��擾
//==================================
int CStateMachine::GetNowStateID()
{
	if (m_pNowState)
		return m_pNowState->GetID(); // ID��Ԃ�

	return 0; // �j���[�g����
}