//=====================================
//
// �v���C���[���� [ player.h ]
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
#include "movecharactor.h"
#include <memory>

//**********************
// �O���錾
//**********************
class CShadow;
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;
class CBoxCollider;
class CMotion;

//*************************
// �v���C���[�N���X���`
//*************************
class CPlayer : public CMoveCharactor
{
public:
	//***********************************
	// �v���C���[���s�����[�V�����񋓌^
	//***********************************
	enum MOTION
	{
		MOTION_NEUTRAL,		// �j���[�g����
		MOTION_MOVE,		// �ړ�
		MOTION_ACTION,		// �A�N�V����
		MOTION_JUMP,		// �W�����v
		MOTION_LANDING,		// ���n
		MOTION_JUMPATTACK,	// �W�����v�U��
		MOTION_DAMAGE,		// �_���[�W
		MOTION_AVOID,		// ���
		MOTION_MAX
	};

	CPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CPlayer();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void ChangeState(CPlayerStateBase* pNewState,int Id);
	bool CollisionBlock(D3DXVECTOR3 * pos);

	CParameter* GetParameter(void) { return m_pParameter.get(); }
	CStateMachine* GetStateMachine() { return m_pStateMachine.get(); }

	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,const char* pFilename);
	static bool IsDeath(void) { return m_isDeath; }

private:
	static bool m_isDeath;  // �ÓI
	std::unique_ptr<CParameter>m_pParameter; // �p�����[�^�[�N���X�|�C���^
	std::unique_ptr<CStateMachine>m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^
	CMotion* m_pMotion;				// ���[�V�����|�C���^
	CBoxCollider* m_pBoxCollider;	// ��`�̃R���C�_�[
};