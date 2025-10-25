//=============================================
//
// �`���[�g���A���Ǘ����� [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �O���錾
//******************************
class CTutorialUi;

//********************************
// �`���[�g���A���Ǘ��N���X���`
//********************************
class CTutorialManager
{
public:
	//***********************
	// �������^�X�N�̎��
	//***********************
	enum TASKTYPE
	{
		TASKTYPE_MOVE,
		TASKTYPE_ATTACK,
		TASKTYPE_JUMP,
		TASKTYPE_JUMPATTACK,
		TASKTYPE_AVOID,
		TASKTYPE_LASER,
		TASKTYPE_LASERACTION,
		TASKTYPE_FREE,
		TASKTYPE_MAX
	};

	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // �`���[�g���A��ui�N���X�̃|�C���^
	TASKTYPE m_Tasktype;	// ���

	bool m_isFreeDone;
	bool m_isCreate;
};