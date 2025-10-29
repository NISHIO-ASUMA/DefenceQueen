//=============================================================================
//
// �e�V�[�����ƂɎg��Manager�N���X���ꊇ�Ǘ����鏈�� [ scenemanagement.h ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include <memory>

//**********************
// �O���錾
//**********************
class CSceneManageBase;
class CTitleManager;
class CGameManager;
class CTutorialManager;
class CResultManager;
class CRankingManager;

//**********************************************
// �e�V�[���̃}�l�[�W���[���Ǘ�����N���X���`
//**********************************************
class CSceneManagement
{
public:

	//***********************
	// �g�p�V�[���̎��
	//***********************
	enum TYPE
	{
		TYPE_NONE,
		TYPE_TITLE,
		TYPE_TUTORIAL,
		TYPE_GAME,
		TYPE_RESULT,
		TYPE_RANKING,
		TYPE_MAX
	};

	CSceneManagement();
	~CSceneManagement();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// �X�V����N���X��؂�ւ��鏈��
	/// </summary>
	/// <param name="NewType">�ύX��̎��</param>
	void ChangeScene(TYPE NewType);

	CSceneManageBase* GetManagerBase(void) { return m_pCurrentManager.get(); }

private:
	TYPE m_CurrentScene;								 // ���݂̎g�p�V�[��
	std::unique_ptr<CSceneManageBase> m_pCurrentManager; // ���݂̃}�l�[�W���[�N���X
};