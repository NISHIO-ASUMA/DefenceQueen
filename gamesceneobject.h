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
#include <memory>

//*************************
// �O���錾
//*************************
class CBlockManager;

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
	CBlockManager* GetBlockManager(void) { return m_pBlocks.get(); }

private:

	std::unique_ptr<CBlockManager>m_pBlocks; // �u���b�N�}�l�[�W���[�N���X�̃|�C���^
	static CScore* m_pScore; // �X�R�A�N���X�̃|�C���^
};