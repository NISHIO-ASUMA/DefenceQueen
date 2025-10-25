//====================================
//
// �^�C�g��ui���� [ titleui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "titleui.h"
#include "texture.h"
#include "manager.h"

//=========================
// �R���X�g���N�^
//=========================
CTitleUi::CTitleUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
}
//=========================
// �f�X�g���N�^
//=========================
CTitleUi::~CTitleUi()
{
	// ����
}
//=========================
// ����������
//=========================
HRESULT CTitleUi::Init(void)
{
	// 2D�I�u�W�F�N�g�̏���������
	CObject2D::Init();

	// ���_�^�C�v��ݒ�
	SetAnchor(ANCHORTYPE_CENTER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=========================
// �I������
//=========================
void CTitleUi::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}
//=========================
// �X�V����
//=========================
void CTitleUi::Update(void)
{
	// 2D�I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}
//=========================
// �`�揈��
//=========================
void CTitleUi::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}
//=========================
// ��������
//=========================
CTitleUi* CTitleUi::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType)
{
	// �C���X�^���X����
	CTitleUi* pTitleui = new CTitleUi;

	// null��������
	if (pTitleui == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTitleui->Init())) 
	{
		// null��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pTitleui->SetPos(pos);
	pTitleui->SetCol(col);
	pTitleui->SetSize(fWidth, fHeight);
	pTitleui->SetTexture(nType);

	// �������ꂽ�|�C���^��Ԃ�
	return pTitleui;
}
//=========================
// �e�N�X�`�����蓖�ď���
//=========================
void CTitleUi::SetTexture(int nType)
{
	// �t�@�C����������
	const char* szFileName = nullptr;

	switch (nType)
	{
	case MENU_GAME:				// �Q�[�����j���[
		szFileName = "titlemenu_001.png";
		break;

	case MENU_TUTORIAL:		// �`���[�g���A�����j���[
		szFileName = "titlemenu_002.png";
		break;

	case MENU_EXIT:			// �I�����j���[
		szFileName = "titlemenu_003.png";
		break;

	default:
		szFileName = nullptr;
		break;
	}

	// �t�@�C���������܂��Ă���ΐݒ�
	if (szFileName)
	{
		// �p�X�Z�b�g
		CObject2D::SetTexture(szFileName);
	}
	else
	{
		// ����
		CObject2D::SetTexture(nullptr);
	}
}
