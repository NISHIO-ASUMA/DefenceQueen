//======================================
//
// ����G�t�F�N�g���� [ effectpiler.h ]
// Author: Asuma Nishio
//
//======================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**************************  
// �C���N���[�h�t�@�C���錾
//**************************
#include "billboard.h"

//**************************  
// �G�t�F�N�g�N���X���`
//**************************
class CEffectPiler : public CBillboard
{
public:
	CEffectPiler(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectPiler();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectPiler* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife);

private:
	int m_nLife;		// �̗�
	float m_fRadius;	// ���a
};