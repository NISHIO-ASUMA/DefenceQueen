//============================================
//
// ���[�U�[�G�t�F�N�g���� [ effectlaser.h ]
// Author: Asuma Nishio
// 
//============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"

//*********************************
// ���[�U�[�G�t�F�N�g�N���X���`
//*********************************
class CEffectLaser : public CBillboard
{
public:

	CEffectLaser(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectLaser();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectLaser* Create(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos,D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;		  // �̗�
	float m_fRadius;	  // ���a
	float m_fLength;	  // ����
	D3DXVECTOR3 m_move;	  // �ړ���
	D3DXVECTOR3 m_EndPos; // �I�_���W
	D3DXVECTOR3 m_OldPos; // �ߋ��̍��W
};