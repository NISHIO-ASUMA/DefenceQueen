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

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "scenemanagebase.h"

//*****************************
// �O���錾
//*****************************
class CStateMachine;
class CGameStateBase;
class CGame;
class CBlockManager;

//*****************************
// �Q�[���i�s�Ǘ��N���X���`
//*****************************
class CGameManager : public CSceneManageBase
{
public:

	CGameManager();
	~CGameManager();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void) override;

	CBlockManager* GetBlockM(void) { return m_pBlock; }
private:
	CBlockManager* m_pBlock;
};