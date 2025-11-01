//=============================================
//
// �G�̏�ԊǗ���ꏈ�� [ enemystatebase.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "state.h"
#include "enemy.h"

//*********************************
// �G�̏�ԊǗ��x�[�X�N���X
//*********************************
class CEnemyStateBase : public CStateBase
{
public:

	//***************************
	// ��ԊǗ�ID�񋓌^
	//***************************
	enum ID
	{
		ID_NEUTRAL, // �ҋ@
		ID_MOVE,	// �ړ�
		ID_ACTION,	// �U��
		ID_DAMAGE,	// �_���[�W
		ID_MAX
	};

	CEnemyStateBase();
	~CEnemyStateBase();

	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnExit() {}

	int GetID() const override { return m_ID; }

	void SetID(ID id) { m_ID = id; }
	void SetOwner(CEnemy* pEnemy) { m_pEnemy = pEnemy; }

protected:
	CEnemy* m_pEnemy;	// �G�̃|�C���^

private:
	ID m_ID;		// �񋓌^�̃|�C���^
};