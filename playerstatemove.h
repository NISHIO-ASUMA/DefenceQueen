//=============================================
//
// �ړ���ԊǗ����� [ playerstatemove.h ]
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
#include "playerstatebase.h"

//***************************
// �ړ���ԊǗ��N���X���`
//***************************
class CPlayerStateMove : public CPlayerStateBase
{
public:

	CPlayerStateMove();
	~CPlayerStateMove();

	void OnStart(void);
	void OnUpdate(void);
	void OnExit(void);

private:

};