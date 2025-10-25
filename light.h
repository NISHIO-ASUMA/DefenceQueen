//====================================
//
// ���C�g���� [ light.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// ���C�g�N���X���`
//**********************
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	static inline constexpr int NUMLIGHT = 3;		// �ݒu���鐔

	D3DLIGHT9 m_aLight[NUMLIGHT];   // ���C�g��
	D3DXVECTOR3 m_vecDir[NUMLIGHT];	// �x�N�g��
};
