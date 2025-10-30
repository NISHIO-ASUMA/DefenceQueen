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
#include "ui.h"
#include "ranking.h"
#include "fade.h"
#include <fstream>

//**************************
// �萔�錾
//**************************
namespace RESULTINFO
{
	constexpr int BOSS_SCOREIDX = 0; // �{�X�X�R�A�̃C���f�b�N�X
	constexpr int TIME_SCOREIDX = 1; // �^�C���X�R�A�̃C���f�b�N�X
	constexpr int LAST_SCOREIDX = 2; // �ŏI�X�R�A�̃C���f�b�N�X
};

//=================================
// �R���X�g���N�^
//=================================
CResultManager::CResultManager()
{
	// �l�̃N���A
	m_isKeyDown = false;
	m_nGameScore = NULL;
	m_nLastTime = NULL;

	for (int nCnt = 0; nCnt < SCORELISTNUM; nCnt++)
	{
		m_pResultScore[nCnt] = nullptr;
	}
}
//=================================
// �f�X�g���N�^
//=================================
CResultManager::~CResultManager()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CResultManager::Init(void)
{	
	// UI����
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "resultback.jpg", false);

	// �f�[�^�̓ǂݍ���
	// Load();

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();

	// null��������
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

	// �J�������擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	// �擾���s��
	if (pCamera == nullptr) return;

	// ����L�[�������ꂽ
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)))
	{
		// �|�C���^�擾
		CFade* pFade = CManager::GetInstance()->GetFade();

		// null����Ȃ��Ƃ�
		if (pFade != nullptr)
		{
			// �t���O�L����
			m_isKeyDown = true;

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
	m_nLastTime = NULL;
}
//=================================
// �C���X�^���X�擾
//=================================
CResultManager* CResultManager::GetInstance(void)
{
	static CResultManager pResultManager;
	return &pResultManager;
}