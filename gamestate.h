//===============================================
//
// �Q�[����ԊǗ����� [ gamestate.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <memory>

//**********************
// �O���錾
//**********************
class CGame;

//****************************
// �Q�[����ԊǗ��N���X���`
//*****************************
class CGameState
{
public:

	//************************
	// �i�s��ԊǗ��񋓌^
	//************************
	enum PROGRESS
	{
		PROGRESS_NONE,		// ��������
		PROGRESS_NORMAL,	// �ʏ���
		PROGRESS_END,		// �Q�[���I��
		PROGRESS_MAX
	};

	CGameState();
	~CGameState();

	void OnStart();
	void OnUpdate();
	void OnExit();

	void SetProgress(PROGRESS progtype) { m_Progress = progtype; }
	void SetGame(CGame* pGame) { m_pGame = pGame; }

private:
	int m_nCount;			// �i�s�Ǘ��J�E���g
	PROGRESS m_Progress;	// �i�s��Ԃ̎��
	CGame * m_pGame; // �Q�[���V�[���|�C���^
};

