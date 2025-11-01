//============================================
//
// ��ԊǗ����� [ statemachine.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �O���錾
//**********************
class CStateBase;

//*********************************
// �X�e�[�g�}�V���N���X���`
//*********************************
class CStateMachine
{
public:

	CStateMachine();
	~CStateMachine();

	void Update(void);
	void ChangeState(CStateBase* pNewState);
	void OnExit();

	int GetNowStateID();
	CStateBase* GetNowState() const { return m_pNowState; }

private:

	CStateBase* m_pNowState;	// ���N���X�̃X�e�[�g�|�C���^
};