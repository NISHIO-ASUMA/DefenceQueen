//=============================================
//
// �G�̈ړ���ԏ��� [ enemystatemove.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "enemystatebase.h"

//**************************
// �ړ���ԊǗ��N���X���`
//**************************
class CEnemyStateMove : public CEnemyStateBase
{
public:
	
	CEnemyStateMove();
	~CEnemyStateMove();

	void OnStart(void) override;
	void OnUpdate(void) override;
	void OnExit(void) override;

private:

};

