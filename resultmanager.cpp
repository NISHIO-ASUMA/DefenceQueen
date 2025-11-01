//==============================================
//
// ���U���g�V�[���Ǘ����� [ resultmanager.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "resultmanager.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "ranking.h"
#include "fade.h"
#include <fstream>

//=================================
// �R���X�g���N�^
//=================================
CResultManager::CResultManager() : m_nGameScore(NULL)
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CResultManager::~CResultManager()
{
	// ����
}
//=================================
// �C���X�^���X�擾
//=================================
CResultManager* CResultManager::GetInstance(void)
{
	static CResultManager pResultManager;
	return &pResultManager;
}
//=================================
// ����������
//=================================
HRESULT CResultManager::Init(void)
{	
	// �f�[�^�̓ǂݍ���
	Load();

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->Play(CSound::SOUND_LABEL_RESULTBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CResultManager::Uninit(void)
{
	// null�`�F�b�N
}
//=================================
// �X�V����
//=================================
void CResultManager::Update(void)
{
	// ���̓f�o�C�X���擾
	CInputKeyboard* pInput = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJyoPad = CManager::GetInstance()->GetJoyPad();

	// �擾���s��
	if (pInput == nullptr) return;
	if (pJyoPad == nullptr) return;

	// ����L�[�������ꂽ
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)))
	{
		// �|�C���^�擾
		CFade* pFade = CManager::GetInstance()->GetFade();

		// null����Ȃ��Ƃ�
		if (pFade != nullptr)
		{
			// �V�[���J��
			pFade->SetFade(std::make_unique <CRanking>());

			return;
		}
	}
}
//=================================
// �`�揈��
//=================================
void CResultManager::Draw(void)
{

}
//=================================
// �ǂݍ��ݏ���
//=================================
void CResultManager::Load(void)
{
	// �ǂݎ�����l���i�[���郁���o�ϐ�
	m_nGameScore = NULL;
}