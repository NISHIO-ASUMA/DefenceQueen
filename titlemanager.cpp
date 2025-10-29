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

//============================
// �R���X�g���N�^
//============================
CTitleManager::CTitleManager() : 
m_pUi(nullptr),
m_isFirstuiCreate(false),
m_nIdx(NULL)
{
	// �l�̃N���A
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
	// ����UI����
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 250.0f, 60.0f, "Enterkey.png", true);

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();
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

	// �t�F�[�h�擾
	CFade* pFade = CManager::GetInstance()->GetFade();
	if (pFade == nullptr) return;

	// �L�[���͎� ���� ui����������Ă��Ȃ�������
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)))
	{
		pFade->SetFade(std::make_unique<CGame>());	// �Q�[���V�[���ɑJ��
		return;
	}
}
//=============================
// �`�揈��
//=============================
void CTitleManager::Draw(void)
{
}
