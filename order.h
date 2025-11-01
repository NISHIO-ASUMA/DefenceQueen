//===========================================
//
// �i�ߓ��L�����N�^�[�̏��� [ order.h ]
// Author: Asuma Nishio
//
//===========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "movecharactor.h"
#include <memory>

//**********************
// �O���錾
//**********************
class CMotion;
class CStateMachine;
class CSphereCollider;

//********************************
// �i�ߓ��L�����N�^�[�N���X���`
//********************************
class COrder : public CMoveCharactor
{
public:

	//***********************************
	// �g�����[�V�����̎��
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// �j���[�g����
		MOTION_MOVE,		// �ړ�
		MOTION_ACTION,		// �A�N�V����
		MOTION_MAX
	};

	COrder(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~COrder();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(CSphereCollider* other);

	static COrder* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

	CMotion* m_pMotion;								// ���[�V�����N���X�̃|�C���^
	std::unique_ptr<CStateMachine>m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^
	CSphereCollider* m_pSphereCollider;				// ���`�̃R���C�_�[
};