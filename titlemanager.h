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

	~CTitleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleManager* GetInstance(void);

private:

	CTitleManager();

	CUi* m_pUi;				// �N���X�|�C���^
	int m_nIdx;				// �I��ԍ�
};