//===========================================
//
// �i�ߓ����� [ order.h ]
// Author: Asuma Nishio
//
//===========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <memory>

//********************************
// �i�ߓ��L�����N�^�[�N���X���`
//********************************
class COrder
{
public:

	COrder();
	~COrder();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static COrder* Create(void);

private:
};