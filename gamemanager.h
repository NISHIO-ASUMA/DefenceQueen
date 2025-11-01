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
class CGameSceneObject;

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

	static CGameManager* GetInstance(void);

	CGameSceneObject* GetGameObj(void) { return m_pGameObj.get(); }

private:

	CGameManager();

	std::unique_ptr<CGameSceneObject>m_pGameObj;		// �Q�[���I�u�W�F�N�g�Ǘ��N���X
};