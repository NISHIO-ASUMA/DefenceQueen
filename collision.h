//=============================================
//
// �����蔻����N���X���� [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//************************************
// �R���W�����N���X���`
//************************************
class CCollision
{
public:

	//***************************
	// �R���W�����̎�ޒ�`
	//***************************
	enum TYPE
	{
		TYPE_NONE,		// ����
		TYPE_BOX,		// ��`
		TYPE_SPHERE,	// ��
		TYPE_MAX
	};

	CCollision(TYPE Type);
	~CCollision();

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetType(TYPE Type) { m_Type = Type; }

	D3DXVECTOR3 GetPos(void) const { return m_pos; }
	TYPE GetType(void) const { return m_Type; }

	static CCollision* Create(D3DXVECTOR3 pos, TYPE Type);

private:
	D3DXVECTOR3 m_pos;	// ���肷����W
	TYPE m_Type;		// ���
};






