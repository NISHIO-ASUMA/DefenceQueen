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

//****************************
// �^�C�g���V�[���N���X���`
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

};