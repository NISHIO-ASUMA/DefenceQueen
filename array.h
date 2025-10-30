//===================================================
//
// �v���C���[�̒��ԏ��� [ array.h ]
// Author: Asuma Nishio
//
//===================================================

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
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CMotion;
class CSphereCollider;

//********************************
// �v���C���[�̒��ԃN���X���`
//********************************
class CArray : public CMoveCharactor
{
public:
	//************************
	// �g�p���[�V������
	//************************
	enum MOTION
	{
		MOTION_NEUTRAL,
		MOTION_MOVE,
		MOTION_DEATH,
		MOTION_MAX
	};

	CArray(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CArray();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Reset(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nLife);
	bool Colision(CSphereCollider* other);

	void SetActive(bool isFlags) { m_isActive = isFlags; }
	bool GetActive(void) { return m_isActive; }

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const int nLife);

private:

	std::unique_ptr<CParameter>m_pParameter;		// �p�����[�^�[�N���X�|�C���^
	std::unique_ptr<CStateMachine>m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^
	CMotion* m_pMotion;					// ���[�V�����|�C���^
	CSphereCollider* m_pSphereCollider;	// ���`�̃R���C�_�[
	bool m_isActive;	// �g�p��Ԃ��ǂ���
};