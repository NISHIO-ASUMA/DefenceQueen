//=====================================
//
// ���C���֐� [ main.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//*****************************
// ���C���v���Z�X�N���X���`
//*****************************
class CMainProc
{
public:
	CMainProc();
	~CMainProc();

	void ToggleFullScreen(HWND hWnd);

private:
	RECT m_Windowrect;	// �E�B���h�E�̕�
};
