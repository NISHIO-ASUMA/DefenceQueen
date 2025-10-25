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

//******************************
// ���O���
//******************************
namespace TUTORIAL_UIINFO
{
	constexpr float MOVEDOWNVALUE = 5.0f;		// �ړ����x
	constexpr float MAX_MOVEWIDTH = 1120.0f;	// �ő���W
}

//==============================
// �R���X�g���N�^
//==============================
CTutorialUi::CTutorialUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nState = STATE_AWAIT;
	m_fAlpha = 1.0f;
}
//==============================
// �f�X�g���N�^
//==============================
CTutorialUi::~CTutorialUi()
{
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
	// ���ݍ��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	//  ��ޕ���
	switch (m_nState)
	{
	case STATE_AWAIT:

		// ��ԕύX
		m_nState = STATE_MOVE;

		break;

	case STATE_MOVE:

		// �ړ��ʂ����Z
		NowPos.x -= TUTORIAL_UIINFO::MOVEDOWNVALUE;

		// ����ɒB������
		if (NowPos.x <= TUTORIAL_UIINFO::MAX_MOVEWIDTH)
		{
			// �����ݒ�
			NowPos.x = TUTORIAL_UIINFO::MAX_MOVEWIDTH;

			// ��ԕύX
			m_nState = STATE_STOP;
		}
		break;

	case STATE_STOP:
		break;

	case STATE_EXIT:
		// ���l������
		m_fAlpha -= 0.03f;

		if (m_fAlpha <= 0.0f)
		{
			m_fAlpha = 0.0f;
		}

		break;

	default:
		break;
	}

	// �I�u�W�F�N�g�̐ݒ�
	SetPos(NowPos);
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

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
//==============================
// �J���[������擾
//==============================
bool CTutorialUi::IsFinished() const
{
	return (m_fAlpha <= 0.0f);
}
