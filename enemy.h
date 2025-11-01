//=====================================
//
// �G�̏��� [ enemy.h ]
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
#include "model.h"
#include "motion.h"
#include "movecharactor.h"
#include <memory>

//**********************
// �O���錾
//**********************
class CParameter;
class CShadowS;
class CStateMachine;
class CEnemyStateBase;
class CSphereCollider;

//**********************
// �G�N���X���`
//**********************
class CEnemy : public CMoveCharactor
{
public:

	//***********************************
	// �G���[�V�����񋓌^
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,	// �j���[�g����
		MOTION_MOVE,	// �ړ�
		MOTION_ACTION,	// �A�N�V����
		MOTION_DAMAGE,	// �_���[�W
		MOTION_MAX
	};

	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CEnemy();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void ChangeState(CEnemyStateBase* pNewState, int Id);
	bool Collision(CSphereCollider* pOther);

	CParameter* GetParameter(void) { return m_pParameter.get(); }
	CStateMachine* GetStateMachine() { return m_pStateMachine.get(); }

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife);

private:

	CMotion * m_pMotion;				// ���[�V�����N���X
	CSphereCollider* m_pSphereCollider; // ���`�R���C�_�[
	std::unique_ptr <CParameter>m_pParameter;		 // �p�����[�^�N���X
	std::unique_ptr<CStateMachine>m_pStateMachine;	 // �X�e�[�g���N���X�̃|�C���^
};