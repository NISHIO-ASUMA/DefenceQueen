//============================================
//
// �������U���g�V�[������ [ loseresult.h ]
// Author: Asuma Nishio
// 
//============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "scene.h"

//********************************
// �������U���g�V�[���N���X���`
//********************************
class CLoseResult : public CScene
{
public:
	CLoseResult();
	~CLoseResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};
