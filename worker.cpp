//=================================================
//
// �w�����o�������A���̏��� [ worker.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "worker.h"
#include "spherecollider.h"
#include "collisionsphere.h"
#include "motion.h"
#include "statemachine.h"

//=================================
// �R���X�g���N�^
//=================================
CWorker::CWorker(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pSphereCollider(nullptr),
m_pStateMachine(nullptr)
{

}
//=================================
// �f�X�g���N�^
//=================================
CWorker::~CWorker()
{

}
//=================================
// ��������
//=================================
CWorker* CWorker::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	return nullptr;
}
//=================================
// ����������
//=================================
HRESULT CWorker::Init(void)
{
	// �e�N���X�̏�����
	CMoveCharactor::Init();

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(CObject::TYPE_WORKER);

	// ���[�V�����Z�b�g
	MotionLoad("data/MOTION/Worker/Worker.txt", MOTION_MAX);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = std::make_unique<CStateMachine>();

	// ������Ԃ��Z�b�g
	// ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);

	// �R���C�_�[����
	m_pSphereCollider = CSphereCollider::Create(GetPos(), 60.0f);

	// ���[�V�����|�C���^�擾
	m_pMotion = CMoveCharactor::GetMotion();

	return S_OK;
}
//=================================
// �I������
//=================================
void CWorker::Uninit(void)
{
	// �j��
	m_pStateMachine.reset();

	// �j��
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// �e�N���X�̏I��
	CMoveCharactor::Uninit();
}
//=================================
// �X�V����
//=================================
void CWorker::Update(void)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 pos = GetPos();

	// �L�����N�^�[�̍��W�X�V
	CMoveCharactor::UpdatePosition();

	// �X�V��̍��W���擾
	D3DXVECTOR3 UpdatePos = GetPos();

	// �R���C�_�[���W�̍X�V
	if (m_pSphereCollider) m_pSphereCollider->SetPos(UpdatePos);

	// �L�����N�^�[�S�̂̍X�V����
	CMoveCharactor::Update();
}
//=================================
// �`�揈��
//=================================
void CWorker::Draw(void)
{
	// �L�����N�^�[�`��
	CMoveCharactor::Draw();
}
//=================================
// �����蔻�菈��
//=================================
bool CWorker::Collision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}