//====================================
//
// �h�q�Ώۂ̏��� [ queen.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "nomovecharactor.h"
#include <memory>

//**********************
// �O���錾
//**********************
class CParameter;
class CShadowS;
class CStateMachine;
class CSphereCollider;
class CMotion;

//*******************************
// �����L�����N�^�[�N���X���`
//*******************************
class CQueen : public CNoMoveCharactor
{
public:

	//***********************************
	// ���[�V�����񋓌^
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// �j���[�g����
		MOTION_ACTION,		// �A�N�V����
		MOTION_DAMAGE,		// �_���[�W
		MOTION_DEATH,		// ���S���
		MOTION_MAX
	};

	CQueen(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CQueen();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CSphereCollider * pOther);

	static CQueen* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	std::unique_ptr<CParameter>m_pParameter;		// �p�����[�^�[�N���X�|�C���^
	std::unique_ptr<CStateMachine>m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^
	CMotion* m_pMotion;								// ���[�V�����|�C���^
	CSphereCollider* m_pSphereCollider;				// �~�`�̂̃R���C�_�[
};