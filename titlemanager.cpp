//==========================================
//
// �^�C�g���Ǘ����� [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "titlemanager.h"
#include "titleui.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "input.h"
#include "ui.h"
#include "sound.h"
#include "fade.h"
#include <memory>

//*************************
// ���O���
//*************************
namespace TITLEMANAGERINFO
{
	const D3DXVECTOR3 BacePos = { 210.0f, 520.0f, 0.0f };	// ����W
	constexpr int FLASHCOUNT = 10;	// �_�ŊԊu
};

//============================
// �R���X�g���N�^
//============================
CTitleManager::CTitleManager(bool isCreate) : m_isFirstuiCreate(isCreate)
{
	// �l�̃N���A
	m_nIdx = NULL;
	m_Info = {};

	for (int nCnt = 0; nCnt < TITLEINFO::TITLE_MENU; nCnt++)
	{
		m_pTitleui[nCnt] = nullptr;
	}
	m_pUi = nullptr;
	m_isuiCreate = false;
}
//============================
// �f�X�g���N�^
//============================
CTitleManager::~CTitleManager()
{
	// ����
}
//============================
// ����������
//============================
HRESULT CTitleManager::Init(void)
{	
	// ���̃V�[��������߂��Ă����Ƃ�
	if (!m_isFirstuiCreate) 
	{
		// �^�C�g����ui�𐶐�
		for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
		{
			// ���̊Ԋu���󂯂�
			D3DXVECTOR3 pos = TITLEMANAGERINFO::BacePos;

			pos.x += nCnt * m_Info.INTERVAL;

			// ui�𐶐�
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, m_Info.UIWIDTH, m_Info.UIHEIGHT, nCnt);
		}

		// �t���O��L����
		m_isuiCreate = true;
	}

	// ����UI����
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 250.0f, 60.0f, "Enterkey.png", true);

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	//	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CTitleManager::Uninit(void)
{
	// ����
}
//============================
// �X�V����
//============================
void CTitleManager::Update(void)
{
	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return;

	// �t�F�[�h�擾
	CFade* pFade = CManager::GetInstance()->GetFade();
	if (pFade == nullptr) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// �L�[���͎� ���� ui����������Ă��Ȃ�������
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)))
	{
		pFade->SetFade(std::make_unique<CGame>());	// �Q�[���V�[���ɑJ��

		return;
	}
}