//======================================
//
// �X�e���V���V���h�E���� [ shadowS.h ]
// Author: Asuma Nishio
//
//======================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"

//**********************************
// �V���h�E�X�e���V���N���X���`
//**********************************
class CShadowS :public CObjectX
{
public:

	CShadowS(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadowS();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtx;		// ���_�o�b�t�@

};