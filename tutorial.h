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
#include <memory>

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

private:
	std::unique_ptr<CTutorialManager>m_pTutoManager; // �}�l�[�W���[�N���X�̃|�C���^
};
