//=====================================
//
// �}�l�[�W���[���� [ manager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "manager.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "ranking.h"
#include "object.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "collision.h"
#include "fade.h"
#include "xfilemanager.h"

//===========================
// �R���X�g���N�^
//===========================
CManager::CManager()
{
	// ����
}
//===========================
// �f�X�g���N�^
//===========================
CManager::~CManager()
{
	// ����
}
//===========================
// �}�l�[�W���[�̏���������
//===========================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �L�[�{�[�h�I�u�W�F�N�g�̐�������
	m_pInputKeyboard = std::make_unique<CInputKeyboard>();

	// �������Ɏ��s������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// �W���C�p�b�h�I�u�W�F�N�g�̐�������
	m_pJoyPad = std::make_unique<CJoyPad>();

	// �������Ɏ��s������
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// �}�E�X�I�u�W�F�N�g�̐�������
	m_pInputMouse = std::make_unique<CInputMouse>();

	// �������Ɏ��s������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// �T�E���h�̐�������
	m_pSound = std::make_unique<CSound>();

	if (FAILED(m_pSound->Init(hWnd)))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// �J�����̐�������
	m_pCamera = std::make_unique<CCamera>();

	// �������Ɏ��s������
	if (FAILED(m_pCamera->Init()))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// �����_���[�̐�������
	m_pRenderer = std::make_unique <CRenderer>();

	// �������Ɏ��s������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// ���C�g����
	m_pLight = std::make_unique <CLight>();

	// �������Ɏ��s������
	if (FAILED(m_pLight->Init()))
	{
		// E_FAIL��Ԃ�
		return E_FAIL;
	}

	// �e�N�X�`������
	m_pTexture = std::make_unique <CTexture>();

	// �e�N�X�`���S�ǂݍ���
	m_pTexture->Load();

	// X�t�@�C���I�u�W�F�N�g�}�l�[�W���[����
	m_pXfileManager = std::make_unique <CXfileManager>();

	// �S���f���̓ǂݍ���
	m_pXfileManager->Load();

	// �t�F�[�h����
	m_pFade = std::make_unique <CFade>();

	// ���������s��
	if (FAILED(m_pFade->Init()))
	{
		// -1��Ԃ�
		return E_FAIL;
	}

#ifdef _DEBUG
	// �V�[���Z�b�g
	m_pFade->SetFade(std::make_unique<CGame>());
#else
	// �V�[���Z�b�g
	m_pFade->SetFade(std::make_unique<CTitle>());

#endif // _DEBUG

	return S_OK;
}
//===========================
// �}�l�[�W���[�̏I������
//===========================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�C���X�^���X�̔j��
	m_pInputKeyboard.reset();

	// �Q�[���p�b�h�C���X�^���X�̔j��
	m_pJoyPad.reset();

	// �}�E�X�C���X�^���X�̔j��
	m_pInputMouse.reset();

	// �T�E���h�C���X�^���X�̔j��
	m_pSound.reset();

	// �J�����C���X�^���X�̔j��
	m_pCamera.reset();

	// ���C�g�C���X�^���X�̔j��
	m_pLight.reset();

	// �e�N�X�`���C���X�^���X�̔j��
	m_pTexture.reset();

	// ���f���C���X�^���X�̔j��
	m_pXfileManager.reset();

	// �V�[���̔j��
	if (m_pScene)
	{
		m_pScene->Uninit();
		m_pScene.reset();
	}

	// �t�F�[�h�̔j��
	if (m_pFade)
	{
		m_pFade->Uninit();
		m_pFade.reset();
	}

	// �����_���[�̔j��
	if (m_pRenderer)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();
		m_pRenderer.reset();
	}
}
//===========================
// �}�l�[�W���[�̍X�V����
//===========================
void CManager::Update()
{
	// �L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	// �W���C�p�b�h�̍X�V����
	m_pJoyPad->Update();

	// �}�E�X�̍X�V����
	m_pInputMouse->Update();

	// �W���C�p�b�h�U���̍X�V����
	m_pJoyPad->UpdateVibration();

	// �J�����X�V
	m_pCamera->Update();

	// �t�F�[�h�̍X�V
	m_pFade->Update();

	// null�`�F�b�N
	if (m_pScene != nullptr)
	{
		// �V�[���̍X�V
		m_pScene->Update();
	}

	// �����_���[�̍X�V����
	m_pRenderer->Update();
}
//===========================
// �}�l�[�W���[�̕`�揈��
//===========================
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//===========================
// �V�[���̃Z�b�g
//===========================
void CManager::SetScene(std::unique_ptr<CScene> pNewScene)
{
	// nullptr����Ȃ�
	if (m_pScene != nullptr)
	{
		// �I������
		m_pScene->Uninit();

		// null����Ȃ�
		if (m_pSound)
		{
			// �T�E���h�̒�~
			m_pSound->StopSound();
		}

		// �S�I�u�W�F�N�g�j��
		CObject::ReleaseAll();

		// �Â��V�[����j��
		m_pScene.reset();
	}

	// �����V�[��������������
	if (pNewScene)
	{
		// �V�[���̏�����
		if (FAILED(pNewScene->Init()))
		{
			// ���s��
			MessageBox(GetActiveWindow(), "�V�[�����������s", "��O�X���[", MB_OK);
			pNewScene.reset();
			return;
		}

		// ���L�����}�l�[�W���Ɉړ�
		m_pScene = std::move(pNewScene);
	}
}
//===========================
// ���݃V�[���擾
//===========================
CScene::MODE CManager::GetScene(void)
{
	// nullptr����Ȃ�
	if (m_pScene)
		return m_pScene->GetScene(); // ���݃V�[��
	else
		return CScene::MODE_NONE;	 // �����Ȃ��V�[��
}