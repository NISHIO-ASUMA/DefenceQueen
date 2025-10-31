//=================================================
//
// ���`�����蔻�菈�� [ collisionsphere.cpp ]
// Author: Asuma Nishio
// 
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "collisionsphere.h"
#include "spherecollider.h"

//================================
// �R���X�g���N�^
//================================
CCollisionSphere::CCollisionSphere() : CCollision(CCollision::TYPE_SPHERE)
{
	// �l�̃N���A
}
//================================
// �f�X�g���N�^
//================================
CCollisionSphere::~CCollisionSphere()
{
	// ����
}
//================================
// �����m�̓����蔻��
//================================
bool CCollisionSphere::Collision(CSphereCollider* thisCollider, CSphereCollider* otherCollider)
{
	// �R���C�_�[�����Z�b�g
	CSphereCollider* MySphere = thisCollider;
	CSphereCollider* OtherSphere = otherCollider;

	// ���W���擾����
	D3DXVECTOR3 MyPos = MySphere->GetPos();
	D3DXVECTOR3 OtherPos = OtherSphere->GetPos();

	// �͈͂��擾����
	float fMyRadius = MySphere->GetRadius();
	float fOtherRadius = OtherSphere->GetRadius();

	// 2�_�̍��W�̋����������Z�o����
	D3DXVECTOR3 DiffPos = MyPos - OtherPos;

	// �����鋗�����v�Z����
	float fDistance = (DiffPos.x * DiffPos.x) + (DiffPos.y * DiffPos.y) + (DiffPos.z * DiffPos.z);

	// ���a��2����v�Z
	float fAllRadius = fMyRadius + fOtherRadius;
	fAllRadius = fAllRadius * fAllRadius;
	
	// ���a�̒l����������������
	if (fDistance <= fAllRadius)return true;

	// ���q�b�g��
	return false;
}