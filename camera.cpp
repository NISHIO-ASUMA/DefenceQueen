//====================================
//
// �J�������� [ camera.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "gamemanager.h"
#include "template.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//**********************
// �萔�錾
//**********************
namespace CAMERAINFO
{
	constexpr float MAX_VIEWUP = 3.0f;			// �J�����̊p�x�����l
	constexpr float MAX_VIEWDOWN = 0.1f;		// �J�����̊p�x�����l
	constexpr float NorRot = D3DX_PI * 2.0f;	// ���K���l
	constexpr float CAMERABACKPOS = 450.0f;		// ����J����
	constexpr float SHAKEVALUE = 12.0f;			// �U���̒l
	constexpr float DIGITVALUE = 1.5f;		// ����l
	constexpr int RANDOMBASE = 2;			// �����_����l
}

//=================================
// �R���X�g���N�^
//=================================
CCamera::CCamera()
{
	// �l�̃N���A
	m_pCamera.mtxprojection = {};
	m_pCamera.mtxView = {};
	m_pCamera.posR = VECTOR3_NULL;
	m_pCamera.posV = VECTOR3_NULL;
	m_pCamera.rot = VECTOR3_NULL;
	m_pCamera.vecU = VECTOR3_NULL;
	m_pCamera.posRDest = VECTOR3_NULL;
	m_pCamera.fDistance = NULL;
	m_pCamera.nMode = MODE_NONE;
	m_pCamera.nUseKey = NULL;
	m_pCamera.nCntAnim = NULL;

	// �C�x���g�p
	m_event.isActive = false;
	m_event.endFrame = NULL;
	m_event.frame = NULL;
	m_event.startPosR = VECTOR3_NULL;
	m_event.startPosV = VECTOR3_NULL;
	m_event.targetPosR = VECTOR3_NULL;
	m_event.targetPosV = VECTOR3_NULL;

	// �A�j���[�V�����p
	m_pCamera.m_AnimData.isLoop = false;
	m_pCamera.m_AnimData.nNumKey = 20;

	// �L�[�\���̕ϐ��̃N���A
	for (int nCnt = 0; nCnt < NUMKEY; nCnt++)
	{
		m_pCamera.m_AnimData.KeyInfo[nCnt].fDistance = 780.0f;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotZ = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].nAnimFrame = 40;
	}

	m_isAnimTime = false;
	m_nAnimNowKey = NULL;
	m_nFileIdx = NULL;
	m_nAnimShakeFlame = NULL;
	m_isCreate = false;
	m_isShake = false;
	m_nShakeTime = NULL;
	m_isLoad = false;
}
//=================================
// �f�X�g���N�^
//=================================
CCamera::~CCamera()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CCamera::Init(void)
{
	// �����l��ݒ肷��
	m_pCamera.posV = D3DXVECTOR3(0.0f, 1200.0f, 0.0f);			// �J�����̈ʒu
	m_pCamera.posR = VECTOR3_NULL;								// �J�����̌��Ă���ʒu
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);				// ������x�N�g��
	m_pCamera.rot = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);	// �p�x

	// �������v�Z
	float fRotx = m_pCamera.posV.x - m_pCamera.posR.x;
	float fRoty = m_pCamera.posV.y - m_pCamera.posR.y;
	float fRotz = m_pCamera.posV.z - m_pCamera.posR.z;

	// ���_���璍���_�܂ł̋���
	m_pCamera.fDistance = sqrtf((fRotx * fRotx) + (fRoty * fRoty) + (fRotz * fRotz));

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CCamera::Uninit(void)
{
	// ����
}
//=================================
// �X�V����
//=================================
void CCamera::Update(void)
{
	// �U���L����
	if (m_isShake)
	{
		// �U���X�V
		UpdateShake();
	}
	
	// �p�x�̐��K��
	if (m_pCamera.rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_pCamera.rot.y -= CAMERAINFO::NorRot;
	}

	// �p�x�̐��K��
	if (m_pCamera.rot.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
}
//=================================
// �J�������Z�b�g
//=================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_pCamera.mtxView,
		&m_pCamera.posV,
		&m_pCamera.posR,
		&m_pCamera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera.mtxprojection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_pCamera.mtxprojection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera.mtxprojection);

	// �t�H���g�Z�b�g
	CDebugproc::Print("Camera : PosV [ %.2f, %.2f, %.2f ]\n", m_pCamera.posV.x, m_pCamera.posV.y, m_pCamera.posV.z);

	// �`��J�n
	CDebugproc::Draw(0, 20);

	CDebugproc::Print("Camera : PosR [ %.2f, %.2f, %.2f ]\n", m_pCamera.posR.x, m_pCamera.posR.y, m_pCamera.posR.z);
	CDebugproc::Draw(0, 40);

	CDebugproc::Print("Camera : Rot [ %.2f, %.2f, %.2f ]\n", m_pCamera.rot.x, m_pCamera.rot.y, m_pCamera.rot.z);
	CDebugproc::Draw(0, 80);
}
//======================================
// �}�E�X����̎��_�ړ�
//======================================
void CCamera::MouseView(CInputMouse * pMouse)
{
	// ���N���b�N
	if (pMouse->GetPress(CInputMouse::MOUSE_LEFT))
	{
		// �}�E�X�̈ړ��ʎ擾
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		// ���݂̊p�x���v�Z
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// ��]�ʂ𐧌�
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// �J�����̎��_�̏��
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// �E�N���b�N
	else if (pMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// ��]�ʂ𐧌�
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// �J�������W���X�V
		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.y = m_pCamera.posV.y + cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}

	// ���K��
	if (m_pCamera.rot.y < -D3DX_PI)
	{
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.y > D3DX_PI)
	{
		m_pCamera.rot.y += -CAMERAINFO::NorRot;
	}
	if (m_pCamera.rot.x < -D3DX_PI)
	{
		m_pCamera.rot.x += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.x > D3DX_PI)
	{
		m_pCamera.rot.x += -CAMERAINFO::NorRot;
	}
}
//=============================
// �U���X�V�֐�
//=============================
void CCamera::UpdateShake(void)
{
	// �V�F�C�N�K�p
	if (m_isShake && (!m_event.isActive))
	{
		if (m_nShakeTime > 0)
		{
			// �����_���I�t�Z�b�g
			float fOffset = static_cast<float>(rand() % 80) - 40.0f;

			// ���_������h�炷
			m_pCamera.posR.x += fOffset;
			m_pCamera.posR.y += fOffset;
			m_pCamera.posR.z += fOffset;

			m_nShakeTime--;

			if (m_nShakeTime <= 0)
			{
				m_isShake = false;
				m_nShakeTime = 0;
			}
		}
		else
		{
			m_isShake = false;
		}
	}
}