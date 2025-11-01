//=====================================
//
// �|�[�Y�Ǘ����� [ pausemanager.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//********************************
// �O���錾
//********************************
class CPause;

//*********************************
// �|�[�Y���j���[�Ǘ��N���X���`
//*********************************
class CPauseManager
{
public:

	CPauseManager();
	~CPauseManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static void SetEnablePause(bool isFlags) { m_isPause = isFlags; }
	void SetEnablePause(void);

	static bool GetPause(void) { return m_isPause; }

private:

	static constexpr int SELECT_BEGIN = 1;	// ���j���[�J�n�ԍ�
	static constexpr int SELECT_END = 3;	// ���j���[�I���ԍ�
	static constexpr int SELECT_MAX = 4;	// �ő吶����

	static bool m_isPause;			// �|�[�Y���ǂ���
	int m_nSelectIdx;				// �Z���N�g�ԍ�
	CPause* m_pPause[SELECT_MAX];	// �|�[�Y�N���X�̃|�C���^�z��
};