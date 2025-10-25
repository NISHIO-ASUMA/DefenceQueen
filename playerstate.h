//=============================================
//
// �v���C���[��ԊǗ����� [ playerstate.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "state.h"
#include "player.h"

//*********************************
// �v���C���[�̃x�[�X��ԊǗ�
//*********************************
class CPlayerStateBase : public CStateBase
{
public:
	//***************************
	// ��ԊǗ�ID�񋓌^
	//***************************
	enum ID
	{
		ID_NEUTRAL, // �ҋ@
		ID_MOVE, // �ړ�
		ID_ACTION, // �U��
		ID_JUMP, // �W�����v
		ID_GUARD, // �h��
		ID_DAMAGE,// �_���[�W
		ID_AVOIDRIGHT, // ���
		ID_AVOIDLEFT, // ���
		ID_MAX
	};

	CPlayerStateBase();
	~CPlayerStateBase();

	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnExit() {}

	int GetID() const override { return m_ID; }
	
	void SetID(ID id) { m_ID = id; }
	void SetOwner(CPlayer* pPlayer) { m_pPlayer = pPlayer; }

protected:
	CPlayer* m_pPlayer;		// �v���C���[�̃|�C���^

private:
	ID m_ID;		// �񋓌^�̃|�C���^
};

//*********************************
// �ҋ@��Ԏ��̏�ԊǗ�
//*********************************
class CPlayerStateNeutral : public CPlayerStateBase
{
public:

	CPlayerStateNeutral();
	~CPlayerStateNeutral();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:
};


//*********************************
// �ړ����̏�ԊǗ�
//*********************************
class CPlayerStateMove : public CPlayerStateBase
{
public:

	CPlayerStateMove();
	~CPlayerStateMove();

	void OnStart();
	void OnUpdate();
	void OnExit();
};

//*********************************
// �U�����̏�ԊǗ�
//*********************************
class CPlayerStateAction : public CPlayerStateBase
{
public:

	CPlayerStateAction();
	~CPlayerStateAction();

	void OnStart();
	void OnUpdate();
	void OnExit();
};

//*********************************
// �W�����v��Ԏ��̊Ǘ�
//*********************************
class CPlayerStateJump : public CPlayerStateBase
{
public:

	CPlayerStateJump();
	~CPlayerStateJump();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};

//*********************************
// �������Ԏ��̊Ǘ�
//*********************************
class CPlayerStateAvoidLeft : public CPlayerStateBase
{
public:

	CPlayerStateAvoidLeft();
	~CPlayerStateAvoidLeft();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};

//*********************************
// �E�����Ԏ��̊Ǘ�
//*********************************
class CPlayerStateAvoidRight : public CPlayerStateBase
{
public:

	CPlayerStateAvoidRight();
	~CPlayerStateAvoidRight();

	void OnStart();
	void OnUpdate();
	void OnExit();

private:

};
