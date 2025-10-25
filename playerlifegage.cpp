//============================================
//
// �v���C���[�̗͏��� [ playerlifegage.cpp ]
// Author: Asuma Nishio
//
//============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "playerlifegage.h"
#include "player.h"
#include "parameter.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"

//*************************
// �萔�錾
//*************************
namespace PLAYERLIFEINFO
{
	constexpr float GAGE_HEIGHT = 45.0f; // �Q�[�W�̍����̌Œ�
	constexpr float VALUELENGTH = 0.28f; // �����̔{��
	constexpr float SHAKEFLOAT = 25.0f; // �U�ꕝ�̏����l
	constexpr float DIGIT = 40.0f;		// �v�Z�ϐ�
	constexpr float RANDOMDIGIT = 100.0f; // �����_���̊���l
	constexpr int SHAKEVALUE = 40;	// �U���̒l
	constexpr int RANDOM_MAX = 400; // �ő�l
	constexpr int RANDOM_MIN = 100; // �ŏ��l
};

//========================
// �R���X�g���N�^
//========================
CPlayerLifeGage::CPlayerLifeGage(int nPriority) : CGage(nPriority)
{
	// �l�̃N���A
	m_pPlayer = nullptr;
	m_nLifeLength = NULL;
	m_gage = GAGE_FRAME;
	m_nMaxLifeLength = NULL;
	m_nMaxLife = NULL;
	m_isShake = false;
	m_nShakeTimer = NULL;
	m_fShakeAmplitude = NULL;
	m_fShakeOffset = NULL;
	m_basePos = VECTOR3_NULL;
}
//========================
// �f�X�g���N�^
//========================
CPlayerLifeGage::~CPlayerLifeGage()
{
	// ����
}
//========================
// ����������
//========================
HRESULT CPlayerLifeGage::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

#if 0
	// null��������
	if (m_pPlayer == nullptr)
	{
		// �v���C���[�擾
		m_pPlayer = CPlayer::GetIdxPlayer(0);
	}
#endif
	// �擾�ł�����
	if (m_pPlayer != nullptr)
	{
		// �p�����[�^�[�擾
		CParameter* pParam = m_pPlayer->GetParameter();

		// ���݂̗̑͂��擾����
		m_nMaxLifeLength = pParam->GetHp();

		// �ő�l��ۑ����Ă���
		m_nMaxLife = pParam->GetHp();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �I������
//========================
void CPlayerLifeGage::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//========================
// �X�V����
//========================
void CPlayerLifeGage::Update(void)
{
	// �p�����[�^�[�擾
	CParameter* pParam = m_pPlayer->GetParameter();

	// null����Ȃ� ���� ��ނ��o�[�̎�
	if (m_pPlayer != nullptr && m_gage == GAGE_BAR)
	{
		// ���݂̗̑͂��擾����
		m_nLifeLength = pParam->GetHp();

		// �Q�[�W�̒����ݒ�
		SetGageLength(m_nMaxLifeLength, m_nLifeLength, PLAYERLIFEINFO::VALUELENGTH, PLAYERLIFEINFO::GAGE_HEIGHT);
	}

	if (m_pPlayer != nullptr)
	{
#if 0
		// �_���[�W�𕉂����t���O���L����
		if (m_pPlayer->GetIsDamege() && !m_isShake)
		{
			// �U��ON
			m_isShake = true;

			// �t���[���U��
			m_nShakeTimer = PLAYERLIFEINFO::SHAKEVALUE;

			// �U�ꕝ�̏����l
			m_fShakeAmplitude = PLAYERLIFEINFO::SHAKEFLOAT;
		}

		if (m_isShake)
		{
			// �������v�Z
			float t = (PLAYERLIFEINFO::SHAKEVALUE - m_nShakeTimer) / PLAYERLIFEINFO::DIGIT;

			// �����ʂ��v�Z
			float decay = (1.0f - t);

			// �����_���l��ݒ�
			float randX = (rand() % PLAYERLIFEINFO::RANDOM_MAX - PLAYERLIFEINFO::RANDOM_MIN) / PLAYERLIFEINFO::RANDOMDIGIT;
			float randY = (rand() % PLAYERLIFEINFO::RANDOM_MAX - PLAYERLIFEINFO::RANDOM_MIN) / PLAYERLIFEINFO::RANDOMDIGIT;

			// ���W���v�Z
			float fOffsetX = randX * m_fShakeAmplitude * decay;
			float fOffsetY = randY * m_fShakeAmplitude * decay;

			// ���W�ɃZ�b�g
			SetPos(m_basePos + D3DXVECTOR3(fOffsetX, fOffsetY, 0.0f));

			// �U�����Ԃ����炷
			m_nShakeTimer--;

			if (m_nShakeTimer <= NULL)
			{
				// �t���O�𖳌���
				m_isShake = false;
				m_nShakeTimer = NULL;

				// ����𖳌���
				m_pPlayer->SetIsDamege(false);

				// ����W�֖߂�
				SetPos(m_basePos);
			}
		}
		else
		{
			// ����W�ɌŒ�
			SetPos(m_basePos);
		}

		// �e�N���X�̍X�V����
		CObject2D::Update();
#endif

	}
}
//========================
// �`�揈��
//========================
void CPlayerLifeGage::Draw(void)
{
	// �e�N���X�̕`��
	CObject2D::Draw();
}
//========================
// ��������
//========================
CPlayerLifeGage* CPlayerLifeGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype, const char* pTexName)
{
	// �C���X�^���X����
	CPlayerLifeGage* pLifeGage = new CPlayerLifeGage;

	// null��������
	if (pLifeGage == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pLifeGage->Init()))
	{
		// null��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pLifeGage->SetPos(pos);
	pLifeGage->m_basePos = pos;
	pLifeGage->SetSize(fWidth, fHeight);
	pLifeGage->SetGage(gagetype);
	pLifeGage->SetTexture(pTexName);
	pLifeGage->SetAnchor(ANCHORTYPE_LEFTSIDE);

	// �������ꂽ�|�C���^��Ԃ�
	return pLifeGage;
}
