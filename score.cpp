//====================================
//
// �X�R�A���� [ score.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "score.h"
#include "manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "load.h"

//==========================================
// �R���X�g���N�^
//==========================================
CScore::CScore(int nPriority) : CObject(nPriority),
m_nScore(NULL),
m_col(COLOR_WHITE),
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_apNumber{},
m_pLoad{},
m_fHeight(0.0f),
m_fWidth(0.0f)
{
	// �l�̃N���A
}
//==========================================
// �f�X�g���N�^
//==========================================
CScore::~CScore()
{
	// ����
}
//==========================================
// ��������
//==========================================
CScore* CScore::Create(D3DXVECTOR3 pos,float fWidth,float fHeight)
{
	// �X�R�A�C���X�^���X����
	CScore* pScore = new CScore;

	// nullptr��������
	if (pScore == nullptr) return nullptr;

	// ���W,�T�C�Y�ݒ�
	pScore->m_pos = pos;
	pScore->m_fWidth = fWidth;
	pScore->m_fHeight = fHeight;

	// ���������s��
	if (FAILED(pScore->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}
	
	// �X�R�A�|�C���^��Ԃ�
	return pScore;
}
//==========================================
// ����������
//==========================================
HRESULT CScore::Init(void)
{
	// �����v�Z
	float fTexPos = m_fWidth / NUM_SCORE;

	// ������
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// �C���X�^���X����
		m_apNumber[nCnt] = new CNumber;

		// ����������
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y,0.0f), fTexPos, m_fHeight);

		// �i���o�[�ϐ��̃T�C�Y
		m_apNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// ���W�ݒ�
		m_apNumber[nCnt]->SetPos(m_pos);

		// �e�N�X�`���Z�b�g
		m_apNumber[nCnt]->SetTexture("number003.png");
	}

	// �|�C���^����
	m_pLoad = std::make_unique<CLoad>();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==========================================
// �I������
//==========================================
void CScore::Uninit(void)
{
	// NOTE : ���� : �����ŃX�R�A�������o��
	// SaveScore();

	// �g�������j��
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_apNumber[nCnt] != nullptr)
		{
			// �I��
			m_apNumber[nCnt]->Uninit();

			// �j��
			delete m_apNumber[nCnt];

			// �|�C���^������
			m_apNumber[nCnt] = nullptr;
		}
	}

	// �|�C���^�I��
	m_pLoad.reset();

	// ���g�̔j��
	CObject::Release();
}
//==========================================
// �X�V����
//==========================================
void CScore::Update(void)
{
	// �X�R�A�i�[
	int nScore = m_nScore;

	// ������
	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++) // �E���珈��
	{
		// �������Ƃɕ�������l���v�Z
		int nDigit = nScore % NUM_DIGIT;

		nScore /= NUM_DIGIT;

		// �i���o�[�X�V
		m_apNumber[nCntScore]->Update();

		// ���X�V
		m_apNumber[nCntScore]->SetDigit(nDigit);
	}
}
//==========================================
// �`�揈��
//==========================================
void CScore::Draw(void)
{
	// �g���Ă��錅�����̕`��
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// �i���o�[�`��
		m_apNumber[nCnt]->Draw();
	}
}
//==========================================
// �X�R�A���Z����
//==========================================
void CScore::AddScore(int nValue)
{
	// �X�R�A���Z
	m_nScore += nValue;
}
//==========================================
// �X�R�A������
//==========================================
void CScore::DeleteScore()
{
	m_nScore = NULL;
}
//==========================================
// �X�R�A�����o������
//==========================================
void CScore::SaveScore(void)
{
	// ��̐��l�������o��
	m_pLoad->SaveInt("data/SCORE/GameScore.bin", m_nScore);
}
