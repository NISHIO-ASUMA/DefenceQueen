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
#include "manager.h"
#include "enemystatebase.h"
#include "statemachine.h"
#include "spherecollider.h"
#include "collisionsphere.h"

//===============================
// �R���X�g���N�^
//===============================
CEnemy::CEnemy(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_pSphereCollider(nullptr)
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
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// �C���X�^���X����
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);

	// �|�C���^����
	pEnemy->m_pParameter = std::make_unique<CParameter>();

	// null�`�F�b�N
	if (pEnemy->m_pParameter != nullptr)
	{
		pEnemy->m_pParameter->SetMaxHp(nLife);
		pEnemy->m_pParameter->SetHp(nLife);
	}

	// ���������s��
	if (FAILED(pEnemy->Init())) return nullptr;

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
	MotionLoad("data/MOTION/Enemy/EnemyMotion.txt", MOTION_MAX);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = std::make_unique<CStateMachine>();

	// ������Ԃ��Z�b�g
	// ChangeState(new CEnemyStateNeutral, CEnemyStateBase::ID_NEUTRAL);

	// �R���C�_�[����
	m_pSphereCollider = CSphereCollider::Create(GetPos(), 60.0f);

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

	// �R���C�_�[�j��
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// �L�����N�^�[�̔j��
	CMoveCharactor::Uninit();
}
//===============================
// �X�V����
//===============================
void CEnemy::Update(void)
{
	// ���W�擾
	D3DXVECTOR3 pos = GetPos();

	// ��ԊǗ��X�V
	if (m_pStateMachine != nullptr) m_pStateMachine->Update();

	// ���W�݂̂̍X�V
	CMoveCharactor::UpdatePosition();

	// ���̍��W�X�V
	if (m_pSphereCollider) m_pSphereCollider->SetPos(pos);

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
//================================
// �����蔻�菈��
//================================
bool CEnemy::Collision(CSphereCollider* pOther)
{
	// ���`���m�̓����蔻��
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}