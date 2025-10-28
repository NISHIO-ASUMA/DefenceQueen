//=================================================
//
// �����L�����N�^�[�N���X���� [ movecharactor.h ]
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
#include "object.h"
#include <memory>
#include <vector>

//**********************
// �O���錾
//**********************
class CShadowS;
class CModel;
class CMotion;

//*********************************
// �����L�����N�^�[�N���X���`
//*********************************
class CMoveCharactor : public CObject
{
public:
	//****************************
	// �L�����N�^�[�̎�ޒ�`
	//****************************
	enum TYPE
	{
		TYPE_NONE,
		TYPE_PLAYER,
		TYPE_BUDDY,
		TYPE_ENEMY,
		TYPE_MAX
	};

	CMoveCharactor(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CMoveCharactor();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetOldPos(const D3DXVECTOR3 posOld) { m_posOld = posOld; }

	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetRotDest(const D3DXVECTOR3 rotdest) { m_rotDest = rotdest; }

	void SetScale(const D3DXVECTOR3 scale = INITSCALE) { m_scale = scale; }
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void SetMoveValue(const float fValue) { m_fMoveValue = fValue; }
	void SetType(TYPE Type) { m_type = Type; }
	void MotionLoad(const char* pScriptName,int nDestMotions);
	void SetCharactor(TYPE type) { m_type = type; }

	D3DXVECTOR3 GetPos(void) const { return m_pos; }
	D3DXVECTOR3 GetOldPos(void) const { return m_posOld; }
	D3DXVECTOR3 GetRot(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	D3DXVECTOR3 GetRotDest(void) const { return m_rotDest; }

	/// <summary>
	/// ���[�V�����̃|�C���^��Ԃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns>
	CMotion* GetMotion(void) { return m_pMotion.get(); }

private:
	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_posOld;	// �ߋ����W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_rotDest;  // �ړI�p
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_scale;	// �g�嗦
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X
	TYPE m_type;			// ���

	std::unique_ptr<CMotion>m_pMotion;	// ���[�V�����N���X�̃��j�[�N�|�C���^
	std::vector<CModel*>m_pModel;		// ���f���N���X�̓��I�z��
	CShadowS* m_pShadowS;				// �X�e���V���V���h�E�N���X�̃|�C���^

	float m_fMoveValue;		// �ړ����Z�l
};