//============================================
//
// �������U���g�V�[������ [ loseresult.cpp ]
// Author: Asuma Nishio
// 
//============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "loseresult.h"
#include "manager.h"
#include "ui.h"
#include "title.h"
#include "sound.h"
#include "fade.h"
#include "input.h"
#include <memory>

//===============================
// �R���X�g���N�^
//===============================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT)
{
	// �l�̃N���A
}
//===============================
// �f�X�g���N�^
//===============================
CLoseResult::~CLoseResult()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CLoseResult::Init(void)
{
	// UI����
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "LoseResult.jpg",false);

	// �T�E���h�擾
	CSound* pSound = CManager::GetInstance()->GetSound();
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->Play(CSound::SOUND_LABEL_LOSERESULTBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CLoseResult::Uninit(void)
{
	// ����
}
//===============================
// �X�V����
//===============================
void CLoseResult::Update(void)
{
	// �L�[���͂Ń^�C�g���ɖ߂�
	if ((CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CManager::GetInstance()->GetJoyPad()->JOYKEY_START)))
	{
		// �|�C���^�擾
		CFade* pFade = CManager::GetInstance()->GetFade();

		// null����Ȃ��Ƃ�
		if (pFade != nullptr)
		{
			// �V�[���J��
			pFade->SetFade(std::make_unique<CTitle>());
			return;
		}
	}
}
//===============================
// �`�揈��
//===============================
void CLoseResult::Draw(void)
{
	// ����
}