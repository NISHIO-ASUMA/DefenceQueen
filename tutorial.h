//=====================================
//
// �`���[�g���A������ [ tutorial.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "scene.h"

//**********************
// �O���錾
//**********************
class CTutorialManager;

//************************************
// �`���[�g���A���V�[���N���X���`
//************************************
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorial* Create(void);

private:
	CTutorialManager* m_pTutoManager; // �}�l�[�W���[�N���X�̃|�C���^
};
