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
// �C���X�^���X�擾
//========================
CGameManager* CGameManager::GetInstance(void)
{
	static CGameManager pInstance;
	return &pInstance;
}
//========================
// �R���X�g���N�^
//========================
CGameManager::CGameManager() : m_pBlockManager(nullptr)
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

	m_pBlockManager = std::make_unique<CBlockManager>();
	m_pBlockManager->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �I������
//========================
void CGameManager::Uninit(void)
{
	// �j��
	m_pBlockManager.reset();
}
//========================
// �X�V����
//========================
void CGameManager::Update(void)
{

#ifdef _DEBUG
	// ��ʑJ��
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
