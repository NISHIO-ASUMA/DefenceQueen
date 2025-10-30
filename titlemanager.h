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

//***********************
// �C���N���[�h�t�@�C��
//***********************
#include <memory>

//**************************************
// �^�C�g���}�l�[�W���[�Ǘ��N���X���`
//**************************************
class CTitleManager
{
public:

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �C���X�^���X�擾
	static CTitleManager* GetInstance(void)
	{
		// �C���X�^���X��Ԃ�
		static CTitleManager pTitleManager;
		return &pTitleManager;
	}

private:

	CTitleManager();
	~CTitleManager();

	CUi* m_pUi;				// �N���X�|�C���^
	int m_nIdx;				// �I��ԍ�
};