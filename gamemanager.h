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
// �O���錾
//*****************************
class CBlockManager;

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include <memory>

//*****************************
// �Q�[���i�s�Ǘ��N���X���`
//*****************************
class CGameManager
{
public:
	
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CBlockManager* GetBlockManager(void) { return m_pBlockManager.get(); }

	static CGameManager* GetInstance(void);

private:

	CGameManager();

	std::unique_ptr<CBlockManager>m_pBlockManager;		// �u���b�N�}�l�[�W���[�̃|�C���^
};