//=================================================
//
// �w�����o�������A���̏��� [ worker.h ]
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
#include "movecharactor.h"
#include <memory>

//**********************
// �O���錾
//**********************
class CMotion;
class CStateMachine;
class CSphereCollider;

//**********************
// �����A���N���X�̒�`
//**********************
class CWorker : public CMoveCharactor
{
public:

	//***********************************
	// ���[�V�����񋓌^
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// �j���[�g����
		MOTION_MOVE,		// �ړ�
		MOTION_ACTION,		// �A�N�V����
		MOTION_MAX
	};

	CWorker(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CWorker();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool Collision(CSphereCollider* other);

	static CWorker* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

	std::unique_ptr<CStateMachine>m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^
	CMotion* m_pMotion;					// ���[�V�����|�C���^
	CSphereCollider* m_pSphereCollider;	// ���`�̃R���C�_�[

};
