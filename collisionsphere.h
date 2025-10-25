//=================================================
//
// ���`�����蔻�菈�� [ collisionsphere.h ]
// Author: Asuma Nishio
// 
//=================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "collision.h"

//**********************
// �O���錾
//**********************
class CSphereCollider;

//**************************
// ���`���m�̓����蔻�菈��
//**************************
class CCollisionSphere : public CCollision
{
public:

	CCollisionSphere();
	~CCollisionSphere();

	/// <summary>
	/// ���`���m�̓����蔻��֐�
	/// </summary>
	/// <param name="thisCollider">�����������Ă�R���C�_�[</param>
	/// <param name="otherCollider">�����̃R���C�_�[</param>
	/// <returns></returns>
	static bool Collision(CSphereCollider * thisCollider, CSphereCollider * otherCollider);

private:

};