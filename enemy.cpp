//=====================================
//
// �G�̏��� [ enemy.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "enemy.h"
#include "parameter.h"
#include "motion.h"
#include "shadowS.h"
#include "state.h"
#include "manager.h"
#include "enemystatebase.h"
#include "enemystate.h"
#include "statemachine.h"

//===============================
// �R���X�g���N�^
//===============================
CEnemy::CEnemy(int nPriority) : CMoveCharactor(nPriority),
m_pFileName{},
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr)
{
	// �l�̃N���A
}
//===============================
// �f�X�g���N�^
//===============================
CEnemy::~CEnemy()
{
	// ����
}
//===============================
// ��������
//===============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, const char* pFileName)
{
	// �C���X�^���X����
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->m_pFileName = pFileName;

	// �|�C���^����
	pEnemy->m_pParameter = std::make_unique<CParameter>();

	// null�`�F�b�N
	if (pEnemy->m_pParameter != nullptr)
	{
		pEnemy->m_pParameter->SetMaxHp(nLife);
		pEnemy->m_pParameter->SetHp(nLife);
	}

	// ���������s��
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	// �G�̃|�C���^��Ԃ�
	return pEnemy;
}
//===============================
// ����������
//===============================
HRESULT CEnemy::Init(void)
{
	// �L�����N�^�\�̏�����
	CMoveCharactor::Init();

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(CObject::TYPE_ENEMY);

	// ���[�V�����Z�b�g
	MotionLoad(m_pFileName, MOTION_MAX);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = std::make_unique<CStateMachine>();

	// ������Ԃ��Z�b�g
	// ChangeState(new CEnemyStateNeutral, CEnemyStateBase::ID_NEUTRAL);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CEnemy::Uninit(void)
{
	// �p�����[�^�I������
	m_pParameter.reset();

	// �X�e�[�g�I������
	m_pStateMachine.reset();

	// �L�����N�^�[�̔j��
	CMoveCharactor::Uninit();
}
//===============================
// �X�V����
//===============================
void CEnemy::Update(void)
{
	// ��ԊǗ��X�V
	if (m_pStateMachine != nullptr) m_pStateMachine->Update();

	// �L�����N�^�[�̍X�V����
	CMoveCharactor::Update();

}
//===============================
// �`�揈��
//===============================
void CEnemy::Draw(void)
{
	// �L�����N�^�[�̕`�揈��
	CMoveCharactor::Draw();
}
//================================
// ��ԕύX����
//================================
void CEnemy::ChangeState(CEnemyStateBase* pNewState, int Id)
{
	// �X�e�[�g�ύX
	pNewState->SetOwner(this);

	// �X�e�[�g�ύX
	m_pStateMachine->ChangeState(pNewState);
}