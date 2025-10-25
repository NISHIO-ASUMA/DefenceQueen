//====================================
//
// �}�l�[�W���[���� [ manager.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**************************  
// �O���錾
//**************************
class CInputKeyboard;
class CJoyPad;
class CInputMouse;
class CSound;
class CTexture;
class CCamera;
class CLight;
class CFade;
class CXfileManager;
class CScene;

//**************************  
// �C���N���[�h�t�@�C��
//**************************
#include <memory>
#include "scene.h"
#include "renderer.h"

//**************************
// �}�l�[�W���[�N���X�錾
//**************************
class CManager
{
public:

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CRenderer* GetRenderer(void) { return m_pRenderer.get(); }
	CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard.get(); }
	CJoyPad* GetJoyPad(void) { return m_pJoyPad.get(); }
	CSound* GetSound(void) { return m_pSound.get(); }
	CInputMouse* GetMouse(void) { return m_pInputMouse.get(); }
	CTexture* GetTexture(void) { return m_pTexture.get(); }
	CCamera* GetCamera(void) { return m_pCamera.get(); }
	CLight* GetLight(void) { return m_pLight.get(); }
	CFade* GetFade(void) { return m_pFade.get(); }
	CXfileManager* GetXManager(void) { return m_pXfileManager.get(); }

	// �V�[���֘A
	CScene* GetSceneRaw(void) { return m_pScene.get(); }	// ���|�C���^��Ԃ�
	void SetScene(std::unique_ptr<CScene> pNewScene);	// unique_ptr�Ŏ󂯎��
	CScene::MODE GetScene(void);

	// �C���X�^���X�擾
	static CManager* GetInstance(void)
	{
		static CManager pManeger;
		return &pManeger;
	};

private:

	CManager();
	~CManager();

	std::unique_ptr<CRenderer>m_pRenderer;			// �����_���[�N���X�̃|�C���^
	std::unique_ptr<CInputKeyboard>m_pInputKeyboard;// �L�[�{�[�h�N���X�̃|�C���^
	std::unique_ptr<CJoyPad>m_pJoyPad;				// �W���C�p�b�h�N���X�̃|�C���^
	std::unique_ptr<CSound>m_pSound;				// �T�E���h�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<CInputMouse>m_pInputMouse;		// �}�E�X�N���X�̃|�C���^
	std::unique_ptr<CTexture>m_pTexture;			// �e�N�X�`���N���X�̃|�C���^
	std::unique_ptr<CCamera>m_pCamera;				// �J�����N���X�̃|�C���^
	std::unique_ptr<CLight>m_pLight;				// ���C�g�N���X�̃|�C���^	
	std::unique_ptr<CScene>m_pScene;;				// �V�[���Ǘ��N���X�̃|�C���^
	std::unique_ptr<CFade>m_pFade;					// �t�F�[�h�N���X�̃|�C���^
	std::unique_ptr<CXfileManager>m_pXfileManager;	// X�t�@�C���}�l�[�W���[�N���X
};