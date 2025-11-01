//============================================
//
// ��ԊǗ���ꏈ�� [ state.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//*********************************
// �X�e�[�g�x�[�X�N���X
//*********************************
class CStateBase
{
public:

	CStateBase();
	virtual ~CStateBase();

	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnExit() {}

	virtual int GetID() const = 0;
};