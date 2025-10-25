//=========================================
//
// �v���C���[���� [ player.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "player.h"
#include "manager.h"
#include "texture.h"
#include "particle.h"
#include "shadow.h"
#include "meshimpact.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "parameter.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstate.h"
#include "effect.h"
#include "game.h"
#include "effectsmoke.h"
#include "sound.h"
#include "statemachine.h"

//**********************
// ���O���
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 0.015f;		 // 1�t���[���̈ړ���
	constexpr float JUMPVALUE = 18.3f;	 // �W�����v��
	constexpr float GRAVITY = 1.5f;		 // �d�͒l
	constexpr float HITRADIUS = 25.0f;	 // �����蔻��̔��a
	constexpr float AVOID_COOLTIME = 5.0f;	// ����̃N�[���^�C��
	constexpr float RADIUS = 550.0f;		// ���a
	constexpr int   NUMBER_MAIN = 0;	 // ���C������v���C���[�ԍ�
	constexpr int   NUMBER_SUB = 1;		 // ���g����v���C���[�ԍ�
	constexpr int   KeyRepeatCount = 15; // �L�[�̃��s�[�g�ő�J�E���g
};

//**********************
// �ÓI�����o�ϐ��錾
//**********************
bool CPlayer::m_isDeath = false;  // ���S�t���O

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CPlayer::CPlayer(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr)
{
	// �l�̃N���A
}
//===============================
// �f�X�g���N�^
//===============================
CPlayer::~CPlayer()
{
	// ����
}
//===============================
// �v���C���[��������
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife, const char* pFilename)
{
	// �v���C���[�̃C���X�^���X����
	CPlayer* pPlayer = new CPlayer;
	if (pPlayer == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	// �|�C���^����
	pPlayer->m_pParameter = std::make_unique<CParameter>();

	// null�`�F�b�N
	if (pPlayer->m_pParameter != nullptr)
	{
		// �̗̓p�����[�^�[��ݒ�
		pPlayer->m_pParameter->SetHp(nLife);
		pPlayer->m_pParameter->SetMaxHp(nLife);
	}
	
	// �v���C���[����������
	if (FAILED(pPlayer->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}
//===============================
// �v���C���[����������
//===============================
HRESULT CPlayer::Init(void)
{
	// �L�����N�^�\�̏�����
	CMoveCharactor::Init();

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(CObject::TYPE_PLAYER);

	// ���[�V�����Z�b�g
	MotionLoad("data/MOTION/Player/Player100motion.txt", MOTION_MAX);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = std::make_unique<CStateMachine>();

	// ������Ԃ��Z�b�g
	ChangeState(new CPlayerStateNeutral,CPlayerStateBase::ID_NEUTRAL); 

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �v���C���[�I������
//===============================
void CPlayer::Uninit(void)
{
	// �p�����[�^�I������
	m_pParameter.reset();

	// �X�e�[�g�I������
	m_pStateMachine.reset();

	// �L�����N�^�[�̔j��
	CMoveCharactor::Uninit();
}
//============================================================
// �v���C���[�X�V����
//============================================================
void CPlayer::Update(void)
{
	// ����ł�Ȃ珈�����Ȃ�
	if (m_isDeath) return;

	// ���݃V�[���擾
	CScene::MODE nMode = CManager::GetInstance()->GetInstance()->GetScene();

	// ���̓f�o�C�X�̃|�C���^�擾
	CInputKeyboard* pInput = nullptr;
	CJoyPad* pJoyPad = nullptr;
	pInput = CManager::GetInstance()->GetInputKeyboard();
	pJoyPad = CManager::GetInstance()->GetJoyPad();

	// nullptr����Ȃ��Ƃ�
	if (m_pStateMachine != nullptr)
	{
		// �X�e�[�g�X�V
		m_pStateMachine->Update();
	}

	// �L�����N�^�[�̍X�V����
	CMoveCharactor::Update();
}
//===============================
// �v���C���[�`�揈��
//===============================
void CPlayer::Draw(void)
{
	// �L�����N�^�[�̕`�揈��
	CMoveCharactor::Draw();
}
//=========================================
// �X�e�[�g�ύX
//=========================================
void CPlayer::ChangeState(CPlayerStateBase* pNewState,int id)
{
	// �������g����
	pNewState->SetOwner(this);

	// �X�e�[�g�ύX
	m_pStateMachine->ChangeState(pNewState);
}
//===============================
// �L�[�������̓��͎擾
//===============================
bool CPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// �����ꂩ�̈ړ��L�[����
	return (pKeyInput->GetPress(DIK_A) || pKeyInput->GetPress(DIK_D));
}
//===============================
// �L�[�������̓��͎擾
//===============================
bool CPlayer::isMovePadButton(CJoyPad* pPad)
{
	// �����ꂩ�̈ړ��L�[����
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
