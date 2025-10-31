//===================================================
//
// �j���[�g������ԊǗ����� [ playerstateneutral.h ]
// Author: Asuma Nishio
//
//===================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "playerstatebase.h"

//**********************
// �ҋ@��ԃN���X���`
//**********************
class CPlayerStateNeutral : public CPlayerStateBase
{
public:

	CPlayerStateNeutral();
	~CPlayerStateNeutral();

	void OnStart(void) override;
	void OnUpdate(void) override;
	void OnExit(void) override;

private:

};