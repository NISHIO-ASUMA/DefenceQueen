//===================================================
//
// �v���C���[�̒��ԏ��� [ array.cpp ]
// Author: Asuma Nishio
//
//===================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "array.h"
#include "parameter.h"
#include "manager.h"
#include "spherecollider.h"
#include "collisionsphere.h"
#include "statemachine.h"
#include "state.h"

//=====================================
// �R���X�g���N�^
//=====================================
CArray::CArray(int nPriority) : CMoveCharactor(nPriority),
m_pSphereCollider(nullptr),
m_pMotion(nullptr),
m_pParameter(nullptr),
m_pStateMachine(nullptr),
m_isActive(false)
{
	// �l�̃N���A
}
//=====================================
// �f�X�g���N�^
//=====================================
CArray::~CArray()
{

}
//=====================================
// ��������
//=====================================
CArray* CArray::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife)
{
	// �C���X�^���X����
	CArray* pArray = new CArray;
	if (pArray == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pArray->SetPos(pos);
	pArray->SetRot(rot);
	pArray->m_pParameter = std::make_unique<CParameter>();

	// null�`�F�b�N
	if (pArray->m_pParameter != nullptr)
	{
		// �̗̓p�����[�^�[��ݒ�
		pArray->m_pParameter->SetHp(nLife);
		pArray->m_pParameter->SetMaxHp(nLife);
	}

	// ����������
	if (FAILED(pArray->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �����|�C���^��Ԃ�
	return pArray;
}
//=====================================
// ����������
//=====================================
HRESULT CArray::Init(void)
{
	// �e�N���X�̏�����
	CMoveCharactor::Init();

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(CObject::TYPE_ARRAY);

	// ���[�V�����Z�b�g
	MotionLoad("data/MOTION/Array/ArrayMotion.txt", MOTION_MAX);

	// �X�e�[�g�}�V���𐶐�
	// m_pStateMachine = std::make_unique<CStateMachine>();

	// �X�t�B�A�R���C�_�[����
	m_pSphereCollider = CSphereCollider::Create(GetPos(),80.0f);

	// ���[�V�����擾
	m_pMotion = CMoveCharactor::GetMotion();

	return S_OK;
}
//=====================================
// �I������
//=====================================
void CArray::Uninit(void)
{
	// �p�����[�^�[�I������
	m_pParameter.reset();

	// �X�e�[�g�I������
	// m_pStateMachine.reset();

	// �R���C�_�[�j��
	if (m_pSphereCollider)
	{
		delete m_pSphereCollider;
		m_pSphereCollider = nullptr;
	}

	// �L�����N�^�[�̔j��
	CMoveCharactor::Uninit();
}
//=====================================
// �X�V����
//=====================================
void CArray::Update(void)
{
	// false�Ȃ�ʂ��Ȃ�
	if (!m_isActive) return;

	// ���W�݂̂̍X�V����
	CMoveCharactor::UpdatePosition();

	// �̗͂��Ȃ�
	if (m_pParameter && m_pParameter->GetHp() <= 0)
	{
		// �̗͂�0�ɂ���
		m_pParameter->SetHp(NULL);

		// ���g�p�ɂ���
		SetActive(false);
	}

	// �L�����N�^�[�̍X�V
	CMoveCharactor::Update();
}
//=====================================
// �`�揈��
//=====================================
void CArray::Draw(void)
{
	// false�Ȃ�ʂ��Ȃ�
	if (!m_isActive) return;

	// �L�����N�^�[�̕`��
	CMoveCharactor::Draw();
}
//=====================================
// �p�����[�^�Đݒ菈��
//=====================================
void CArray::Reset(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nLife)
{
	SetPos(pos);
	SetRot(rot);
	SetActive(true);
	if (m_pParameter)
	{
		m_pParameter->SetMaxHp(nLife);
		m_pParameter->SetHp(nLife);
	}
}
//=====================================
// �����蔻�菈��
//=====================================
bool CArray::Colision(CSphereCollider* other)
{
	return CCollisionSphere::Collision(m_pSphereCollider,other);
}