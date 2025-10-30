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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �C���X�^���X�擾
	static CTutorialManager* GetInstance(void)
	{
		// �������ꂽ�C���X�^���X
		static CTutorialManager pTutoManager;
		return &pTutoManager;
	}

private:

	CTutorialManager();
	~CTutorialManager();

	CTutorialUi* m_pTutoui; // �`���[�g���A��ui�N���X�̃|�C���^
};