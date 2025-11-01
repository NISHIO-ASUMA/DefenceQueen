//=======================================
//
// �����L���O�V�[������ [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "ranking.h"
#include "manager.h"
#include "rankingmanager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include <memory>

//===================================
// �I�[�o�[���[�h�R���X�g���N�^
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{

}
//===================================
// �f�X�g���N�^
//===================================
CRanking::~CRanking()
{
	// ����
}
//===================================
// ��������
//===================================
CRanking* CRanking::Create(void)
{
	// �C���X�^���X����
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pRanking->Init())) return nullptr;

	return pRanking;
}
//===================================
// ����������
//===================================
HRESULT CRanking::Init(void)
{
	// �C���X�^���X����
	//m_pRankManager = new CRankingManager;

	//// null����Ȃ�������
	//if (m_pRankManager != nullptr)
	//{
	//	// ����������
	//	m_pRankManager->Init();
	//}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===================================
// �I������
//===================================
void CRanking::Uninit(void)
{

}
//===================================
// �X�V����
//===================================
void CRanking::Update(void)
{
	// null�`�F�b�N
	// if (m_pRankManager != nullptr) m_pRankManager->Update();

	// ����L�[����
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetInstance()->GetFade();
		if (pFade == nullptr) return;

		// ��ʑJ��
		pFade->SetFade(std::make_unique<CTitle>());
		return;
	}
}
//===================================
// �`�揈��
//===================================
void CRanking::Draw(void)
{
	// ����
}