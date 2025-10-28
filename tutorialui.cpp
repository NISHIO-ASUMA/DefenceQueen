//=============================================
//
// �`���[�g���A��UI���� [ tutorialui.cpp ]
// Author: Asuma Nishio
//
//=============================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "tutorialui.h"
#include "manager.h"

//==============================
// �R���X�g���N�^
//==============================
CTutorialUi::CTutorialUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_fAlpha = 1.0f;
}
//==============================
// �f�X�g���N�^
//==============================
CTutorialUi::~CTutorialUi()
{
	// �j��
	CObject2D::Uninit();
}
//==============================
// ��������
//==============================
CTutorialUi* CTutorialUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * pFileName,int nState)
{
	// �C���X�^���X����
	CTutorialUi* pTutoUi = new CTutorialUi;

	// �C���X�^���X�������s��
	if (pTutoUi == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTutoUi->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̊�{�ݒ�
	pTutoUi->SetPos(pos);
	pTutoUi->SetSize(fWidth, fHeight);
	pTutoUi->SetTexture(pFileName);
	pTutoUi->SetState(nState);

	// �������ꂽ�|�C���^��Ԃ�
	return pTutoUi;
}
//==============================
// ����������
//==============================
HRESULT CTutorialUi::Init(void)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	// ���_�����^�C�v��ݒ�
	SetAnchor(CObject2D::ANCHORTYPE_CENTER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CTutorialUi::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CTutorialUi::Update(void)
{
	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();
}
//==============================
// �`�揈��
//==============================
void CTutorialUi::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}
