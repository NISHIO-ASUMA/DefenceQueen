//==========================================
//
// �^�C�g���Ǘ����� [ titlemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//***********************
// �C���N���[�h�t�@�C��
//***********************
#include "scenemanagebase.h"

//***********************
// �O���錾
//***********************
class CTitleUi;
class CUi;

//**************************************
// �^�C�g���}�l�[�W���[�Ǘ��N���X���`
//**************************************
class CTitleManager : public CSceneManageBase
{
public:

	CTitleManager();
	~CTitleManager();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	CUi* m_pUi;				// �N���X�|�C���^
	int m_nIdx;				// �I��ԍ�
	bool m_isuiCreate;		// �������ꂽ���ǂ����̔��ʃt���O
	bool m_isFirstuiCreate;	// �ŏ��̃V�[���Ő������ꂽ�����ʃt���O
};