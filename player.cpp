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
#include "boxcollider.h"
#include "collisionbox.h"
#include "motion.h"

//**********************
// ���O���
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 4.5f;		 // 1�t���[���̈ړ���
	constexpr float NorRot = D3DX_PI * 2.0f; // ���K���l
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
m_pStateMachine(nullptr),
m_pBoxCollider(nullptr)
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

	// �R���C�_�[����
	m_pBoxCollider = CBoxCollider::Create(GetPos(), GetOldPos(), D3DXVECTOR3(50.0f,50.0f,50.0f));

	// ���[�V�����擾
	m_pMotion = CMoveCharactor::GetMotion();

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

	// �R���C�_�[�j��
	if (m_pBoxCollider)
	{
		delete m_pBoxCollider;
		m_pBoxCollider = nullptr;
	}

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

	// ���W�擾
	D3DXVECTOR3 pos = GetPos();

	// ���̓f�o�C�X�̃|�C���^�擾
	CInputKeyboard* pInput = CManager::GetInstance()->GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetInstance()->GetJoyPad();

	// nullptr����Ȃ��Ƃ�
	if (m_pStateMachine != nullptr)
	{
		// �X�e�[�g�X�V
		m_pStateMachine->Update();
	}

	// �ړ�����
	MoveKey(pInput,pJoyPad);
	MovePad(pJoyPad);

	// �R���C�_�[�̈ʒu�X�V
	m_pBoxCollider->SetPos(pos);

	// ���W�Z�b�g
	SetPos(pos);

	// �u���b�N�Ƃ̓����蔻��
	CollisionBlock(&pos);

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

	// �f�o�b�O�\��
	CDebugproc::Print("���[�V�����^�C�v [ %d ]", m_pMotion->GetMotionType());
	CDebugproc::Draw(0, 100);
}
//=========================================
// �L�[���͈ړ��֐�
//=========================================
void CPlayer::MoveKey(CInputKeyboard* pInput,CJoyPad * pPad)
{
	// �p�b�h����������
	if (pPad->GetLeftStick()) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// �擾�֌W
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 rotDest = GetRotDest();

	if (pInput->GetPress(DIK_A) || pPad->GetPress(CJoyPad::JOYKEY_LEFT))
	{// A�L�[
		if (pInput->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
		{// ���΂ߏ�

			move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(MOTION_MOVE);

		}
		else if (pInput->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// �E�΂߉�

			move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(MOTION_MOVE);
		}
		else
		{// �P��
			move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(MOTION_MOVE);
		}

		// �p�x�̐��K��
		if (rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			rot.y -= PLAYERINFO::NorRot;
		}
	}
	else if (pInput->GetPress(DIK_D) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT))
	{// D�L�[��������

		if (pInput->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
		{// W�L�[��������
			move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(MOTION_MOVE);

		}
		else if (pInput->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
		{// S�L�[��������
			move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(MOTION_MOVE);
		}
		else
		{// D�L�[�̂݉�����
			move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(MOTION_MOVE);
		}

		// �p�x�̐��K��
		if (rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			rot.y -= PLAYERINFO::NorRot;
		}
	}
	else if (pInput->GetPress(DIK_W) || pPad->GetPress(CJoyPad::JOYKEY_UP))
	{// W�L�[��������

		move.x += sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		move.z += cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		rotDest.y = pCamera->GetRot().y - D3DX_PI;

		// ���[�V�����ύX
		m_pMotion->SetMotion(MOTION_MOVE);
	
		// �p�x�𐳋K��
		if (rot.y < -D3DX_PI)
		{// D3DX_PI��菬�����Ȃ�����
			rot.y += PLAYERINFO::NorRot;
		}

	}
	else if (pInput->GetPress(DIK_S) || pPad->GetPress(CJoyPad::JOYKEY_DOWN))
	{// S�L�[��������

		move.x -= sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		move.z -= cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		rotDest.y = pCamera->GetRot().y;

		// ���[�V�����ύX
		m_pMotion->SetMotion(MOTION_MOVE);

		// �p�x�̐��K��
		if (rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			rot.y -= PLAYERINFO::NorRot;
		}
	}
	else
	{
		if (m_pMotion->GetMotionType() == MOTION_MOVE)
		{
			//�@���[�V�����؂�ւ�
			m_pMotion->SetMotion(MOTION_NEUTRAL, true, 10, false);
		}
	}

	if (rotDest.y - rot.y > D3DX_PI)
	{// ����]
		// �p�x
		rot.y = rot.y + PLAYERINFO::NorRot;
	}
	else if (rot.y - rotDest.y > D3DX_PI)
	{// �E��]
		// �p�x
		rot.y = rot.y - PLAYERINFO::NorRot;
	}

	// ���݂̊p�x
	rot.y += (rotDest.y - rot.y) * 0.25f;

	// �L�����N�^�[�ɓK�p����
	SetRot(rot);
	SetRotDest(rotDest);
	SetMove(move);
}
//=========================================
// �W���C�p�b�h���͈ړ��֐�
//=========================================
void CPlayer::MovePad(CJoyPad* pPad)
{
	// �p�b�h�擾
	XINPUT_STATE* pStick;
	pStick = pPad->GetStickAngle();

	// �J�����擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	if (pCamera == nullptr) return;

	// �L�����N�^�[���̎擾
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rotDest = GetRotDest();

	// �t���O
	bool isMoving = false;

	// �擾�ł�����
	if (pPad->GetLeftStick())
	{
		// ���X�e�B�b�N�̊p�x
		float LStickAngleY = pStick->Gamepad.sThumbLY;
		float LStickAngleX = pStick->Gamepad.sThumbLX;

		// �f�b�h�]�[����ݒ�
		float DeadZone = 32767.0f * 0.25f;
		float fMag = sqrtf((LStickAngleX * LStickAngleX) + (LStickAngleY * LStickAngleY));

		if (fMag > DeadZone)
		{
			// ���K��
			float normalizeX = (LStickAngleX / fMag);
			float normalizeY = (LStickAngleY / fMag);

			// �ړ���
			float MoveX = normalizeX * cosf(-pCamera->GetRot().y) - normalizeY * sinf(-pCamera->GetRot().y);
			float MoveZ = normalizeX * sinf(-pCamera->GetRot().y) + normalizeY * cosf(-pCamera->GetRot().y);

			// �v���C���[�̈ړ��ʂ�ݒ�
			move.x += MoveX * PLAYERINFO::MOVE;
			move.z += MoveZ * PLAYERINFO::MOVE;
			rotDest.y = atan2f(-MoveX, -MoveZ);
			isMoving = true;
		}
	}

	if (isMoving)
	{
		if (m_pMotion->GetMotionType() != MOTION_MOVE)
		{
			m_pMotion->SetMotion(MOTION_MOVE);
		}
	}

	// �K�p
	SetMove(move);
	SetRotDest(rotDest);
}

//=========================================
// �u���b�N�Ƃ̓����蔻��
//=========================================
bool CPlayer::CollisionBlock(D3DXVECTOR3* pos)
{
	// ������Ȃ��Ƃ�
	return false;
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
