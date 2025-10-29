//====================================
//
// �h�q�Ώۂ̏��� [ queen.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "queen.h"
#include "collisionsphere.h"
#include "spherecollider.h"
#include "parameter.h"
#include "statemachine.h"

//==================================
// �R���X�g���N�^
//==================================
CQueen::CQueen(int nPriority) : CNoMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr)
{
	// �l�̃N���A
}
//==================================
// �f�X�g���N�^
//==================================
CQueen::~CQueen()
{

}
//==================================
// ��������
//==================================
CQueen* CQueen::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �C���X�^���X����
	CQueen* pQueen = new CQueen;
	if (pQueen == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pQueen->SetPos(pos);
	pQueen->SetRot(rot);

	// ���������s��
	if (FAILED(pQueen->Init())) return nullptr;

	// �������ꂽ�|�C���^
	return pQueen;
}
//==================================
// ����������
//==================================
HRESULT CQueen::Init(void)
{
	// �e�N���X�̏�����
	CNoMoveCharactor::Init();

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(CObject::TYPE_QUEEN);

	// ���[�V�����Z�b�g
	MotionLoad("data/MOTION/Queen/QueenMotion.txt", MOTION_MAX);

	// �p�����[�^�[����
	m_pParameter = std::make_unique<CParameter>();
	m_pParameter->SetMaxHp(HP);
	m_pParameter->SetHp(HP);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = std::make_unique<CStateMachine>();

	// ������Ԃ��Z�b�g
	// ChangeState(new CPlayerStateNeutral, CPlayerStateBase::ID_NEUTRAL);

	// �R���C�_�[����
	m_pSphereCollider = CSphereCollider::Create(GetPos(),80.0f);

	// ���[�V�����擾
	m_pMotion = CNoMoveCharactor::GetMotion();

	return S_OK;
}
//==================================
// �I������
//==================================
void CQueen::Uninit(void)
{
	// �|�C���^�j��
	m_pParameter.reset();

	// �X�e�[�g�I������
	m_pStateMachine.reset();

	// �R���C�_�[�j��
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// �e�N���X�̏I������
	CNoMoveCharactor::Uninit();
}
//==================================
// �X�V����
//==================================
void CQueen::Update(void)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 pos = GetPos();

	// �R���C�_�[�̈ʒu�X�V
	m_pSphereCollider->SetPos(pos);

	// �e�N���X�̍X�V
	CNoMoveCharactor::Update();
}
//==================================
// �`�揈��
//==================================
void CQueen::Draw(void)
{
	// �e�N���X�̕`��
	CNoMoveCharactor::Draw();
}
//==================================
// �����蔻�菈��
//==================================
bool CQueen::Collision(CSphereCollider* pOther)
{
	return CCollisionSphere::Collision(m_pSphereCollider,pOther);
}
