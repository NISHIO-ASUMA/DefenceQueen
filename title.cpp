//====================================
//
// �^�C�g������ [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
#include "titlemanager.h"
#include "input.h"

//=====================================
// �R���X�g���N�^
//=====================================
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{
}
//=====================================
// �f�X�g���N�^
//=====================================
CTitle::~CTitle()
{
	// ����
}
//=====================================
// ����������
//=====================================
HRESULT CTitle::Init(void)
{
	// ����������
	CTitleManager::GetInstance()->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CTitle::Uninit(void)
{
	// �I������
	CTitleManager::GetInstance()->Uninit();
}
//=====================================
// �X�V����
//=====================================
void CTitle::Update(void)
{
	// �X�V����
	CTitleManager::GetInstance()->Update();
}
//=====================================
// �`�揈��
//=====================================
void CTitle::Draw(void)
{
	// �`�揈��
	CTitleManager::GetInstance()->Draw();
}
