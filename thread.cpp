//=====================================
//
// �X���b�h�N���X���� [ thread.cpp ]
// Author: Asuma Nishio
//
// TOOD : ���Ԃ�m���Ă����낤
// �܂��̓}���`�X���b�h�̌�������
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "thread.h"

//**********************
// �g�p���O���
//**********************
using namespace std;

//============================
// �R���X�g���N�^
//============================
CThread::CThread()
{
	//�l�̃N���A
	m_isRunning = false;
}
//============================
// �f�X�g���N�^
//============================
CThread::~CThread()
{

}
//============================
// �X���b�h�J�n
//============================
void CThread::Start(std::function<void()> func)
{
	// �L����ԂȂ�
	if (m_isRunning) return;

	// �t���O��L����
	m_isRunning = true;

	// �����X���b�h���J�n����
	m_thread = std::thread(&CThread::ThreadProc, this, func);
}
//============================
// �X���b�h��~
//============================
void CThread::Stop(void)
{
	// �����X���b�h���܂��I����ĂȂ��Ȃ�
	if (m_thread.joinable())
	{
		// �X���b�h�I���܂ő҂�
		m_thread.join();
	}

	// �t���O�𖢎g�p�ɂ���
	m_isRunning = false;
}
//============================
// �����X���b�h����
//============================
void CThread::ThreadProc(std::function<void()> func)
{
	// �����̏������N��
	func();
}