//=====================================
//
// �X���b�h�N���X���� [ thread.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <thread>
#include <atomic>
#include <functional>

//**********************
// �X���b�h�N���X���`
//**********************
class CThread
{
public:

	CThread();
	~CThread();

	// �X���b�h�J�n�֐�
	void Start(std::function<void()> func);

	// �X���b�h��~�֐�
	void Stop(void);

	// �X���b�h�����쒆��
	bool IsRunning(void) const { return m_isRunning; }

private:

	// �����X���b�h�֐�
	void ThreadProc(std::function<void()> func);

	std::thread m_thread; // �X���b�h�ϐ�
	std::atomic<bool> m_isRunning; // �X���b�h���쒆���̃t���O
};