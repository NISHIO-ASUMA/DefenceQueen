//====================================
//
// ���U���g�V�[������ [ result.h ]
// Author: Asuma Nishio
// 
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "scene.h"

//**************************
// �O���錾
//**************************
class CResultManager;

//*****************************
// ���U���g�V�[���N���X���`
//*****************************
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult* Create(void);

private:
	CResultManager* m_pResultManager;	// �}�l�[�W���[�N���X�|�C���^
};