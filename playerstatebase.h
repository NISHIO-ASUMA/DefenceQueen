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
		ID_DAMAGE,// �_���[�W
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