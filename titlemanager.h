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
// �O���錾
//***********************
class CTitleUi;
class CUi;

//**************************************
// �^�C�g���}�l�[�W���[�Ǘ��N���X���`
//**************************************
class CTitleManager
{
public:

	CTitleManager();
	~CTitleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	CUi* m_pUi;				// �N���X�|�C���^
	int m_nIdx;				// �I��ԍ�
	bool m_isuiCreate;		// �������ꂽ���ǂ����̔��ʃt���O
	bool m_isFirstuiCreate;	// �ŏ��̃V�[���Ő������ꂽ�����ʃt���O
};