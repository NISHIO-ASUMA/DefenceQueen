//=============================================
//
// �G�̑ҋ@��ԊǗ����� [ enemystateneutral.h ]
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

//**********************
// �ҋ@��Ԃ̃N���X
//**********************
class CEnemyStateNeutral : public CEnemyStateBase
{
public:

	CEnemyStateNeutral();
	~CEnemyStateNeutral();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};

