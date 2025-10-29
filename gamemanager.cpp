//==========================================
//
// �Q�[���Ǘ����� [ gamemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "gamemanager.h"
#include "manager.h"
#include "debugproc.h"
#include "result.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "blockmanager.h"

//========================
// �R���X�g���N�^
//========================
CGameManager::CGameManager()
{
	// �l�̃N���A
}
//========================
// �f�X�g���N�^
//========================
CGameManager::~CGameManager()
{
	// �I������
	Uninit();
}
//========================
// ����������
//========================
HRESULT CGameManager::Init(void)
{
	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	m_pBlock = new CBlockManager;
	m_pBlock->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �I������
//========================
void CGameManager::Uninit(void)
{
	// �j��
	if (m_pBlock)
	{
		delete m_pBlock;
		m_pBlock = nullptr;
	}
}
//========================
// �X�V����
//========================
void CGameManager::Update(void)
{
#ifdef _DEBUG
	//
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_2))
	{
		// �J�ڍX�V
		CManager::GetInstance()->GetFade()->SetFade(std::make_unique<CResult>());

		return;
	}
#endif
}
//========================
// �`�揈��
//========================
void CGameManager::Draw(void)
{

}
