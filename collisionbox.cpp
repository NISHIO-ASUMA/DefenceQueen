//==============================================
//
// ��`�̓����蔻�菈�� [ collisionbox.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "collisionbox.h"
#include "boxcollider.h"

//***********************
// �萔���
//***********************
namespace BOXINFO
{
	constexpr float HALF = 0.5f;		/// �����̔{���l
	constexpr float PUSHVALUE = 0.1f; // �����o�����Z�l
};

//============================
// �R���X�g���N�^
//============================
CCollisionBox::CCollisionBox() : CCollision(CCollision::TYPE_BOX)
{
	// �l�̃N���A
}
//============================
// �f�X�g���N�^
//============================
CCollisionBox::~CCollisionBox()
{
	// ����
}
//==============================
// ��`���m�̃R���W��������֐�
//==============================
bool CCollisionBox::Collision(CBoxCollider* thisCollider, CBoxCollider* OtherCollider, D3DXVECTOR3* ExtrusionPos)
{
	//===========================
	// �R���C�_�[�|�C���^���
	//===========================
	CBoxCollider* pMyCollider = thisCollider;
	CBoxCollider* pOtherCollider = OtherCollider;

	//===========================
	// �����Ƒ���̍��W���擾
	//===========================
	D3DXVECTOR3 MyPos = pMyCollider->GetPos();
	D3DXVECTOR3 OtherPos = pOtherCollider->GetPos();

	//===========================
	// �R���C�_�[�T�C�Y���擾
	//===========================
	D3DXVECTOR3 MySize = pMyCollider->GetInfo().Size;
	D3DXVECTOR3 OtherSize = pOtherCollider->GetInfo().Size;

	//================================
	// �����Ƒ���̔����̃T�C�Y���擾
	//================================
	D3DXVECTOR3 MyHalfSize = MySize * BOXINFO::HALF;
	D3DXVECTOR3 OtherHalfSize = OtherSize * BOXINFO::HALF;

	//===============================
	// �ő�ŏ����W���v�Z����
	//===============================
	D3DXVECTOR3 MyPosMax = MyPos + MyHalfSize;
	D3DXVECTOR3 MyPosMin = MyPos - MyHalfSize;
	D3DXVECTOR3 OtherPosMax = OtherPos + OtherHalfSize;
	D3DXVECTOR3 OtherPosMin = OtherPos - OtherHalfSize;
	
	//===========================
	// �ߋ��̍��W���擾
	//===========================
	D3DXVECTOR3 MyPosOldMin = pMyCollider->GetInfo().posOld - MyHalfSize;
	D3DXVECTOR3 MyPosOldMax = pMyCollider->GetInfo().posOld + MyHalfSize;
	D3DXVECTOR3 OtherPosOldMin = pOtherCollider->GetInfo().posOld - OtherHalfSize;
	D3DXVECTOR3 OtherPosOldMax = pOtherCollider->GetInfo().posOld + OtherHalfSize;

	// �����͈͓̔��ɓ����Ė��������画������Ȃ�
	const bool isHitRangeY = MyPosOldMin.y <= OtherPosOldMax.y && MyPosOldMax.y >= OtherPosOldMin.y;
	if (!isHitRangeY) return false;

	//==============================
	// z���͈͓̔��ɓ����Ă���Ƃ�
	//==============================
	if (MyPosOldMin.z < OtherPosMax.z && MyPosMax.z > OtherPosMin.z)
	{
		if (MyPosOldMax.x <= OtherPosMin.x && MyPosMax.x > OtherPosMin.x)
		{// ������߂荞��

			// �����ւ̉����o�����W���v�Z
			ExtrusionPos->x = OtherPosMin.x - MyHalfSize.x - BOXINFO::PUSHVALUE;
			return true;
		}
		else if (MyPosOldMin.x >= OtherPosMax.x && MyPosMin.x < OtherPosMax.x)
		{// �E����߂荞��
			
			// �E���ւ̉����o�����W���v�Z
			ExtrusionPos->x = OtherPosMax.x + MyHalfSize.x + BOXINFO::PUSHVALUE;
			return true;
		}
	}
	
	//==============================
	// x���͈͓̔��ɓ����Ă���Ƃ�
	//==============================
	if (MyPosOldMin.x < OtherPosMax.x && MyPosMax.x > OtherPosMin.x)
	{
		if (MyPosOldMax.z < OtherPosMin.z && MyPosMax.z > OtherPosMin.z)
		{// ��O����߂荞��

			// ��O�ւ̉����������W���v�Z
			ExtrusionPos->z = OtherPosMin.z - MyHalfSize.z - BOXINFO::PUSHVALUE;
			return true;
		}
		else if (MyPosOldMin.z > OtherPosMax.z && MyPosMin.z < OtherPosMax.z)
		{// �������O�ɂ߂荞��

			// �����ɉ����o�����W���v�Z����
			ExtrusionPos->z = OtherPosMax.z + MyHalfSize.z + BOXINFO::PUSHVALUE;
			return true;
		}
	}

	// ���q�b�g��
	return false;
}