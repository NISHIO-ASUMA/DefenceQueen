//=======================================
//
// �u���b�N�Ǘ����� [ blockmanager.h ]
// Author: Asuma Nishio
//
//=======================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "block.h"
#include <vector>

//**********************
// �O���錾
//**********************
class CBoxCollider;

//**********************************
// �u���b�N�ꊇ�Ǘ��N���X���`
//**********************************
class CBlockManager
{
public:

	CBlockManager();
	~CBlockManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	HRESULT Load();

	static int GetAll(void) { return static_cast<int>(m_pBlocks.size()); }
	static CBlock* GetBlock(const int nIdx) { return m_pBlocks[nIdx]; }
	static CBlock* CreateManager(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName);

private:

	static std::vector<CBlock*>m_pBlocks; // �z�u����u���b�N�̓��I�z��

};