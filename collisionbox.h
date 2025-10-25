//=============================================
//
// ��`�̓����蔻�菈�� [ collisionbox.h ]
// Author: Asuma Nishio
// 
//==============================================

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
class CBoxCollider;

//*************************************
// ��`�̓����蔻�������N���X���`
//*************************************
class CCollisionBox : public CCollision
{
public:
	CCollisionBox();
	~CCollisionBox();

	/// <summary>
	/// ��`���m�̓����蔻������s����
	/// </summary>
	/// <param name="thisCollider">�����������Ă��`�R���C�_�[</param>
	/// <param name="OtherCollider">�����̋�`�R���C�_�[</param>
	/// <param name="ExtrusionPos">�q�b�g�������o�����W</param>
	/// <returns></returns>
	static bool Collision(CBoxCollider* thisCollider, CBoxCollider* OtherCollider,D3DXVECTOR3 * ExtrusionPos);

private:
};

