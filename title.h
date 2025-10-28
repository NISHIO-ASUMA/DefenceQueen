//====================================
//
// �^�C�g������ [ title.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "scene.h"
#include <memory>

//**************************
// �O���錾
//**************************
class CTitleManager;

//****************************
// �^�C�g���N���X���`
//****************************
class CTitle :public CScene
{
public:

	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	std::unique_ptr<CTitleManager>m_pTitleManager; // �}�l�[�W���[�N���X�|�C���^
};
