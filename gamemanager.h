//==========================================
//
// �Q�[���i�s�Ǘ����� [ gamemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include <memory>

//*****************************
// �O���錾
//*****************************
class CStateMachine;
class CGameStateBase;
class CGame;

//*****************************
// �Q�[���i�s�Ǘ��N���X���`
//*****************************
class CGameManager
{
public:

	CGameManager();
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
};

