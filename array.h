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

//********************************
// �v���C���[�̒��ԃN���X���`
//********************************
class CArray : public CMoveCharactor
{
public:
	CArray(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CArray();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CArray* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:

};