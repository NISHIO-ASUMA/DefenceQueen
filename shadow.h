//====================================
//
// �e���� [ shadow.h ]
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
#include "object3D.h"

//*****************************
// �e�N���X���`
//*****************************
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadow();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdatePos(D3DXVECTOR3 pos) { SetPos(pos); }

	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
};
