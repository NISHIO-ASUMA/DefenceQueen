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

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "scenemanagebase.h"

//******************************
// �O���錾
//******************************
class CTutorialUi;

//********************************
// �`���[�g���A���Ǘ��N���X���`
//********************************
class CTutorialManager : public CSceneManageBase
{
public:

	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	CTutorialUi* m_pTutoui; // �`���[�g���A��ui�N���X�̃|�C���^
};