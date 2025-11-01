//===========================================
//
// �i�ߓ��L�����N�^�[�̏��� [ order.cpp ]
// Author: Asuma Nishio
//
//===========================================

//************************
// �C���N���[�h�t�@�C��
//************************
#include "order.h"
#include "motion.h"
#include "statemachine.h"
#include "spherecollider.h"
#include "collisionsphere.h"

//************************
// �萔���
//************************
namespace ORDERINFO
{

};

//======================================
// �R���X�g���N�^
//======================================
COrder::COrder(int nPriority) : CMoveCharactor(nPriority),
m_pMotion(nullptr),
m_pSphereCollider(nullptr),
m_pStateMachine(nullptr)
{
	// �l�̃N���A
}
//======================================
// �f�X�g���N�^
//======================================
COrder::~COrder()
{
	// ����
}
//======================================
// ��������
//======================================
COrder* COrder::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// �C���X�^���X����
	COrder* pOrder = new COrder;
	if (pOrder == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pOrder->SetPos(pos);
	pOrder->SetRot(rot);

	// ���������s��
	if (FAILED(pOrder->Init())) return nullptr;

	return pOrder;
}
//======================================
// ����������
//======================================
HRESULT COrder::Init(void)
{
	// �e�N���X�̏�����
	CMoveCharactor::Init();

	// �I�u�W�F�N�g�̎�ރZ�b�g
	CObject::SetObjType(TYPE_ORDER);

	// ���[�V�������[�h
	MotionLoad("data/MOTION/Order/Order.txt", MOTION_MAX);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = std::make_unique<CStateMachine>();

	// ������Ԃ��Z�b�g
	// ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);

	// �R���C�_�[����
	m_pSphereCollider = CSphereCollider::Create(GetPos(),60.0f);

	// ���[�V�����擾
	m_pMotion = CMoveCharactor::GetMotion();

	return S_OK;
}
//======================================
// �I������
//======================================
void COrder::Uninit(void)
{
	// �X�e�[�g�I������
	m_pStateMachine.reset();

	// �R���C�_�[�j��
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// �e�N���X�̏I������
	CMoveCharactor::Uninit();
}
//======================================
// �X�V����
//======================================
void COrder::Update(void)
{
	// ���݂̍��W���擾
	D3DXVECTOR3 pos = GetPos();

	// ���W�̍X�V
	CMoveCharactor::UpdatePosition();

	// �X�V��̍��W���擾
	D3DXVECTOR3 UpdatePos = GetPos();

	// �R���C�_�[���W�̍X�V
	m_pSphereCollider->SetPos(UpdatePos);

	// �R���W��������
	
	// �e�N���X�̍X�V
	CMoveCharactor::Update();
}
//======================================
// �`�揈��
//======================================
void COrder::Draw(void)
{
	// �e�N���X�̕`��
	CMoveCharactor::Draw();
}
//======================================
// �����蔻�菈��
//======================================
bool COrder::Collision(CSphereCollider* other)
{
	// ���`�̓����蔻��
	return CCollisionSphere::Collision(m_pSphereCollider, other);
}