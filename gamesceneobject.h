//===============================================
//
// �Q�[���̃I�u�W�F�N�g�Ǘ����� [ gameobject.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "score.h"
#include "object.h"

//************************************************
// �Q�[���V�[���Ŏg���I�u�W�F�N�g�Ǘ��N���X���`
//************************************************
class CGameSceneObject
{
public:

	CGameSceneObject();
	~CGameSceneObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CScore* GetScore(void) { return m_pScore; } 

private:
	static CScore* m_pScore; // �X�R�A�N���X�̃|�C���^
};