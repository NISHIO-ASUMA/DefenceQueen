//=================================================
//
// �`���[�g���A���Ǘ����� [ tutorialmanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "tutorialmanager.h"
#include "tutorialui.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "ui.h"

//==========================
// �R���X�g���N�^
//==========================
CTutorialManager::CTutorialManager() : m_pTutoui(nullptr)
{
	// �l�̃N���A
}
//==========================
// �f�X�g���N�^
//==========================
CTutorialManager::~CTutorialManager()
{
	// ����
}
//==========================
// ����������
//==========================
HRESULT CTutorialManager::Init(void)
{
	// ui����
	CUi::Create(D3DXVECTOR3(65.0f, 200.0f, 0.0f), 0, 60.0f, 30.0f, "bullet.png", false);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==========================
// �I������
//==========================
void CTutorialManager::Uninit(void)
{
	// �j��
}
//==========================
// �X�V����
//==========================
void CTutorialManager::Update(void)
{

}
//==========================
// �`�揈��
//==========================
void CTutorialManager::Draw(void)
{

}